# 2.5.4 Pertanyaan Seven Segment
## 1. Gambarkan rangkaian schematic yang digunakan pada percobaan!
<img width="1664" height="1292" alt="Screenshot 2026-04-09 091756" src="https://github.com/user-attachments/assets/0f182ecf-3d79-4ff6-b18b-65521c684bf9" />

## 2. Apa yang terjadi jika nilai num lebih dari 15?
Jika nilai num lebih dari 15, maka program akan mencoba mengakses indeks array digitPattern di 
luar batas (karena array hanya berisi indeks 0–15). Hal ini dapat menyebabkan tampilan seven 
segment menjadi tidak sesuai (acak) atau bahkan error karena terjadi out of bounds array access.
## 3. Apakah program ini menggunakan common cathode atau common anode? Jelaskan alasanya!
Program ini menggunakan common anode. Hal ini karena pada fungsi displayDigit(), nilai pada 
digitPattern dibalik menggunakan operator ! (NOT). Artinya, ketika nilai logika 1 (seharusnya menyalakan segmen), 
justru dikirim sebagai LOW, dan pada common anode segmen LED akan menyala saat diberi logika LOW.
## 4. Modifikasi program agar tampilan berjalan dari F ke 0 dan berikan penjelasan

#### Kode Program
```cpp
// Display 0 - 9 and A - F

// Pin mapping segment
const int segmentPins[8] = {7, 6, 5, 11, 10, 8, 9, 4};
// a b c d e f g dp

// Segment pattern for 0-F
// urutan segmen: a b c d e f g dp
byte digitPattern[16][8] = {

{1,1,1,1,1,1,0,0}, //0
{0,1,1,0,0,0,0,0}, //1
{1,1,0,1,1,0,1,0}, //2
{1,1,1,1,0,0,1,0}, //3
{0,1,1,0,0,1,1,0}, //4
{1,0,1,1,0,1,1,0}, //5
{1,0,1,1,1,1,1,0}, //6
{1,1,1,0,0,0,0,0}, //7
{1,1,1,1,1,1,1,0}, //8
{1,1,1,1,0,1,1,0}, //9
{1,1,1,0,1,1,1,0}, //A
{0,0,1,1,1,1,1,0}, //b
{1,0,0,1,1,1,0,0}, //C
{0,1,1,1,1,0,1,0}, //d
{1,0,0,1,1,1,1,0}, //E
{1,0,0,0,1,1,1,0}  //F
};

// Fungsi menampilkan digit
void displayDigit(int num)
{
  for(int i=0;i<8;i++)
  {
    digitalWrite(segmentPins[i], !digitPattern[num][i]);
  }
}

void setup()
{
  for(int i=0;i<8;i++)
  {
    pinMode(segmentPins[i], OUTPUT);
  }
}

void loop()
{
  for(int i=15;i >= 0;i--)
  {
    displayDigit(i);
    delay(1000);
  }
}
```

---

### Penjelasan Setiap Baris Kode

```cpp
const int segmentPins[8] = {7, 6, 5, 11, 10, 8, 9, 4};
```
Array yang berisi pin Arduino yang terhubung ke masing-masing segmen (a–g dan dp) pada seven segment.

```cpp
byte digitPattern[16][8]
```
Array 2 dimensi yang menyimpan pola nyala LED untuk menampilkan angka 0–9 dan huruf A–F.

```cpp
void displayDigit(int num)
```
Fungsi untuk menampilkan angka tertentu ke seven segment sesuai dengan pola yang telah ditentukan.

```cpp
digitalWrite(segmentPins[i], !digitPattern[num][i]);
```
Mengirim sinyal ke setiap segmen. Operator `!` digunakan karena seven segment bertipe common anode, sehingga logika dibalik (LOW = menyala, HIGH = mati).

```cpp
void setup()
```
Fungsi yang dijalankan sekali saat Arduino pertama kali menyala.

```cpp
pinMode(segmentPins[i], OUTPUT);
```
Mengatur semua pin sebagai output agar dapat mengontrol LED pada seven segment.

```cpp
void loop()
```
Fungsi utama yang berjalan terus menerus.

```cpp
for(int i=15;i >= 0;i--)
```
Perulangan dari 15 ke 0 yang digunakan untuk menampilkan angka secara menurun (F ke 0).

```cpp
displayDigit(i);
```
Menampilkan angka sesuai nilai variabel `i` pada seven segment.

```cpp
delay(1000);
```
Memberikan jeda 1 detik agar perubahan angka dapat terlihat jelas.
