#include <LiquidCrystal_I2C.h>//16x2 LCD Ekran kütüphanemizi yazılımımıza dahil ediyoruz.
LiquidCrystal_I2C lcd(0x27,16,2);//Kullanılan Ekran Türünün 0x27 olduğunu sisteme tanımlıyoruz.
#include <Wire.h>
#include "Adafruit_MCP9808.h"
const int Enable_A = 10; // Panel soğutma sisteminin bağlantıları
const int inputA1 = 3;
const int inputA2 = 5;

const int Enable_B = 11; // Tarla sulama sisteminin bağlantıları
const int inputB1 = 6;
const int inputB2 = 9;

int TnemValue=0; // Topraktan alınan nemin analog degeri (0-1023)
int YuzdeNem=0; // Topraktan alınan nemin yuzdelik degeri (0-100)

Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();// Sıcaklık sensoru kutuphanesini sisteme tanımladık.
void setup() 
{
  Serial.begin(9600); // Seri haberleşmeyi 9600 bandında başlattık.
  lcd.begin(); // lcd ekranı aktifleştirdik.
  Serial.println("MCP9808 started");// Serial ekrana MCP9808 sıcaklık sensörünün başlatıldığı mesajını yazdırdık.
  
  pinMode(Enable_A, OUTPUT);// Panel soğutma sisteminin pinlerini çıktı olarak tanımladık.
  pinMode(inputA1, OUTPUT); // Panel soğutma sisteminin pinlerini çıktı olarak tanımladık.
  pinMode(inputA2, OUTPUT); // Panel soğutma sisteminin pinlerini çıktı olarak tanımladık.
  
  pinMode(Enable_B, OUTPUT);  // Tarla sulama sistemipinlerini çıktı olarak tanımladık.
  pinMode(inputB1, OUTPUT);  // Tarla sulama sistemipinlerini çıktı olarak tanımladık.
  pinMode(inputB2, OUTPUT); // Tarla sulama sistemipinlerini çıktı olarak tanımladık.
  

  if (!tempsensor.begin()) { // Eğer sıcaklık sensörü aktive edilemezse Serial Habeleşme paneline "Başarız bağlantı" uyarısısı verecek
    Serial.println("Basarisiz Baglanti!");
    while (1);
  }
}

void loop() {
  TnemValue = analogRead(A3 ); //Toprak sensöründen alınan veriyi Arduino'ya A0 pininden iletilecek.
  YuzdeNem=map(TnemValue,1023,0,100,0); // Topraktan alınan veriyi(0-1023) yüzdelik değere dönüştürüyoruz.
  //Serial.println(9600);
  float c = tempsensor.readTempC(); // Topraktan alınan veriyi Celcius formatına dönüştemek için tanımlama yapıldı.
  float f = c * 9.0 / 5.0 + 32; // Celcius formatı için fonksiyon tanımlandı.

 // Serial Ekrana yansıtılan veriler
 Serial.print("Temp: "); Serial.print(c); Serial.print("*C\t"); 
 Serial.print(f); Serial.println("*F");
 Serial.println(TnemValue);
 lcd.setCursor(0,0);// Lcd ekranın 0. satırının 0. sütununa
 lcd.print("PANELIN SICAKLIGI"); // "PANELIN SICAKLIĞI" yazıldı.
 lcd.setCursor(0,1); // Lcd Ekranın 1.satırının 0.sütuna 
 lcd.print("      ");
 lcd.setCursor(10,1);
 lcd.print(     c); // Sıcaklık verisi yazıldı.
 delay(2000); // 2 saniye bekleme süresi
  
 lcd.clear(); // Lcd ekrandaki veriler silinecek ve 2. bilgilendirici metine hazır hale getirilecektir.
 lcd.noBacklight(); 
 delay(1000);
 lcd.backlight(); 
 lcd.setCursor(0,0); // Lcd ekranın 0. satırının 0. sütununa
 lcd.print("SUSUZLUK ORANI");// "SUSUZLUK ORANI" yazıldı.
 lcd.setCursor(0,1);
 lcd.print("      %");
 lcd.print(    YuzdeNem); // Sıcaklık verisi yazıldı.
 delay(3000);
 lcd.clear();
 
   if(c>25 )// Eğer ölçülen sıcaklık 25 dereceden büyük olursa Panel soğutma motoru çalıştırılacak.
  {
  digitalWrite(inputA1,LOW);
  digitalWrite(inputA2,HIGH);
  analogWrite(Enable_A,250);
  }
  else if(c<22)
  {
  digitalWrite(inputA1,LOW);
  digitalWrite(inputA2,HIGH);
  analogWrite(Enable_A,0);
  }
  delay(1);
  if(TnemValue>=500 && TnemValue<=1200)// Eğer ölçülen toprak nem değeri belirlenen aralıkta olursa Tarla sulama motoru çalıştırılacak.
  {
  digitalWrite(inputB1,LOW);
  digitalWrite(inputB2,HIGH);
  analogWrite(Enable_B,250);
  }
  else if(TnemValue<=490)
  {
  digitalWrite(inputB1,LOW);
  digitalWrite(inputB2,HIGH);
  analogWrite(Enable_B,0);
  }
}
