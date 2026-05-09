# 5.6.4 Pertanyaan KomunikasiTask

## 1. Apakah kedua task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!
Kedua task pada program FreeRTOS berjalan secara concurrent, sehingga terlihat berjalan secara bersamaan. Namun pada Arduino Uno yang menggunakan satu inti prosesor, task sebenarnya dijalankan secara bergantian dengan sangat cepat oleh scheduler FreeRTOS. Pada program ini terdapat task read_data yang bertugas mengirim data ke queue dan task display yang bertugas menerima lalu menampilkan data ke Serial Monitor. Scheduler FreeRTOS akan mengatur pergantian eksekusi antar task. Ketika suatu task menjalankan vTaskDelay() atau sedang menunggu data queue, prosesor akan diberikan kepada task lainnya sehingga kedua task dapat berjalan secara concurrent dengan baik. 
## 2. Apakah program ini berpotensi mengalami race condition? Jelaskan!
Program ini memiliki potensi race condition yang sangat kecil karena komunikasi data antar task menggunakan queue dari FreeRTOS. Queue berfungsi sebagai media komunikasi yang aman (thread-safe) sehingga akses data diatur langsung oleh kernel FreeRTOS. Pada program ini, task read_data hanya mengirim data ke queue menggunakan xQueueSend(), sedangkan task display hanya membaca data menggunakan xQueueReceive(). Karena kedua task tidak mengakses variabel global yang sama secara langsung, maka konflik akses data dapat dihindari. Dengan demikian, penggunaan queue membantu mencegah terjadinya race condition pada sistem multitasking. 
## 3. Modifikasilah program dengan menggunakan sensor DHT sesungguhnya sehingga informasi yang ditampilkan dinamis. Bagaimana hasilnya?

### Kode Program
```cpp
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22   // ganti DHT22 jika pakai DHT22

DHT dht(DHTPIN, DHTTYPE);

struct readings {
  float temp;
  float h;
};

QueueHandle_t my_queue;

void setup() {
  Serial.begin(9600);
  dht.begin();

  my_queue = xQueueCreate(1, sizeof(struct readings));

  xTaskCreate(read_data, "read sensors", 256, NULL, 1, NULL);
  xTaskCreate(display,   "display",      256, NULL, 1, NULL);
}

void loop() {}

void read_data(void *pvParameters) {
  struct readings x;

  for (;;) {
    float humidity    = dht.readHumidity();
    float temperature = dht.readTemperature(); // Celsius

    if (!isnan(humidity) && !isnan(temperature)) {
      x.temp = temperature;
      x.h    = humidity;
      xQueueSend(my_queue, &x, portMAX_DELAY);
    } else {
      Serial.println("Gagal membaca sensor DHT!");
    }

    vTaskDelay(pdMS_TO_TICKS(2000)); // DHT butuh min. 2 detik antar pembacaan
  }
}

void display(void *pvParameters) {
  struct readings x;

  for (;;) {
    if (xQueueReceive(my_queue, &x, portMAX_DELAY) == pdPASS) {
      Serial.print("Temperatur = ");
      Serial.print(x.temp, 1);
      Serial.println(" °C");

      Serial.print("Kelembaban = ");
      Serial.print(x.h, 1);
      Serial.println(" %");

      Serial.println("-------------------");
    }
  }
}
```

```cpp
#include <Arduino_FreeRTOS.h>
```
Digunakan untuk memanggil library FreeRTOS agar Arduino dapat menjalankan multitasking.

```cpp
#include <queue.h>
```
Digunakan untuk memanggil library queue pada FreeRTOS yang berfungsi sebagai media komunikasi antar task.

```cpp
#include <DHT.h>
```
Digunakan untuk memanggil library sensor DHT.

---

```cpp
#define DHTPIN 2
```
Menentukan bahwa pin data sensor DHT terhubung ke pin digital 2 Arduino.

```cpp
#define DHTTYPE DHT22
```
Menentukan jenis sensor yang digunakan yaitu DHT22.

---

```cpp
DHT dht(DHTPIN, DHTTYPE);
```
Membuat objek sensor DHT dengan pin dan tipe sensor yang telah ditentukan.

---

```cpp
struct readings {
  float temp;
  float h;
};
```
Membuat struktur data bernama `readings` untuk menyimpan data suhu (`temp`) dan kelembaban (`h`).

---

```cpp
QueueHandle_t my_queue;
```
Membuat variabel queue handle untuk komunikasi antar task.

