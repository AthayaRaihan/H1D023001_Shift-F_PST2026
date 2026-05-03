# Pertanyaan Modul 4 - ADC
## 1. Simpan scetch dengan nama file modul4_percobaan1 konfigurasi rangkaian
analogRead() digunakan untuk membaca nilai tegangan analog dari potensiometer, lalu mengubahnya menjadi data digital (0–1023) yang bisa diproses oleh Arduino.
## 2. Mengapa diperlukan fungsi map() dalam program tersebut?
Karena nilai dari analogRead() (0–1023) berbeda dengan rentang sudut servo (0–180°), maka map() digunakan untuk mengubah nilai ADC tersebut agar sesuai dengan sudut yang bisa digunakan oleh servo.
## 3. Modifikasi program berikut agar servo hanya bergerak dalam rentang 30° hingga 150°, meskipun potensiometer tetap memiliki rentang ADC 0–1023
#### Kode Program
```cpp
#include <Servo.h>

Servo myservo;

const int potensioPin = A0;
const int servoPin = 9;

int val = 0;
int pos = 0;

void setup() {
  myservo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  val = analogRead(potensioPin);

  // Mapping ke 30–150 derajat
  pos = map(val, 0, 1023, 30, 150);

  myservo.write(pos);

  Serial.print("ADC Potensio: ");
  Serial.print(val);
  Serial.print(" | Sudut Servo: ");
  Serial.println(pos);

  delay(15);
}
```

---

### Penjelasan Setiap Baris Kode

```cpp
#include <Servo.h>
```
Library untuk mengontrol motor servo pada Arduino.

```cpp
Servo myservo;
```
Membuat objek servo dengan nama `myservo`.

---

```cpp
const int potensioPin = A0;
```
Menentukan potensiometer terhubung ke pin analog A0.

```cpp
const int servoPin = 9;
```
Menentukan servo terhubung ke pin digital 9 (PWM).

---

```cpp
int val = 0;
```
Variabel untuk menyimpan nilai ADC dari potensiometer (0–1023).

```cpp
int pos = 0;
```
Variabel untuk menyimpan nilai sudut servo.

---

```cpp
void setup() {
```
Fungsi yang dijalankan satu kali saat Arduino mulai aktif.

```cpp
myservo.attach(servoPin);
```
Menghubungkan servo ke pin 9 agar bisa dikontrol.

```cpp
Serial.begin(9600);
```
Memulai komunikasi serial dengan baud rate 9600.

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
val = analogRead(potensioPin);
```
Membaca nilai analog dari potensiometer (0–1023).

---

```cpp
pos = map(val, 0, 1023, 30, 150);
```
Mengubah nilai ADC menjadi sudut servo dengan rentang 30–150 derajat.

---

```cpp
myservo.write(pos);
```
Menggerakkan servo sesuai sudut hasil mapping.

---

```cpp
Serial.print("ADC Potensio: ");
Serial.print(val);
```
Menampilkan nilai ADC ke Serial Monitor.

```cpp
Serial.print(" | Sudut Servo: ");
Serial.println(pos);
```
Menampilkan sudut servo dan pindah ke baris baru.

---

```cpp
delay(15);
```
Memberikan jeda agar servo stabil dan tidak bergetar.

```cpp
}
```
Menutup fungsi `loop()`.

---
