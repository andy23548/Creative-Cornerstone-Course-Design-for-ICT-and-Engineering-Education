#include<SoftwareSerial.h>
int dir;
int ask_direction(){  
    while(1){
        if(BT.available()){
            char in = BT.read();
            switch (in)
            {
              case 'f':
                dir = 0;
                break;
              case 'l':
                dir = 1;
                break;
              case 'r':
                dir = 2;
                break;
              case 'b':
                dir = 3;
                break;
              case 'e':
                dir = -1;
                break;
            }
            return dir;
        }
    }
}

void send_byte(byte *id, byte idSize){
    BT.write(byte(1));
    for(int i = 0; i < idSize; i++){
        Serial.print(i);
        Serial.print("   ");
        //out[i] = id[i-1];
        BT.write(id[i]);
        Serial.println(id[i]);
    }
}