---

```cpp
void setup() {
```
Fungsi setup dijalankan satu kali saat Arduino pertama kali menyala.

---

```cpp
Serial.begin(9600);
```
Memulai komunikasi serial dengan baud rate 9600 bps.

```cpp
dht.begin();
```
Menginisialisasi sensor DHT agar siap digunakan.

---

```cpp
my_queue = xQueueCreate(1, sizeof(struct readings));
```
Membuat queue dengan kapasitas 1 data bertipe `struct readings`.

---

```cpp
xTaskCreate(read_data, "read sensors", 256, NULL, 1, NULL);
```
Membuat task `read_data` untuk membaca data sensor.

Penjelasan parameter:
- `read_data` → nama fungsi task
- `"read sensors"` → nama task
- `256` → ukuran stack memory
- `NULL` → parameter task
- `1` → prioritas task
- `NULL` → task handle

---

```cpp
xTaskCreate(display, "display", 256, NULL, 1, NULL);
```
Membuat task `display` untuk menampilkan data ke Serial Monitor.

---

```cpp
}
```
Penutup fungsi setup.

---

```cpp
void loop() {}
```
Fungsi loop dikosongkan karena semua proses dijalankan menggunakan task FreeRTOS.

---

# ================= TASK READ SENSOR =================

```cpp
void read_data(void *pvParameters) {
```
Membuat task untuk membaca data sensor DHT.

---

```cpp
struct readings x;
```
Membuat variabel `x` bertipe `struct readings` untuk menyimpan data sensor.

---

```cpp
for (;;) {
```
Perulangan tak hingga agar task berjalan terus-menerus.

---

```cpp
float humidity = dht.readHumidity();
```
Membaca nilai kelembaban dari sensor DHT.

```cpp
float temperature = dht.readTemperature();
```
Membaca nilai suhu dari sensor DHT dalam satuan Celsius.

---

```cpp
if (!isnan(humidity) && !isnan(temperature)) {
```
Memeriksa apakah data sensor valid dan bukan `NaN` (*Not a Number*).

---

```cpp
x.temp = temperature;
```
Menyimpan nilai suhu ke variabel struktur.

```cpp
x.h = humidity;
```
Menyimpan nilai kelembaban ke variabel struktur.

---

```cpp
xQueueSend(my_queue, &x, portMAX_DELAY);
```
Mengirim data sensor ke queue agar dapat diterima task lain.

Parameter:
- `my_queue` → queue tujuan
- `&x` → alamat data yang dikirim
- `portMAX_DELAY` → menunggu hingga queue tersedia

---

```cpp
} else {
```
Dijalankan jika pembacaan sensor gagal.

---

```cpp
Serial.println("Gagal membaca sensor DHT!");
```
Menampilkan pesan error pada Serial Monitor.

---

```cpp
vTaskDelay(pdMS_TO_TICKS(2000));
```
Memberikan delay 2000 ms tanpa menghentikan scheduler FreeRTOS.

---

```cpp
}
}
```
Penutup perulangan dan task `read_data`.

---

# ================= TASK DISPLAY =================

```cpp
void display(void *pvParameters) {
```
Membuat task untuk menampilkan data sensor.

---

```cpp
struct readings x;
```
Membuat variabel untuk menerima data dari queue.

---

```cpp
for (;;) {
```
Perulangan tak hingga agar task terus berjalan.

---

```cpp
if (xQueueReceive(my_queue, &x, portMAX_DELAY) == pdPASS) {
```
Menerima data dari queue.

Jika data berhasil diterima maka kondisi bernilai `pdPASS`.

---

```cpp
Serial.print("Temperatur = ");
```
Menampilkan teks “Temperatur = ”.

```cpp
Serial.print(x.temp, 1);
```
Menampilkan nilai suhu dengan 1 angka di belakang koma.

```cpp
Serial.println(" °C");
```
Menampilkan satuan Celsius.

---

```cpp
Serial.print("Kelembaban = ");
```
Menampilkan teks “Kelembaban = ”.

```cpp
Serial.print(x.h, 1);
```
Menampilkan nilai kelembaban dengan 1 angka di belakang koma.

```cpp
Serial.println(" %");
```
Menampilkan satuan persen.

---

```cpp
Serial.println("-------------------");
```
Menampilkan garis pemisah output pada Serial Monitor.

---

```cpp
}
}
```
Penutup kondisi, perulangan, dan task display.