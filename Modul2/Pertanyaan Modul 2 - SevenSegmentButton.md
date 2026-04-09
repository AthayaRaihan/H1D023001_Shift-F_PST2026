# 2.6.4 Pertanyaan Seven Segment Button
## 1. Gambarkan rangkaian schematic yang digunakan pada percobaan!
<img width="1672" height="1296" alt="Screenshot 2026-04-09 100013" src="https://github.com/user-attachments/assets/18ae78cb-54f3-49cc-ab7c-a13a8105d27b" />

## 2. Mengapa pada push button digunakan mode INPUT_PULLUP pada Arduino Uno? Apa keuntungannya dibandingkan rangkaian biasa?
Mode INPUT_PULLUP digunakan agar pin input memiliki resistor pull-up internal, sehingga kondisi default bernilai HIGH tanpa perlu resistor eksternal. Saat tombol ditekan, pin akan terhubung ke GND sehingga bernilai LOW.
Keuntungannya:
- Tidak perlu tambahan resistor (lebih sederhana)
- Menghindari kondisi floating (input tidak stabil)
- Rangkaian lebih rapi dan mudah dibuat
## 3. Jika salah satu LED segmen tidak menyala, apa saja kemungkinan penyebabnya dari sisi hardware maupun software?
Jika salah satu LED segmen tidak menyala, kemungkinan penyebabnya adalah:

Dari sisi hardware:
- Kabel jumper tidak terhubung dengan benar atau longgar
- Resistor rusak atau tidak terpasang
- LED pada segmen tersebut rusak
- Kesalahan wiring (pin salah sambung)

Dari sisi software:
- Kesalahan pada mapping pin di program
- Pola pada digitPattern tidak sesuai (nilai 0/1 salah)
- Pin belum diset sebagai OUTPUT pada pinMode()
## 4. Modifikasi rangkaian dan program dengan dua push button yang berfungsi sebagai penambahan (increment) dan pengurangan (decrement) pada sistem counter dan berikan penjelasan disetiap baris kode nya

#### Kode Program
```cpp
const int segmentPins[8] = {7, 6, 5 ,11, 10, 8, 9, 4};
// a b c d e f g dp

const int btnUp = 3;
const int btnDown = 2;

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

int currentDigit = 0;

bool lastUpState = HIGH;
bool lastDownState = HIGH;

void displayDigit(int num)
{
  for(int i=0;i<8;i++)
  {
    digitalWrite(segmentPins[i], !digitPattern[num][i]);
  }
}

void setup() {
  for(int i=0;i<8;i++)
  {
    pinMode(segmentPins[i], OUTPUT);
  }

  pinMode(btnUp, INPUT_PULLUP);
  pinMode(btnDown, INPUT_PULLUP);

  displayDigit(currentDigit);
}

void loop() {
  bool upState = digitalRead(btnUp);
  bool downState = digitalRead(btnDown);

  if(lastUpState == HIGH && upState == LOW)
  {
    currentDigit++;
    if(currentDigit > 15) currentDigit = 0;
    displayDigit(currentDigit);
  }
  
  if(lastDownState == HIGH && downState == LOW)
  {
    currentDigit--;
    if(currentDigit < 0)
      currentDigit = 15;
    displayDigit(currentDigit);
  }
  
  lastUpState = upState;
  lastDownState = downState;
}
```

---

### Penjelasan Setiap Baris Kode

```cpp
const int segmentPins[8] = {7, 6, 5 ,11, 10, 8, 9, 4};
```
Array yang berisi pin Arduino yang terhubung ke masing-masing segmen seven segment.

```cpp
const int btnUp = 3;
const int btnDown = 2;
```
Menentukan pin untuk push button:
- `btnUp` untuk menambah angka (increment)
- `btnDown` untuk mengurangi angka (decrement)

---

```cpp
byte digitPattern[16][8]
```
Array 2 dimensi yang menyimpan pola nyala LED untuk menampilkan angka 0–9 dan A–F.

---

```cpp
int currentDigit = 0;
```
Variabel untuk menyimpan nilai angka yang sedang ditampilkan.

---

```cpp
bool lastUpState = HIGH;
bool lastDownState = HIGH;
```
Menyimpan kondisi tombol sebelumnya untuk mendeteksi perubahan saat tombol ditekan (edge detection).

---

```cpp
void displayDigit(int num)
```
Fungsi untuk menampilkan angka ke seven segment sesuai dengan pola.

---

```cpp
digitalWrite(segmentPins[i], !digitPattern[num][i]);
```
Mengirim sinyal ke setiap segmen.  
Operator `!` digunakan karena seven segment bertipe common anode.

---

```cpp
void setup()
```
Fungsi yang dijalankan sekali saat Arduino menyala.

---

```cpp
pinMode(segmentPins[i], OUTPUT);
```
Mengatur semua pin seven segment sebagai output.

---

```cpp
pinMode(btnUp, INPUT_PULLUP);
pinMode(btnDown, INPUT_PULLUP);
```
Mengatur push button sebagai input dengan pull-up internal agar stabil tanpa resistor tambahan.

---

```cpp
displayDigit(currentDigit);
```
Menampilkan angka awal (0) saat pertama kali dijalankan.

---

```cpp
void loop()
```
Fungsi utama yang berjalan terus menerus.

---

```cpp
bool upState = digitalRead(btnUp);
bool downState = digitalRead(btnDown);
```
Membaca kondisi tombol saat ini.

---

```cpp
if(lastUpState == HIGH && upState == LOW)
```
Mendeteksi saat tombol increment ditekan (perubahan dari HIGH ke LOW).

---

```cpp
currentDigit++;
```
Menambah nilai counter.

---

```cpp
if(currentDigit > 15) currentDigit = 0;
```
Jika melebihi 15, maka kembali ke 0 (looping).

---

```cpp
if(lastDownState == HIGH && downState == LOW)
```
Mendeteksi saat tombol decrement ditekan.

---

```cpp
currentDigit--;
```
Mengurangi nilai counter.

---

```cpp
if(currentDigit < 0) currentDigit = 15;
```
Jika kurang dari 0, maka kembali ke 15.

---

```cpp
displayDigit(currentDigit);
```
Menampilkan angka terbaru ke seven segment.

---

```cpp
lastUpState = upState;
lastDownState = downState;
```
Menyimpan kondisi tombol saat ini untuk perbandingan pada loop berikutnya.
