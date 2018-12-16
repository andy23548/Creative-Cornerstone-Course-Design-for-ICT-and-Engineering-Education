#include<SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN      4        // 讀卡機的重置腳位
#define SS_PIN       13        // 晶片選擇腳位
MFRC522 mfrc522(SS_PIN, RST_PIN);  // 建立MFRC522物件
SoftwareSerial BT(8,7);   //RX,TX

int MotorRight1 = 3;
int MotorRight2 = 5;
int MotorLeft1 = 9;
int MotorLeft2 = 10;
const int SensorLeft = A2;
const int SensorMiddle = A1;
const int SensorRight = A0;

int SL;
int SM;
int SR;
bool cor = 0;
bool ed = 0;
bool _end = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(MotorRight1,   OUTPUT);
  pinMode(MotorRight2,   OUTPUT);
  pinMode(MotorLeft1,   OUTPUT);
  pinMode(MotorLeft2,   OUTPUT);
  Serial.println("Start!");
//    analogWrite(MotorR_PWMR, 255);
//    analogWrite(MotorL_PWML, 255); 
}

void loop() {
  // put your main code here, to run repeatedly:
    digitalWrite(MotorLeft1, LOW); 
    digitalWrite(MotorLeft2, HIGH);
    digitalWrite(MotorRight1, LOW); 
    digitalWrite(MotorRight2, HIGH);
    delay(3000);

}
