#define BLYNK_TEMPLATE_ID "TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "AkıllısulamaSistemi"
#define BLYNK_AUTH_TOKEN "BLYNK_AUTH_TOKEN"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "WIFI_ADI";
char pass[] = "WIFI_SIFRESI";

const int sensorPin = A0;
const int motorPinA = D5;
const int motorPinB = D6;

int sulamaSuresi = 1500;
int beklemeSuresi = 10000;
int toplamTekrarSayisi = 5;
int ISLAK_ESIK = 800;
int nemDegeri = 0;
int kalanTekrar = 0;
bool islemSuruyor = false;
int tmrSulamaBitir = -1;
int tmrBeklemeBitir = -1;

BlynkTimer timer;

void yeniTurBaslat();
void turuBitirVeBekle();
void sulamaBaslat();
void sulamayiIptalEt();
void sensorOku();
bool nemYeterliMiVeDurdur();   

void motorIslemi(bool calistir) {
  if (calistir) {
    digitalWrite(motorPinA, HIGH);
    digitalWrite(motorPinB, LOW);
    Serial.println("MOTOR: Aktif (Su veriliyor...)");
  } else {
    digitalWrite(motorPinA, LOW);
    digitalWrite(motorPinB, LOW);
    Serial.println("MOTOR: Pasif (Bekleniyor/Durdu)");
  }
}

void sulamayiIptalEt() {
  islemSuruyor = false;
  kalanTekrar = 0;
  if (tmrSulamaBitir != -1) {
    timer.deleteTimer(tmrSulamaBitir);
    tmrSulamaBitir = -1;
  }
  if (tmrBeklemeBitir != -1) {
    timer.deleteTimer(tmrBeklemeBitir);
    tmrBeklemeBitir = -1;
  }
  motorIslemi(false);
  Serial.println("İPTAL: Kullanıcı elle durdurdu.");
}

bool nemYeterliMiVeDurdur() {
  int hamDeger = analogRead(sensorPin);
  int anlikNem = 1024 - hamDeger;
  if (anlikNem < 0) anlikNem = 0;
  nemDegeri = anlikNem;                 
  Blynk.virtualWrite(V1, nemDegeri);   
  if (nemDegeri >= ISLAK_ESIK) {
    Serial.println("OTOMATİK DUR: Nem eşiği aşıldı. Sulama iptal ediliyor.");
    Blynk.virtualWrite(V2, 0);
    sulamayiIptalEt();
    return true; 
  }
  return false; 
}

void yeniTurBaslat() {
  if (!islemSuruyor) return;
  if (nemYeterliMiVeDurdur()) return;
  Serial.println("DÖNGÜ: Yeni tur baslıyor -> Sulama...");
  motorIslemi(true);
  tmrSulamaBitir = timer.setTimeout((unsigned long)sulamaSuresi, turuBitirVeBekle);
}

void turuBitirVeBekle() {
  motorIslemi(false);
  if (!islemSuruyor) return;
  kalanTekrar--;
  Serial.print("DÖNGÜ: Tur bitti. Kalan tekrar: ");
  Serial.println(kalanTekrar);

  if (nemYeterliMiVeDurdur()) return;
  
  if (kalanTekrar > 0) {
    Serial.println("BEKLEME: Toprak emsin diye bekleniyor...");
    tmrBeklemeBitir = timer.setTimeout((unsigned long)beklemeSuresi, yeniTurBaslat);
  } else {
    islemSuruyor = false;
    Blynk.virtualWrite(V2, 0);
    Serial.println("BİTİŞ: Tüm sulama işlemi tamamlandı.");
  }
}

void sulamaBaslat() {
  if (islemSuruyor) return;
  if (nemYeterliMiVeDurdur()) return;
  islemSuruyor = true;
  kalanTekrar = toplamTekrarSayisi;
  Serial.println("BAŞLAT: Sulama rutini tetiklendi.");
  motorIslemi(true);
  tmrSulamaBitir = timer.setTimeout((unsigned long)sulamaSuresi, turuBitirVeBekle);
}

BLYNK_WRITE(V2) {
  int butonBasildi = param.asInt();
  if (butonBasildi == 1) {
    sulamaBaslat();
  } else {
    sulamayiIptalEt();
  }
}

void sensorOku() {
  int hamDeger = analogRead(sensorPin);
  nemDegeri = 1024 - hamDeger;
  if (nemDegeri < 0) nemDegeri = 0;
  Blynk.virtualWrite(V1, nemDegeri);
  Serial.print("Anlık Nem: ");
  Serial.println(nemDegeri);
}

void setup() {
  Serial.begin(115200);
  pinMode(motorPinA, OUTPUT);
  pinMode(motorPinB, OUTPUT);
  pinMode(sensorPin, INPUT);
  motorIslemi(false);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, sensorOku);
}

void loop() {
  Blynk.run();
  timer.run();
}
