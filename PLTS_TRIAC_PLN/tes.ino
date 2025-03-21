//const int sensorPin = A3;  // Pin ADC tempat sensor ZMPT101B terhubung
//const float calibrationFactor = 0.707;  // Faktor kalibrasi RMS dari Vpp
//const int sampleSize = 100;  // Jumlah sampel untuk mendapatkan nilai maksimum & minimum
//
//void setup() {
//    Serial.begin(9600);  // Inisialisasi komunikasi serial
//}
//
//void loop() {
//    int sensorMax = 0;
//    int sensorMin = 1023;
//
//    // Ambil beberapa sampel untuk mendapatkan nilai puncak dan lembah
//    for (int i = 0; i < sampleSize; i++) {
//        int sensorValue = analogRead(sensorPin);
//
//        if (sensorValue > sensorMax) {
//            sensorMax = sensorValue;
//        }
//        if (sensorValue < sensorMin) {
//            sensorMin = sensorValue;
//        }
//
//        delayMicroseconds(500);  // Delay kecil agar tidak terlalu cepat membaca
//    }
//
//    // Hitung tegangan puncak-ke-puncak (Vpp)
//    float Vpp = (sensorMax - sensorMin) * (5.0 / 1023.0);  // Jika menggunakan Arduino (5V ADC)
//    // float Vpp = (sensorMax - sensorMin) * (3.3 / 4095.0);  // Jika menggunakan ESP32 (3.3V ADC)
//
//    // Konversi ke tegangan RMS
//    float Vrms = Vpp * calibrationFactor;
//    
//    float Faktor_Kalibrasi = 220 / 2.24;
//    float tegangan_AC = Vrms * Faktor_Kalibrasi;
//    float AC_Voltage = Vrms * Faktor_Kalibrasi; 
//    // Tampilkan hasil di Serial Monitor
//    Serial.print("Vpp: ");
//    Serial.print(Vpp);
//    Serial.print("V, Vrms: ");
//    Serial.print(Vrms);
//    Serial.print("V, AC : ");
//    Serial.print(AC_Voltage);
//    Serial.println("V");
//
//
//    delay(1000);  // Tunggu 1 detik sebelum membaca ulang
//}
