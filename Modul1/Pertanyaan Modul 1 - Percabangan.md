# 1.5.4 Pertanyaan Percabangan
## 1. Pada kondisi apa program masuk ke blok if?
Program akan masuk ke blok if ketika nilai variabel `timeDelay` kurang dari atau sama dengan 100 <br>
```cpp 
if (timeDelay <= 100)
```
Artinya, ketika nilai `timeDelay` sudah berkurang secara bertahap (dikurangi 100 setiap siklus) hingga mencapai 100 milidetik atau kurang, maka kondisi tersebut bernilai true, sehingga program akan menjalankan perintah di dalam blok if.
## 2. Pada kondisi apa program masuk ke blok else?
Program akan masuk ke blok else ketika kondisi pada if tidak terpenuhi, yaitu saat nilai `timeDelay` lebih dari 100 (timeDelay > 100).
```cpp
  else { 
timeDelay -= 100;   // percepatan bertahap 
}
```
Perintah tersebut berfungsi untuk mengurangi nilai delay secara bertahap, sehingga kecepatan kedipan LED menjadi semakin cepat di setiap siklus.
## 3. Apa fungsi dari perintah delay(timeDelay)?
```cpp
delay(timeDelay);
```
Perintah delay(timeDelay) berfungsi untuk memberikan jeda waktu (delay) pada program selama nilai timeDelay dalam satuan milidetik (ms).
Dalam konteks program ini, delay(timeDelay) digunakan untuk:
- Mengatur lama waktu LED menyala
- Mengatur lama waktu LED mati
## 4. Jika program yang dibuat memiliki alur mati → lambat → cepat → reset (mati), ubah menjadi LED tidak langsung reset → tetapi berubah dari cepat → sedang → mati dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!
Alur yang diminta : mati → lambat → cepat → sedang → mati (tanpa reset langsung)
### Implementasi Program

Berikut adalah kode program yang digunakan untuk menghasilkan alur tersebut:

```cpp
const int ledPin = 13; 
int timeDelay = 1000; 
bool menujuCepat = true; 

void setup() { 
  pinMode(ledPin, OUTPUT); 
} 

void loop() { 
  digitalWrite(ledPin, HIGH); 
  delay(timeDelay); 

  digitalWrite(ledPin, LOW); 
  delay(timeDelay); 

  if (menujuCepat) { 
    timeDelay -= 100; 

    if (timeDelay <= 100) { 
      menujuCepat = false; 
    } 
  } else { 
    timeDelay += 100; 

    if (timeDelay >= 1000) { 
      delay(2000); 
      timeDelay = 1000; 
      menujuCepat = true; 
    } 
  } 
}
```

---

### Penjelasan Setiap Baris Kode

```cpp
const int ledPin = 13;
```

Menentukan bahwa LED terhubung ke pin 13 pada Arduino.

```cpp
int timeDelay = 1000;
```

Variabel untuk menyimpan waktu delay dalam milidetik. Nilai awal 1000 ms (kedip lambat).

```cpp
bool menujuCepat = true;
```

Variabel untuk menentukan arah perubahan kecepatan:

* `true` → LED akan semakin cepat
* `false` → LED akan semakin lambat

---

```cpp
void setup() {
  pinMode(ledPin, OUTPUT);
}
```

Mengatur pin LED sebagai output agar dapat digunakan untuk menyalakan dan mematikan LED.

---

```cpp
void loop() {
```

Fungsi utama yang akan dijalankan berulang kali selama Arduino aktif.

---

```cpp
digitalWrite(ledPin, HIGH);
delay(timeDelay);
```

Menyalakan LED dan mempertahankannya selama waktu `timeDelay`.

---

```cpp
digitalWrite(ledPin, LOW);
delay(timeDelay);
```

Mematikan LED dan memberikan jeda sesuai `timeDelay`.

---

```cpp
if (menujuCepat) {
```

Kondisi untuk mengecek apakah LED sedang dalam fase percepatan.

---

```cpp
timeDelay -= 100;
```

Mengurangi nilai delay sehingga LED berkedip semakin cepat.

---

```cpp
if (timeDelay <= 100) {
  menujuCepat = false;
}
```

Jika delay sudah sangat kecil (LED sangat cepat), maka arah diubah menjadi perlambatan.

---

```cpp
else {
  timeDelay += 100;
}
```

Jika tidak dalam fase percepatan, maka delay ditambah sehingga LED menjadi lebih lambat.

---

```cpp
if (timeDelay >= 1000) {
```

Jika delay sudah kembali ke nilai awal (lambat).

---

```cpp
delay(2000);
```

Memberikan jeda selama 2 detik sebelum mengulang siklus.

---

```cpp
timeDelay = 1000;
menujuCepat = true;
```

Mengatur ulang kondisi awal agar siklus dapat dimulai kembali dari lambat ke cepat.

---

### Kesimpulan

Program ini memodifikasi pola LED dari yang sebelumnya langsung reset menjadi lebih halus, yaitu dengan menambahkan fase perlambatan (sedang) sebelum kembali ke kondisi awal. Hal ini dicapai dengan menggunakan variabel kontrol (`menujuCepat`) dan percabangan `if-else` untuk mengatur arah perubahan kecepatan LED.
