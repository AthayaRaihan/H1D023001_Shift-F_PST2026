# Pertanyaan Modul 4 - PWM 
## 1. Jelaskan mengapa LED dapat diatur kecerahannya menggunakan fungsi analogWrite()!
Karena analogWrite() menghasilkan sinyal PWM (Pulse Width Modulation), yaitu sinyal digital yang dinyalakan dan dimatikan dengan sangat cepat. Dengan mengatur duty cycle (lama waktu LED menyala), LED terlihat lebih redup atau lebih terang meskipun sebenarnya hanya ON dan OFF secara cepat.
## 2. Apa hubungan antara nilai ADC (0–1023) dan nilai PWM (0–255)?
Nilai ADC dari potensiometer (0–1023) dikonversi menjadi nilai PWM (0–255) menggunakan fungsi map(). Hubungannya bersifat linier, artinya semakin besar nilai ADC maka semakin besar juga nilai PWM, sehingga LED menjadi semakin terang.
## 3. Modifikasilah program berikut agar LED hanya menyala pada rentang kecerahan sedang, yaitu hanya ketika nilai PWM berada pada rentang 50 sampai 200
#### Kode Program
```cpp
#include <Arduino.h>

const int potPin = A0;
const int ledPin = 9;

int nilaiADC = 0;
int pwm = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  nilaiADC = analogRead(potPin);

  // Mapping ADC ke PWM
  pwm = map(nilaiADC, 0, 1023, 0, 255);

  // Filter rentang PWM (50–200)
  if (pwm >= 50 && pwm <= 200) {
    analogWrite(ledPin, pwm);
  } else {
    analogWrite(ledPin, 0); // LED mati di luar rentang
  }

  Serial.print("ADC: ");
  Serial.print(nilaiADC);
  Serial.print(" | PWM: ");
  Serial.println(pwm);

  delay(50);
}
```

---

### Penjelasan Setiap Baris Kode

```cpp
#include <Arduino.h>
```
Library dasar Arduino.

---

```cpp
const int potPin = A0;
```
Menentukan potensiometer pada pin analog A0.

```cpp
const int ledPin = 9;
```
Menentukan LED pada pin digital PWM 9.

---

```cpp
int nilaiADC = 0;
```
Variabel untuk menyimpan nilai ADC (0–1023).

```cpp
int pwm = 0;
```
Variabel untuk menyimpan nilai PWM (0–255).

---

```cpp
void setup() {
```
Fungsi yang dijalankan sekali saat Arduino menyala.

```cpp
pinMode(ledPin, OUTPUT);
```
Mengatur pin LED sebagai output.

```cpp
Serial.begin(9600);
```
Memulai komunikasi serial.

```cpp
}
```
Menutup fungsi setup.

---

```cpp
void loop() {
```
Fungsi utama yang berjalan terus-menerus.

```cpp
nilaiADC = analogRead(potPin);
```
Membaca nilai analog dari potensiometer.

---

```cpp
pwm = map(nilaiADC, 0, 1023, 0, 255);
```
Mengubah nilai ADC menjadi PWM.

---

```cpp
if (pwm >= 50 && pwm <= 200) {
```
Kondisi agar LED hanya menyala jika PWM berada di antara 50 sampai 200.

```cpp
analogWrite(ledPin, pwm);
```
Mengatur kecerahan LED sesuai nilai PWM.

```cpp
} else {
  analogWrite(ledPin, 0);
}
```
Jika di luar rentang, LED dimatikan.

---

```cpp
Serial.print("ADC: ");
Serial.print(nilaiADC);
```
Menampilkan nilai ADC ke Serial Monitor.

```cpp
Serial.print(" | PWM: ");
Serial.println(pwm);
```
Menampilkan nilai PWM.

---

```cpp
delay(50);
```
Memberikan jeda agar pembacaan stabil.

```cpp
}
```
Menutup fungsi loop.

---
