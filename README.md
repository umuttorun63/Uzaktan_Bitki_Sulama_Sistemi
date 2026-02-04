## Uzaktan_Bitki_Sulama_Sistemi
ESP8266 ve Blynk tabanlı, özel kesikli sulama algoritmasına ve aşırı sulama korumasına sahip IoT akıllı bitki sulama sistemi.

---

## 📌 Proje Özeti
Bu çalışmanın amacı, ev bitkilerinin bakımını otomatize etmek ve uzaktan yönetilebilir hale getirmektir. Proje, toprağın nemini sürekli analiz eder ve belirlediğimiz **"Kesikli Sulama Algoritması"** ile saksı taşmasını önleyerek sulama yapar. Ayrıca **"Islaklık Eşiği Koruması"** sayesinde aşırı sulamayı engeller.

---

## 🚀 Özellikler
* **IoT Desteği:** Blynk platformu üzerinden dünyanın her yerinden kontrol ve izleme.
* **Kesikli Sulama:** Motoru 1.5 sn çalıştırıp 10 sn bekleterek toprağın suyu emmesini sağlar.
* **Güvenlik Modu:** Toprak zaten ıslaksa manuel sulama isteğini reddeder.
* **Anlık Veri:** Mobil uygulama üzerinden canlı nem takibi.

---

## 🛠️ Donanım Listesi
* ESP8266 NodeMCU V3
* L9110 Çift Kanallı Motor Sürücü
* FC-28 Toprak Nem Sensörü
* Mini DC Dalgıç Su Pompası (3V-5V)
* 5V DC Adaptör / USB Kablo
* Jumper Kablolar
* Breadboard

---

## 💻 Kullanılan Yazılım ve Teknolojiler
Projenin geliştirilmesinde aşağıdaki yazılım ve kütüphaneler kullanılmıştır:
* **Geliştirme Ortamı:** Arduino IDE (C++ tabanlı)
* **IoT Platformu:** Blynk (Mobil Arayüz ve Bulut Sunucusu)
* **Kütüphaneler:**
    * `ESP8266WiFi.h` (Wi-Fi Bağlantısı için)
    * `BlynkSimpleEsp8266.h` (Blynk Haberleşmesi için)

---
     
 ## ⚙️ Sistem Çalışma Mantığı
 Sistem, toprağın nemini sürekli analiz ederek duruma göre karar veren akıllı bir yapıya sahiptir:

1.  **Kesikli Sulama (Smart Pulse Watering):** Motor sürekli çalışmak yerine **1.5 saniye aktif / 10 saniye pasif** döngüsüyle çalışır. Bu bekleme süresi, suyun toprağa süzülmesine izin verir ve saksı taşmasını önler.
2.  **Güvenlik (Islaklık) Koruması:** Eğer toprak nemi belirlenen eşiğin (Örn: 800 birim) üzerindeyse, kullanıcı manuel olarak sulama komutu gönderse bile sistem bitkiyi korumak için bu işlemi **otomatik olarak reddeder**.
3.  **Uzaktan Kontrol:** Kullanıcı, Blynk uygulaması üzerinden anlık nem değerini görebilir ve sistemi manuel olarak tetikleyebilir.

---

## 🔌 Devre Bağlantı Şeması
Projenin elektronik bağlantıları aşağıdaki şemaya sadık kalınarak yapılmıştır.

![Devre Şeması](docs/devre_semasi.png)

---

## 🏗️ Projenin Donanım Kurulumu
Aşağıda sistemin fiziksel olarak kurulmuş ve çalışmaya hazır hali görülmektedir:

![Donanım Kurulumu](img/proje_kurulum.jpg)

---

## 🧠 Algoritma Akış Diyagramı
Yazılımın karar verme mekanizması aşağıdaki akış diyagramında detaylandırılmıştır.

![Akış Diyagramı](docs/akis_diyagrami.png)

---

## 📊 Blynk Anlık Nem Takibi
Sistem, ölçülen analog nem verilerini işleyerek anlık olarak Blynk sunucularına iletir. Kullanıcı, mobil uygulama üzerinden bitkinin durumunu canlı olarak izleyebilir.

![Blynk Ekran Görüntüsü](img/blynk_screenshot.jpg)

---

## 🧑‍💻 Arduino IDE Üzerinden Nem Takibi
Sistemin kararlılığı ve sensör hassasiyeti, geliştirme aşamasında Seri Port Ekranı (Serial Monitor) üzerinden test edilmiştir. Aşağıdaki çıktılar, sistemin nem değişimlerine anlık tepki verdiğini göstermektedir.

![Serial Monitor](img/serial_monitor.png)
