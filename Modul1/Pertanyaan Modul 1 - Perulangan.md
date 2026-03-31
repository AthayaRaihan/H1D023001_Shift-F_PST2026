# 1.6.4 Pertanyaan Perulangan
## 1. Gambarkan rangkaian schematic 5 LED running yang digunakan pada percobaan!
Rangkaian terdiri dari 5 LED yang dihubungkan ke pin digital Arduino. 
Konfigurasi rangkaian:
* LED 1 → Pin 2
* LED 2 → Pin 3
* LED 3 → Pin 4
* LED 4 → Pin 5
* LED 5 → Pin 6
* Semua kaki negatif (katoda) LED dihubungkan ke GND <br>
Skema sederhana:
Pin Arduino → Anoda LED <br>
Katoda LED → GND
---
### 2. Jelaskan bagaimana program membuat efek LED berjalan dari kiri ke kanan!
Program menggunakan perulangan `for` dengan nilai pin yang meningkat (increment).
```cpp
for (int ledPin = 2; ledPin < 7; ledPin++)
```
Penjelasan:
* Perulangan dimulai dari pin 2 hingga pin 6
* Setiap iterasi:
  * LED dinyalakan (`HIGH`)
  * Diberi jeda (`delay`)
  * Kemudian dimatikan (`LOW`)
* Karena pin bertambah dari kecil ke besar, LED terlihat menyala berurutan dari kiri ke kanan
Efek visual yang dihasilkan adalah LED menyala satu per satu secara berurutan.
---
### 3. Jelaskan bagaimana program membuat LED kembali dari kanan ke kiri!
Program menggunakan perulangan `for` dengan nilai pin yang menurun (decrement).
```cpp
for (int ledPin = 6; ledPin >= 2; ledPin--)
```
Penjelasan:
* Perulangan dimulai dari pin terbesar (6) hingga pin terkecil (2)
* Setiap iterasi:
  * LED dinyalakan
  * Diberi jeda
  * Dimatikan kembali
* Karena nilai pin berkurang, LED menyala dari kanan ke kiri
Efek ini membuat LED seperti “bolak-balik” (running LED dua arah).
---
### 4. Buatkan program agar LED menyala tiga LED kanan dan tiga LED kiri secara bergantian dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!
#### Kode Program
```cpp
const int ledPins[] = {2, 3, 4, 5, 6, 7};
int timer = 200;

void setup() {
  for (int i = 0; i < 6; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // Nyalakan 3 LED kiri (pin 2,3,4)
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPins[i], HIGH);
  }

  // Matikan 3 LED kanan (pin 5,6,7)
  for (int i = 3; i < 6; i++) {
    digitalWrite(ledPins[i], LOW);
  }

  delay(timer);

  // Matikan 3 LED kiri
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPins[i], LOW);
  }

  // Nyalakan 3 LED kanan
  for (int i = 3; i < 6; i++) {
    digitalWrite(ledPins[i], HIGH);
  }

  delay(timer);
}
```
---
### Penjelasan Setiap Baris Kode

```cpp
const int ledPins[] = {2, 3, 4, 5, 6, 7};
```

Array yang berisi daftar pin LED yang digunakan.

```cpp
int timer = 200;
```

Variabel untuk mengatur waktu jeda antar perpindahan LED.

---

```cpp
void setup() {
  for (int i = 0; i < 6; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}
```

Menginisialisasi semua pin LED sebagai output menggunakan perulangan.

---

```cpp
void loop() {
```

Fungsi utama yang berjalan terus menerus.

---

```cpp
for (int i = 0; i < 3; i++) {
  digitalWrite(ledPins[i], HIGH);
}
```

Menyalakan 3 LED bagian kiri (pin 2, 3, 4).

---

```cpp
for (int i = 3; i < 6; i++) {
  digitalWrite(ledPins[i], LOW);
}
```

Memastikan 3 LED bagian kanan dalam kondisi mati.

---

```cpp
delay(timer);
```

Memberikan jeda sebelum perpindahan pola.

---

```cpp
for (int i = 0; i < 3; i++) {
  digitalWrite(ledPins[i], LOW);
}
```

Mematikan 3 LED kiri.

---

```cpp
for (int i = 3; i < 6; i++) {
  digitalWrite(ledPins[i], HIGH);
}
```

Menyalakan 3 LED kanan (pin 5, 6, 7).

---

```cpp
delay(timer);
```

Memberikan jeda sebelum kembali ke pola awal.

---

### Kesimpulan

Perulangan `for` sangat membantu dalam mengontrol banyak LED secara efisien tanpa penulisan kode berulang. Dengan mengatur arah perulangan (naik atau turun), dapat dibuat efek LED berjalan. Kombinasi perulangan dan logika sederhana juga memungkinkan pembuatan pola LED yang lebih kompleks seperti nyala bergantian.
