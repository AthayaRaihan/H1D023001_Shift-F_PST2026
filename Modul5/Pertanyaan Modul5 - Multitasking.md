# 5.5.4 Pertanyaan Multitasking

## 1. Apakah ketiga task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!
Ketiga task pada program FreeRTOS berjalan secara concurrent, sehingga terlihat seperti berjalan secara bersamaan. Namun pada Arduino Uno yang hanya memiliki satu inti prosesor, task sebenarnya dijalankan secara bergantian dengan sangat cepat oleh scheduler FreeRTOS. Mekanisme ini dilakukan menggunakan pembagian waktu eksekusi (task switching) oleh scheduler. Ketika suatu task menjalankan vTaskDelay(), prosesor akan diberikan kepada task lain yang siap dijalankan. Oleh karena itu, TaskBlink1, TaskBlink2, dan Taskprint dapat berjalan secara concurrent sehingga LED dapat berkedip dengan interval berbeda sambil counter tetap tampil pada Serial Monitor. 
## 2. Bagaimana cara menambahkan task keempat? Jelaskan langkahnya! 
Untuk menambahkan task keempat pada FreeRTOS, langkah-langkah yang dilakukan adalah sebagai berikut:
1. Membuat deklarasi fungsi task baru, misalnya:
```cpp
void TaskBaru(void *pvParameters);
```
2. Menambahkan xTaskCreate() di dalam setup() untuk membuat task:
```cpp
xTaskCreate(
TaskBaru,
"task4",
128,
NULL,
1,
NULL );
```
3. Membuat isi fungsi task baru, contohnya:
```cpp
void TaskBaru(void *pvParameters)
{
  while(1)
  {
    Serial.println("Task4");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
```
## 3. Modifikasilah program dengan menambah sensor (misalnya potensiometer), lalu gunakan nilainya untukmengontrolkecepatan LED! Bagaimana hasilnya?

```cpp
#include <Arduino_FreeRTOS.h>

const int led1 = 8;
const int led2 = 9;
const int potPin = A0;

int delayLED = 200;

void TaskBlink1(void *pvParameters);
void TaskBlink2(void *pvParameters);
void TaskPotensiometer(void *pvParameters);

void setup() {

  Serial.begin(9600);

  xTaskCreate(
    TaskBlink1,     
    "Task1",        
    128,            
    NULL,           
    1,              
    NULL            
  );

  xTaskCreate(
    TaskBlink2,
    "Task2",
    128,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    TaskPotensiometer,
    "TaskPot",
    128,
    NULL,
    1,
    NULL
  );

  vTaskStartScheduler();
}

void loop() {}

void TaskBlink1(void *pvParameters) {

  pinMode(led1, OUTPUT);

  while (1) {
    Serial.println("Task LED 1");
    digitalWrite(led1, HIGH);
    vTaskDelay(delayLED / portTICK_PERIOD_MS);
    digitalWrite(led1, LOW);
    vTaskDelay(delayLED / portTICK_PERIOD_MS);
  }
}

void TaskBlink2(void *pvParameters) {

  pinMode(led2, OUTPUT);

  while (1) {
    Serial.println("Task LED 2");
    digitalWrite(led2, HIGH);
    vTaskDelay((delayLED + 100) / portTICK_PERIOD_MS);
    digitalWrite(led2, LOW);
    vTaskDelay((delayLED + 100) / portTICK_PERIOD_MS);
  }
}

void TaskPotensiometer(void *pvParameters) {
  while (1) {
    int nilaiPot = analogRead(potPin);

    delayLED = map(nilaiPot, 0, 1023, 100, 1000);

    Serial.print("Nilai Potensiometer : ");
    Serial.print(nilaiPot);
    Serial.print(" | Delay LED : ");
    Serial.println(delayLED);

    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}
```

# Penjelasan Program

- `#include <Arduino_FreeRTOS.h>`
  Digunakan untuk memanggil library FreeRTOS pada Arduino.

- `const int led1 = 8;`
  Mendeklarasikan pin LED pertama pada pin 8.

- `const int led2 = 9;`
  Mendeklarasikan pin LED kedua pada pin 9.

- `const int potPin = A0;`
  Mendeklarasikan pin analog A0 untuk potensiometer.

- `int delayLED = 200;`
  Variabel global untuk menyimpan delay kedipan LED.

- `void TaskBlink1(void *pvParameters);`
  Deklarasi fungsi task LED pertama.

- `void TaskBlink2(void *pvParameters);`
  Deklarasi fungsi task LED kedua.

- `void TaskPotensiometer(void *pvParameters);`
  Deklarasi fungsi task pembaca potensiometer.

- `Serial.begin(9600);`
  Memulai komunikasi serial dengan baud rate 9600 bps.

- `xTaskCreate(...)`
  Digunakan untuk membuat task baru pada FreeRTOS.

- `vTaskStartScheduler();`
  Menjalankan scheduler FreeRTOS agar semua task dapat berjalan.

- `void loop() {}`
  Dikosongkan karena program dijalankan oleh task FreeRTOS.

- `pinMode(led1, OUTPUT);`
  Mengatur pin LED sebagai output.

- `digitalWrite(led1, HIGH);`
  Menyalakan LED.

- `digitalWrite(led1, LOW);`
  Mematikan LED.

- `vTaskDelay(delayLED / portTICK_PERIOD_MS);`
  Memberikan delay tanpa menghentikan scheduler FreeRTOS.

- `analogRead(potPin);`
  Membaca nilai analog dari potensiometer.

- `map(nilaiPot, 0, 1023, 100, 1000);`
  Mengubah nilai ADC menjadi delay antara 100 ms sampai 1000 ms.

- `Serial.print()`
  Menampilkan data potensiometer dan delay LED ke Serial Monitor.