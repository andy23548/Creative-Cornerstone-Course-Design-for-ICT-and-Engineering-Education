// dir = 0 : advance
// dir = 1 : left
// dir = 2 : right
// dir = 3 : back
int RL_time = 310;
void corner(int dir){
    digitalWrite(MotorRight1, LOW);  //dir == 0
    analogWrite(MotorRight2, 150);
    digitalWrite(MotorLeft1, LOW);
    analogWrite(MotorLeft2, 150);
    delay(230);
    if(dir == 1) {
       digitalWrite(MotorRight1, LOW);
       analogWrite(MotorRight2, 240);
       digitalWrite(MotorLeft1, HIGH);
       analogWrite(MotorLeft2, 0);
       delay(250);
    }
    else if(dir == 2) {
       digitalWrite(MotorRight1, HIGH);
       analogWrite(MotorRight2, 0);
       digitalWrite(MotorLeft1, LOW);
       analogWrite(MotorLeft2, 255);
       delay(245);
    }
    else if(dir == 3){
       digitalWrite(MotorRight1, HIGH);
       analogWrite(MotorRight2, 0);
       digitalWrite(MotorLeft1, LOW);
       analogWrite(MotorLeft2, 255);
       delay(500);
    }
    halt();
}


