# 3.5.4 Pertanyaan UART
## 1. Jelaskan proses dari input keyboard hingga LED menyala/mati! 
Saat pengguna mengetik angka 1 atau 0 pada keyboard di Serial Monitor, data akan dikirim dari komputer ke Arduino melalui 
komunikasi UART melalui kabel USB. Arduino kemudian membaca data yang masuk menggunakan fungsi Serial.read(). Jika data 
yang diterima adalah '1', maka Arduino memberikan logika HIGH pada pin LED sehingga LED menyala. Jika data yang diterima 
adalah '0', maka Arduino memberikan logika LOW pada pin LED sehingga LED mati.
## 2. Mengapa digunakan Serial.available() sebelum membaca data? Apa yang terjadi jika baris tersebut dihilangkan?
Fungsi Serial.available() digunakan untuk mengecek apakah ada data yang masuk ke buffer serial sebelum dibaca dengan Serial.read(). 
Hal ini penting agar Arduino hanya membaca saat data benar-benar tersedia. Jika baris tersebut dihilangkan, maka Serial.read() dapat 
dijalankan saat tidak ada data masuk, sehingga menghasilkan nilai kosong atau data tidak valid dan program dapat bekerja tidak sesuai harapan.
## 3. Modifikasi program agar LED berkedip (blink) ketika menerima input '2' dengan kondisi jika ‘2’ aktif maka LED akan terus berkedip sampai perintah selanjutnya diberikan
#### Kode Program
```cpp
const int PIN_LED = 12;
char mode = '0';

unsigned long previousMillis = 0;
const long interval = 500;

bool ledState = LOW;

void setup() {
  Serial.begin(9600);
  Serial.println("Ketik '1' = ON, '0' = OFF, '2' = BLINK");
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char data = Serial.read();

    if (data == '1') {
      mode = '1';
      Serial.println("LED ON");
    }
    else if (data == '0') {
      mode = '0';
      Serial.println("LED OFF");
    }
    else if (data == '2') {
      mode = '2';
      Serial.println("LED BLINK");
    }
    else if (data != '\n' && data != '\r') {
      Serial.println("Perintah tidak dikenal");
    }
  }

  if (mode == '1') {
    digitalWrite(PIN_LED, HIGH);
  }
  else if (mode == '0') {
    digitalWrite(PIN_LED, LOW);
  }
  else if (mode == '2') {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(PIN_LED, ledState);
    }
  }
}
```

---

### Penjelasan Setiap Baris Kode

```cpp
const int PIN_LED = 12;
```
Menentukan pin 12 sebagai pin output untuk LED.

```cpp
char mode = '0';
```
Variabel untuk menyimpan mode LED. Nilai awal `'0'` berarti LED mati.

```cpp
unsigned long previousMillis = 0;
```
Menyimpan waktu terakhir saat LED berubah kondisi.

```cpp
const long interval = 500;
```
Menentukan jeda kedip LED selama 500 milidetik.

```cpp
bool ledState = LOW;
```
Menyimpan status LED saat ini (mati atau menyala).

---

```cpp
void setup() {
```
Fungsi yang dijalankan satu kali saat Arduino dinyalakan.

```cpp
Serial.begin(9600);
```
Memulai komunikasi serial dengan baud rate 9600.

```cpp
Serial.println("Ketik '1' = ON, '0' = OFF, '2' = BLINK");
```
Menampilkan petunjuk penggunaan pada Serial Monitor.

```cpp
pinMode(PIN_LED, OUTPUT);
```
Mengatur pin LED sebagai output.

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
if (Serial.available() > 0) {
```
Mengecek apakah ada data masuk dari Serial Monitor.

```cpp
char data = Serial.read();
```
Membaca satu karakter data yang dikirim.

---

```cpp
if (data == '1') {
```
Jika input adalah angka 1.

```cpp
mode = '1';
Serial.println("LED ON");
```
Mengubah mode menjadi ON dan menampilkan pesan LED menyala.

---

```cpp
else if (data == '0') {
```
Jika input adalah angka 0.

```cpp
mode = '0';
Serial.println("LED OFF");
```
Mengubah mode menjadi OFF dan menampilkan pesan LED mati.

---

```cpp
else if (data == '2') {
```
Jika input adalah angka 2.

```cpp
mode = '2';
Serial.println("LED BLINK");
```
Mengubah mode menjadi BLINK dan menampilkan pesan LED berkedip.

---

```cpp
else if (data != '\n' && data != '\r') {
```
Jika input bukan 1, 0, 2, dan bukan ENTER.

```cpp
Serial.println("Perintah tidak dikenal");
```
Menampilkan pesan bahwa input tidak dikenali.

---

```cpp
if (mode == '1') {
  digitalWrite(PIN_LED, HIGH);
}
```
Jika mode ON aktif, LED akan menyala terus.

---

```cpp
else if (mode == '0') {
  digitalWrite(PIN_LED, LOW);
}
```
Jika mode OFF aktif, LED akan mati.

---

```cpp
else if (mode == '2') {
```
Jika mode BLINK aktif.

```cpp
unsigned long currentMillis = millis();
```
Mengambil waktu saat ini sejak Arduino menyala.

```cpp
if (currentMillis - previousMillis >= interval) {
```
Mengecek apakah sudah lewat 500 ms sejak perubahan terakhir.

```cpp
previousMillis = currentMillis;
```
Menyimpan waktu terbaru.

```cpp
ledState = !ledState;
```
Membalik kondisi LED (jika mati jadi nyala, jika nyala jadi mati).

```cpp
digitalWrite(PIN_LED, ledState);
```
Mengubah kondisi LED sesuai status terbaru.

---
## 4. Tentukan apakah menggunakan delay() atau milis()! Jelaskan pengaruhnya terhadap sistem 
Pada program modifikasi tersebut digunakan millis() untuk mengatur waktu kedip LED. Fungsi millis() bekerja dengan menghitung waktu sejak Arduino mulai berjalan, sehingga LED dapat berkedip setiap interval tertentu tanpa menghentikan proses utama program.

Pengaruhnya terhadap sistem adalah Arduino tetap dapat menjalankan tugas lain secara bersamaan, seperti membaca input baru dari Serial Monitor. Hal ini membuat sistem menjadi lebih responsif dan efisien dibandingkan delay(), karena delay() akan menghentikan sementara jalannya program selama waktu tertentu.
