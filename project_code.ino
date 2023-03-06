/* Kütüphane tanımları.*/
#include <IRremote.h>
#include <DHT.h>
/* Kumanda tuşları kodları.*/
#define IR_1 69
#define IR_2 70
#define IR_3 71
#define IR_4 68
#define IR_5 64
#define IR_6 67
#define IR_7 7
#define IR_8 21
#define IR_9 9
#define IR_yildiz 22
#define IR_0 25
#define IR_kare 13

#define IR_yukari 24
#define IR_sag 90
#define IR_sol 8
#define IR_asagi 82
#define IR_ok 28
#define IR_RECEIVE_PIN 3
/*----------------------------*/

/* Sensör ve Değişken tanımları*/
#define sensor_guc_kontrol_pini 4
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#define nem_sensor 2
#define led 6
float sicaklik_sensor = A5;
float sicaklik;
int komut;
int leddegeri = 255; /*ledin değeri 0-255 arasında olmalı. */
/*---------------------------*/


void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
  dht.begin();
  analogReference(INTERNAL);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  pinMode(sicaklik, INPUT);
  pinMode(nem_sensor, INPUT); /* Hata olursa burayı sil.*/
  pinMode(sensor_guc_kontrol_pini, OUTPUT);
  digitalWrite(sensor_guc_kontrol_pini, LOW);
}

void sensoroku() {
  digitalWrite(sensor_guc_kontrol_pini, HIGH);
  Serial.println(komut);

  for (int i = 1; i <= 5; i++) {
    /* Sensörleri okuma kodları*/
    float dhtnem = dht.readHumidity();
    float dhtsicaklik = dht.readTemperature();

    sicaklik = analogRead(sicaklik_sensor);
    sicaklik = ((sicaklik) / 9.31);
    /*--------------------------*/

    /* Yazdırma kodları*/
    Serial.println("----------------------");
    Serial.print("DHT11 Nem: % ");
    Serial.println(dhtnem);
    Serial.print("DHT11 Sicaklik: ");
    Serial.print(dhtsicaklik);
    Serial.println(" C");


    Serial.print("LM35 Sicaklik: ");
    Serial.print(sicaklik);
    Serial.println(" C");
    Serial.println("-----------------------");
    Serial.println(i);
    delay(1500);
    /*------------------*/
  }
  digitalWrite(sensor_guc_kontrol_pini, LOW);
  komut = 0;
}

void kumanda(){
  /*daha sonra düzenle. Kumanda komutları.*/

  if (komut == IR_1) {
    sensoroku();
  }

  if (komut == IR_yildiz) {
    leddegeri = 0;
    komut=0;
  }
  if(komut == IR_kare){
    leddegeri = 255;
    komut=0;
  }


    if (leddegeri < 255 && komut == IR_yukari) {
      leddegeri = leddegeri + 15;
      komut=0;
    }
    if (leddegeri > 0 && komut == IR_asagi) {
      leddegeri = leddegeri - 15;
      komut=0;
  }

}

void loop() {
  analogWrite(led, leddegeri);

  /* Kumanda kontrolleri*/
  if (IrReceiver.decode()) {
    IrReceiver.resume();
    komut = IrReceiver.decodedIRData.command;
    kumanda();
  }


  delay(100);

  /*---------------------*/



  /*Arduino Sensörlü Led Projesi - Seydi Ali İçlek. */
}
