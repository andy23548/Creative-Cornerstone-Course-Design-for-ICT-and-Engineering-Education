int count = 0;

void fix_tooLeft(){
    analogWrite(MotorRight1, 0);
    analogWrite(MotorRight2, 85);
    analogWrite(MotorLeft1, 0);
    analogWrite(MotorLeft2, 104);
}
void fix_tooRight(){
    analogWrite(MotorRight1, 0);
    analogWrite(MotorRight2,110);
    analogWrite(MotorLeft1, 0);
    analogWrite(MotorLeft2, 83);
}
void advance(){
    analogWrite(MotorRight1, 0);
    analogWrite(MotorRight2, 100);
    analogWrite(MotorLeft1, 0);
    analogWrite(MotorLeft2, 94);
}
void halt(){
    analogWrite(MotorRight1, 255);
    analogWrite(MotorRight2, 255);
    analogWrite(MotorLeft1, 255);
    analogWrite(MotorLeft2, 255);
}
bool track(int SL, int SM, int SR) {
    if (SM == HIGH) {
        if      (SR == LOW && SL == HIGH) { count = 0; fix_tooRight(); return 0;}
        else if (SR == HIGH && SL == LOW) { count = 0; fix_tooLeft(); return 0;}
        else if (SR == LOW && SL == LOW)  { count = 0; advance(); return 0;}
        else                              
        { 
          count++;
          if(count == 1)
          {
            count = 0;
            halt(); return 1;
          }
          return 0;
        }
    }
    else{
        count = 0;
        if      (SR == LOW && SL == HIGH) { fix_tooRight(); return 0;}
        else if (SR == HIGH && SL == LOW) { fix_tooLeft(); return 0;}
        else                              { halt(); return 0;}
    }
}
//delay(100);

