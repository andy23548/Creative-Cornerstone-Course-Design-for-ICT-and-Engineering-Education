#include<SoftwareSerial.h>

// TODO: Write the functions from what you learned in former labs.
void Tracing() {
   // Simple Tracking
   /*************************************************/
   /* Read the sensor value and determine wether to */
   /* turn left or turn right or go straight        */
   /*************************************************/

   //TODO
   // Initialize Senor value
   int r2 = digitalRead(R2);
   int r1 = digitalRead(R1);  // right-inner sensor
   int m = digitalRead(M); // middle sensor
   int l1 = digitalRead(L1); // left-inner sensor
   int l2 = digitalRead(L2);
//   Serial.println(r2);
//   Serial.println(r1);
//   Serial.println(m);
//   Serial.println(l1);
//   Serial.println(l2);

  
   //TODO
   // Using "MotorWriting()" to turn or go straight
   // depending on the sensors value
   
   
   // HIGH = when black road is sensed
   int high_number = 0;
   high_number = (r2 == HIGH) + (r1 == HIGH) + (m == HIGH) + (l1 == HIGH) + (l2 == HIGH); 
//   Serial.print("High_number : ");
//   Serial.println(high_number);
  if ((r2 == HIGH) && (r1 == LOW) && (m == LOW) && (l1 == LOW) && (l2 == LOW)) {  
    // big right turn
    MotorWriting(-100, 250);
  } else if ((r2 == HIGH) && (r1 == HIGH) && (m == LOW) && (l1 == LOW) && (l2 == LOW)) {
    // small right turn 
    MotorWriting(-50, 250);
  } else if ((r2 == LOW) && (r1 == HIGH) && (m == LOW) && (l1 == LOW) && (l2 == LOW)) {
    // small right turn 
    MotorWriting(50, 200);
  } else if ((r2 == LOW) && (r1 == HIGH) && (m == HIGH) && (l1 == LOW) && (l2 == LOW)) {
    // small right turn
    MotorWriting(100, 150);
  } else if ((r2 == LOW) && (r1 == LOW) && (m == HIGH) && (l1 == LOW) && (l2 == LOW)) {
    // center
    MotorWriting(100, 100);
  } else if ((r2 == LOW) && (r1 == LOW) && (m == HIGH) && (l1 == HIGH) && (l2 == LOW)) {
    // small left turn
    MotorWriting(150, 100);
  } else if ((r2 == LOW) && (r1 == LOW) && (m == LOW) && (l1 == HIGH) && (l2 == LOW)) {
    // small left turn
    MotorWriting(200, 50);
  } else if ((r2 == LOW) && (r1 == LOW) && (m == LOW) && (l1 == HIGH) && (l2 == HIGH)) {
    // small left turn
    MotorWriting(250, -50);
  } else if ((r2 == LOW) && (r1 == LOW) && (m == LOW) && (l1 == LOW) && (l2 == HIGH)) {
    // big left turn
    MotorWriting(250, -100);
  } else if ((r2 == LOW) && (r1 == LOW) && (m == LOW) && (l1 == LOW) && (l2 == LOW)) {
    MotorWriting(100, 100);
  } else if (high_number >= 3) {
      /**
       * Here is the place to meet the node !!!
       */
     // Send back to Python !!  
    if (true) {
        if (BT.available()) {
          BT.write('N');
        }
        Serial.print("Sent id: ");
        Serial.println('N');
     }
     if (_cmd == 'f') {
      // Advance !!
       Serial.print("_cmd: ");
       Serial.println(_cmd);
       MotorWriting(200, 200);
       delay(1000);
    } else if (_cmd == 'b') {
      // U-Turn
       Serial.print("_cmd: ");
       Serial.println(_cmd);
       MotorWriting(200, 200);
       delay(300);
       MotorWriting(200, -200);
       delay(700);
    } else if (_cmd == 'r') {
      // Turn right
       Serial.print("_cmd: ");
       Serial.println(_cmd);
       MotorWriting(200, 200);
       delay(300);
       MotorWriting(0, 200);
       delay(700);
    } else if (_cmd == 'l') {
      // Turn right
       Serial.print("_cmd: ");
       Serial.println(_cmd);
       MotorWriting(200, 200);
       delay(300);
       MotorWriting(200, 0);
       delay(700);
    } else if (_cmd == 'h') {
      // Halt
       Serial.print("_cmd: ");
       Serial.println(_cmd);
       MotorWriting(200, 200);
       delay(300);
       MotorWriting(0, 0);
       delay(1000);
    } else {
      /**
       * Testing only!!!!
       */
//      // Left turn
//      MotorWriting(200, 0);
//      delay(700);
  //    Serial.println("Invalid cmd!!!");
    }
  } else {    
    MotorWriting(-40, -40);
  }
    // don't know what to do; stop
//       delay(50);

}
