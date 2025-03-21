#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 4);// jika 16x2 //0x27 alamat I2C 

////////////PIN SENSOR TEGANGAN////////////
#define Sensor_Tegangan A0
////////////PIN TRIAC/////////////////////
#define TRC1 4
#define TRC2 5
#define TRC3 6
#define TRC4 7

float ref = 5; //5v ref arduino

float r1  = 30000; //30k
float r2  = 7500; //7.5k

const int sensorPin = A3;  // Pin ADC tempat sensor ZMPT101B terhubung
const float calibrationFactor = 0.707;  // Faktor kalibrasi RMS dari Vpp
const int sampleSize = 100;  // Jumlah sampel untuk mendapatkan nilai maksimum & minimum

bool pl = false;  // Status PLN aktif
bool ps = false;  // Status PLTS aktif
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(Sensor_Tegangan,INPUT); // Seting Sebagai Input
  pinMode(sensorPin,INPUT); // Seting Sebagai Input
  pinMode(TRC1,OUTPUT); // Seting sebagai output PLTS
  pinMode(TRC2,OUTPUT); // Seting sebagai output PLN
  pinMode(TRC3,OUTPUT); // opsi
  pinMode(TRC4,OUTPUT);
  digitalWrite(TRC1,LOW); // Matikan PLTS
  digitalWrite(TRC2,LOW); // Matikan PLN
  digitalWrite(TRC3,LOW); // Matikan PLTS
  digitalWrite(TRC4,LOW); // Matikan PLN
  lcd.init(); //inisialisasi LCD
  lcd.backlight(); //Nyalakan Lampu LCD
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int adc           = analogRead(Sensor_Tegangan); // baca nilai adc asli
  float voltage     = adc*(ref/1023.0); //konversi ke tegangan 0-5
  float RealVoltage = voltage * ((r1+r2)/r2);// masukan persamaan untuk dapat tegangan real
  float y = (0.8248*RealVoltage) + 0.0551;

//  Serial.println("Tegangan Panel Surya = "+String(RealVoltage)+" V/DC");
//  Serial.println("Tegangan Real  Surya = "+String(y)+" V/DC");

  int sensorMax = 0;
    int sensorMin = 1023;

    // Ambil beberapa sampel untuk mendapatkan nilai puncak dan lembah
    for (int i = 0; i < sampleSize; i++) {
        int sensorValue = analogRead(sensorPin);

        if (sensorValue > sensorMax) {
            sensorMax = sensorValue;
        }
        if (sensorValue < sensorMin) {
            sensorMin = sensorValue;
        }

        delayMicroseconds(500);  // Delay kecil agar tidak terlalu cepat membaca
    }
   // Hitung tegangan puncak-ke-puncak (Vpp)
    float Vpp = (sensorMax - sensorMin) * (5.0 / 1023.0);  // Jika menggunakan Arduino (5V ADC)
    // float Vpp = (sensorMax - sensorMin) * (3.3 / 4095.0);  // Jika menggunakan ESP32 (3.3V ADC)

    // Konversi ke tegangan RMS
    float Vrms = Vpp * calibrationFactor;
    
    float Faktor_Kalibrasi = 220 / 2.24;
    float tegangan_AC = Vrms * Faktor_Kalibrasi;
    float AC_Voltage = Vrms * Faktor_Kalibrasi; 
    // Tampilkan hasil di Serial Monitor
//    Serial.print("Vpp: ");
//    Serial.print(Vpp);
//    Serial.print("V, Vrms: ");
//    Serial.print(Vrms);
//    Serial.print("V, AC : ");
//    Serial.print(AC_Voltage);
//    Serial.println("V");
  lcd.setCursor(0, 0);
  lcd.print("DC = "+String(y)+" V/DC");
  lcd.setCursor(0, 1);
  if(AC_Voltage>=100){
  lcd.print("AC = "+String(AC_Voltage)+" V/AC");}
  else{
  lcd.print("AC = "+String(AC_Voltage)+" V/AC  ");}
  
if (RealVoltage <= 7 && !pl) {  // Jika tegangan panel drop & PLN belum menyala
    Serial.println("PLN NYALA");
    lcd.setCursor(0,3);
    lcd.print("PLN NYALA ");
    digitalWrite(TRC1, LOW);  // Matikan PLTS
    digitalWrite(TRC3, LOW);
    delay(5000);
    digitalWrite(TRC2, HIGH);  // Nyalakan PLN
    digitalWrite(TRC4, HIGH);
    
    pl = true;  // PLN aktif
    ps = false; // PLTS nonaktif
} 

else if (RealVoltage > 7 && !ps) {  // Jika tegangan panel cukup & PLTS belum menyala
    Serial.println("PLTS NYALA");
    lcd.setCursor(0,3);
    lcd.print("PLTS NYALA ");
    digitalWrite(TRC2, LOW);  // Matikan PLN
    digitalWrite(TRC4, LOW);
    delay(5000);
    digitalWrite(TRC1, HIGH);  // Nyalakan PLTS
    digitalWrite(TRC3, HIGH);
    
    ps = true;  // PLTS aktif
    pl = false; // PLN nonaktif
}


}
