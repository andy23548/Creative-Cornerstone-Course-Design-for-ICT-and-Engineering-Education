#include<SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN      4        // RFID resetpin
#define SS_PIN       13        // RFID selection pin
MFRC522 mfrc522(SS_PIN, RST_PIN);  // MFRC522 object declaration
SoftwareSerial BT(8,7);   //bluetooth RX,TX

/*pin definition*/

void setup()
{
    BT.begin(9600); //bluetooth initialization
    
    SPI.begin();         //RFID initialization
    mfrc522.PCD_Init();

    /*define your pin mode*/
}

#include "track.h"
#include "node.h"
#include "bluetooth.h"
#include "RFID.h"

void loop()
{
    /*TODO*/
    
}
