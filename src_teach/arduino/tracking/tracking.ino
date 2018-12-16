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

void setup()
{
    Serial.begin(9600);
    Serial.println("hello world");
    BT.begin(9600);
    // 
    pinMode(MotorRight1, OUTPUT);
    pinMode(MotorRight2, OUTPUT);
    pinMode(MotorLeft1, OUTPUT);
    pinMode(MotorLeft2, OUTPUT);

    // 
    pinMode(SensorRight, INPUT);
    pinMode(SensorMiddle, INPUT);
    pinMode(SensorLeft, INPUT);

    SPI.begin();
    mfrc522.PCD_Init();

    while(1)
    {
        if(BT.available())
        {
            char start = BT.read();
            if(start == 's') break;
        }
    }
}
#include "track.h"
#include "corner.h"
#include "bluetooth.h"
#include "RFID.h"
void loop()
{
    if(_end) //end signal
      return;
    
    SL = digitalRead(SensorLeft);   //infrared sensor
    SM = digitalRead(SensorMiddle);
    SR = digitalRead(SensorRight);
    
    Serial.print(SL);
    Serial.print(',');
    Serial.print(SM);
    Serial.print(',');
    Serial.print(SR);
    Serial.print(',');
    Serial.print(ed);
    Serial.print(',');
    Serial.print(cor);
    Serial.print('\n');
    
    if (ed == 0 && cor == 0) cor = track(SL, SM, SR); //tracking
    else if (ed == 0 && cor == 1) { //corner detected
        byte idSize = 0;
        byte* id;
        *id = 0;
        id = rfid(&idSize); //read rfid
        delay(500);
        send_byte(id,idSize);
        int dir = ask_direction();
        if(dir == -1) //end signal
        {
          _end = 1;
          return;
        }
        corner(dir); ed = 1; cor = 0;
    }
    
    else if(ed == 1 && cor == 0) { //advance for little distance
        advance();
        delay(10);
        //cor = track(SL, SM, SR); //until the exit of the corner
        cor = 1;
    }
    else if(ed == 1 && cor == 1){ //
        advance();
        delay(200);
        halt();
        cor = 0; ed = 0;
    }
}

