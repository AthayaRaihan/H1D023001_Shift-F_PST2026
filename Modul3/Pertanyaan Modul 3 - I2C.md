# 3.6.4 Pertanyaan Seven Segment
## 1. Jelaskan bagaimana cara kerja komunikasi I2C antara Arduino dan LCD pada rangkaian tersebut!
Komunikasi I2C antara Arduino dan LCD menggunakan dua jalur, yaitu SDA sebagai jalur data dan SCL sebagai jalur clock. 
Arduino bertindak sebagai master yang mengirimkan perintah dan data ke LCD sebagai slave sesuai alamat I2C yang digunakan, 
yaitu 0x27. Melalui jalur ini, Arduino mengirim data tampilan seperti nilai ADC dan grafik bar ke LCD sehingga dapat ditampilkan pada layar.
## 2. Apakah pin potensiometer harus seperti itu? Jelaskan yang terjadi apabila pin kiri dan pin kanan tertukar! 
Pin potensiometer umumnya dihubungkan dengan pin kiri ke 5V, pin kanan ke GND, dan pin tengah ke pin analog Arduino sebagai 
output tegangan variabel. Susunan pin kiri dan kanan tidak harus selalu seperti itu, karena jika pin kiri dan kanan 
tertukar maka potensiometer tetap berfungsi normal, namun arah putarannya menjadi terbalik. Jika sebelumnya diputar ke 
kanan nilai bertambah, maka setelah ditukar justru nilai akan berkurang.
## 3. Modifikasi program dengan menggabungkan antara UART dan I2C (keduanya sebagai output) sehingga:
- Data tidak hanya ditampilkan di LCD tetapi juga di Serial Monitor  
- Adapun data yang ditampilkan pada Serial Monitor sesuai dengan table berikut: <br>
  | ADC : 0 | Volt : 0.00 V | Persen : 0% |
  |----------|----------|----------|
  Tampilan jika potensiometer dalam kondisi diputar paling kiri
- ADC: 0  0% | setCursor(0, 0) dan Bar (level) | setCursor(0, 1)
#### Kode Program
```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Alamat LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int pinPot = A0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  int nilai = analogRead(pinPot);

  // Konversi ke tegangan
  float volt = nilai * (5.0 / 1023.0);

  // Konversi ke persen
  int persen = map(nilai, 0, 1023, 0, 100);

  // Mapping bar LCD
  int panjangBar = map(nilai, 0, 1023, 0, 16);

  // ===== UART (Serial Monitor) =====
  Serial.print("ADC : ");
  Serial.print(nilai);
  Serial.print(" | Volt : ");
  Serial.print(volt, 2);
  Serial.print(" V | Persen : ");
  Serial.print(persen);
  Serial.println("%");

  // ===== LCD =====
  lcd.setCursor(0, 0);
  lcd.print("ADC: ");
  lcd.print(nilai);
  lcd.print(" ");

  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    if (i < panjangBar) {
      lcd.print((char)255);
    } else {
      lcd.print(" ");
    }
  }

  delay(200);
}
```

---

### Penjelasan Setiap Baris Kode

```cpp
#include <Wire.h>
```
Library untuk komunikasi I2C antara Arduino dan LCD.

```cpp
#include <LiquidCrystal_I2C.h>
```
Library untuk mengontrol LCD yang menggunakan modul I2C.

---

```cpp
LiquidCrystal_I2C lcd(0x27, 16, 2);
```
Membuat objek LCD dengan alamat I2C `0x27`, ukuran 16 kolom dan 2 baris.

```cpp
const int pinPot = A0;
```
Menentukan potensiometer terhubung ke pin analog A0.

---

```cpp
void setup() {
```
Fungsi yang dijalankan satu kali saat Arduino mulai aktif.

```cpp
Serial.begin(9600);
```
Memulai komunikasi serial dengan baud rate 9600.

```cpp
lcd.init();
```
Menginisialisasi LCD.

```cpp
lcd.backlight();
```
Menyalakan lampu latar LCD.

```cpp
}
```
Menutup fungsi `setup()`.

---

```cpp
void loop() {
```
Fungsi utama yang berjalan terus-menerus.

```cpp
int nilai = analogRead(pinPot);
```
Membaca nilai analog dari potensiometer (0–1023).

---

```cpp
float volt = nilai * (5.0 / 1023.0);
```
Mengubah nilai ADC menjadi tegangan dalam Volt.

```cpp
int persen = map(nilai, 0, 1023, 0, 100);
```
Mengubah nilai ADC menjadi persentase 0% sampai 100%.

```cpp
int panjangBar = map(nilai, 0, 1023, 0, 16);
```
Mengubah nilai ADC menjadi panjang bar LCD (0–16 karakter).

---

```cpp
Serial.print("ADC : ");
Serial.print(nilai);
```
Menampilkan nilai ADC ke Serial Monitor.

```cpp
Serial.print(" | Volt : ");
Serial.print(volt, 2);
```
Menampilkan nilai tegangan dengan 2 angka desimal.

```cpp
Serial.print(" V | Persen : ");
Serial.print(persen);
Serial.println("%");
```
Menampilkan nilai persentase dan pindah ke baris baru.

---

```cpp
lcd.setCursor(0, 0);
```
Memindahkan kursor ke kolom 0 baris pertama LCD.

```cpp
lcd.print("ADC: ");
lcd.print(nilai);
lcd.print(" ");
```
Menampilkan teks ADC dan nilainya pada baris pertama.

---

```cpp
lcd.setCursor(0, 1);
```
Memindahkan kursor ke kolom 0 baris kedua LCD.

```cpp
for (int i = 0; i < 16; i++) {
```
Perulangan untuk membuat grafik bar sepanjang 16 kolom.

```cpp
if (i < panjangBar) {
```
Jika posisi kolom masih dalam panjang bar.

```cpp
lcd.print((char)255);
```
Menampilkan blok penuh sebagai indikator level.

```cpp
} else {
  lcd.print(" ");
}
```
Jika tidak termasuk bar, maka ditampilkan spasi kosong.

---

```cpp
delay(200);
```
Memberikan jeda 200 ms sebelum pembacaan ulang.

```cpp
}
```
Menutup fungsi `loop()`.

--- 
## 4. Lengkapi table berikut berdasarkan pengamatan pada Serial Monitor 
| ADC | Volt (V) | Persen (%) |
|-----|----------|------------|
| 1   | 0.00 V   | 0%         |
| 21  | 0.10 V   | 2%         |
| 49  | 0.24 V   | 4%         |
| 74  | 0.36 V   | 7%         |
| 96  | 0.47 V   | 9%         |
