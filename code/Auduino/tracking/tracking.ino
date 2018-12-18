#define DEBUG
//#define BT_TEST

#ifdef BT_TEST
#include <SoftwareSerial.h>
SoftwareSerial BT(11, 10);   //bluetooth RX,TX
void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  Serial.println("Start!");
}
char c;
void loop() {
  BT.write('H');
  Serial.println("Message sent.");
  delay(1000);
  if(BT.available()) {
    c = BT.read();
    Serial.print("Received: ");
    Serial.println(c);
  }
  delay(1000);
}
#endif

#ifndef BT_TEST
#include <Wire.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>

// App Controller State
enum ControlState {
	START_STATE,
	TRACING_STATE,
	WAITING_STATE
};

#define RST_PIN      4        // RFID reset pin
#define SS_PIN       13       // RFID selection pin
#define RFID_SDA      9
#define RFID_SCK     13
#define RFID_MOSI    11
#define RFID_MISO    12

MFRC522 mfrc522(SS_PIN, RST_PIN);  // MFRC522 object declaration

// L298N 馬達驅動板
// 宣告 MotorR 為右邊
// 宣告 MotorL 為左邊
#define MotorRR_I3     4  //定義 I1 接腳
#define MotorRR_I4     5 //定義 I2 接腳
#define MotorLL_I1     6 //定義 I3 接腳
#define MotorLL_I2     7 //定義 I4 接腳
#define MotorR_PWMR    3  //定義 ENA (PWM調速) 接腳
#define MotorL_PWML    9  //定義 ENB (PWM調速) 接腳

// 循線模組
// observator : sitting in the back of the car
#define L2  A0  // Define Second Left Sensor Pin
#define L1  A1  // Define First Left Sensor Pin
#define M   A2  // Define Middle Sensor Pin
#define R1  A3  // Define First Right Sensor Pin
#define R2  A4  // Define Second Right Sensor Pin

SoftwareSerial BT(11, 10);   //bluetooth RX,TX

/*pin definition*/

/**************************************/
/*   Variables Define Here            */
/*   Initialized in setup() Funciton  */
/**************************************/
ControlState _state;               // Control State
double _Tp;                         // Velocity of Car
double _w2;                         // Weight Value for the Outer Sensor
double _w1;                         // Weight Value for the Inner Sensor
double _Kp;                         // _Kp Parameter
double _Kd;                         // _Kd Parameter
double _Ki;                         // _Ki Parameter
double _LastError;                  // Error in Last Stage
char   _cmd;                        // Command
//char   _final_project_cmd;          // Final project Command
double _integral;                   // Integral from Starting point
bool R_dir = true;                  // if dir == ture, mean right-motor is forwarding. On the other hand, backwarding.
bool L_dir = true;                  // if dir == ture, mean Left-motor is forwarding. On the other hand, backwarding.
int right_motor = 0;
int left_motor = 0;
int node_time = 0;

/**************************************/
/*   Function Prototypes Define Here  */
/**************************************/
void Start_State();
void Tracing_State();
void Waiting_State();
void MotorWriting(double vR, double vL);
void get_cmd(char& cmd);
bool Car_Turn(char cmd);
void MotorCheck();

/***************************/
/*   Functions Definition  */
/***************************/

void setup() {
	// Setting PINMode
  Serial.begin(9600);
  BT.begin(9600);  //bluetooth initialization
	pinMode(MotorRR_I3, OUTPUT);
	pinMode(MotorRR_I4, OUTPUT);
	pinMode(MotorLL_I1, OUTPUT);
	pinMode(MotorLL_I2, OUTPUT);
	pinMode(MotorR_PWMR, OUTPUT);
	pinMode(MotorL_PWML, OUTPUT);
	pinMode(R1, INPUT);
	pinMode(R2, INPUT);
	pinMode(M, INPUT);
	pinMode(L1, INPUT);
	pinMode(L2, INPUT);
	// Initialize Variables
	// You can Define you own value here.
	_state = START_STATE;      // Control State
	_cmd = 'n';                // Command
	_Tp = 130;              // Velocity of Car
	_w2 = 13.5;             // Second Stage Weight
	_w1 = _w2 / 2.0;          // First Stage Weight
	_Kp = 15;               // _Kp Parameter
	_Kd = 0.03;             // _Kd Parameter
	_Ki = 0.0;              // _Ki Parameter
	_LastError = 0;            // Error in Last Stage
	_integral = 0;
  #ifdef DEBUG
	Serial.println("Start!");
  #endif

	SPI.begin();         //RFID initialization
	mfrc522.PCD_Init();
	/*define your pin mode*/
}

#include "track.h"
#include "node.h"
#include "bluetooth.h"
#include "RFID.h"

void loop() {
	if (_state == START_STATE) Start_State();
	else if (_state == TRACING_STATE) Tracing_State();
  else if (_state == WAITING_STATE) Waiting_State();
  delay(200);  // I think it is needed to prevent bluetooth to unexpectedly fail.
}

void Start_State() {
	MotorWriting(0, 0);  // Stop the car.
  get_cmd(_cmd);  // Listen the command of BT.
  if (_cmd == 's') {
    // If command 's' is received, the car should change to Tracing State.
    _state = TRACING_STATE;
    #ifdef DEBUG
    Serial.println("Changing to Tracing State...");  // Print out the message about the state change.
    #endif
  }
}

void Tracing_State() {
  // The car do tracing generally.
  if (Tracing())	{
    // If the car sees the node, it should tell the computer and change to Waiting State.
    BT.write('N');
    _state = WAITING_STATE;
    #ifdef DEBUG
    Serial.println("The car has sent a message via bluetooth.");
    Serial.println("Changing to Waiting State...");  // Print out the message about the state change.
    #endif
  }
}

void Waiting_State() {
  MotorWriting(0, 0);  // Stop the car.
  get_cmd(_cmd);  // Listen the command of BT.
  if (_cmd != 'n') {
    // If a command is received, it is supposed to be the turning direction.
    // Perform the movement by given direction.
    #ifdef DEBUG
    Serial.println("A command received.");
    #endif
    if (Car_Turn(_cmd)) {
      _state = START_STATE;  // The car is stopped. Reset to the Start State.
      #ifdef DEBUG
      Serial.println("Changing to Start State...");  // Print out the message about the state change.
      #endif
    } else {
      _state = TRACING_STATE;
      #ifdef DEBUG
      Serial.println("Changing to Tracing State...");  // Print out the message about the state change.
      #endif
    }
  } else {
    #ifdef DEBUG
    Serial.println("No command received.");
    #endif
  }
}

void MotorWriting(double vR, double vL) {

	/*************************************************/
	/* Assign vR to right-motor and vL to left-motor */
	/*************************************************/
	if (vR >= 0) {
		R_dir = true;
		digitalWrite(MotorRR_I3, LOW);
		digitalWrite(MotorRR_I4, HIGH);
	}
	else if (vR < 0) {
		R_dir = false;
		digitalWrite(MotorRR_I3, HIGH);
		digitalWrite(MotorRR_I4, LOW);
		vR = -vR;
	}
	if (vL >= 0) {
		L_dir = true;
		digitalWrite(MotorLL_I1, LOW);
		digitalWrite(MotorLL_I2, HIGH);
	}
	else if (vL < 0) {
		L_dir = false;
		digitalWrite(MotorLL_I1, HIGH);
		digitalWrite(MotorLL_I2, LOW);
		vL = -vL;
	}
	analogWrite(MotorL_PWML, vL);
	analogWrite(MotorR_PWMR, vR);
}

void get_cmd(char &cmd) {
	delay(10); // Don't delete its!!

	/*************************************/
	/* Using BT object to get command */
	/* Assign value to cmd               */
	/*************************************/
  if (BT.available()) {
    // A command received. Just record the char what BT read.
    cmd = BT.read();
  }
  else {
    // No command received. Set a dummy command.
    cmd = 'n';
  }
  #ifdef DEBUG
  Serial.print("Cmd: ");
  Serial.println(cmd);  // Print out the command in debugging mode.
  #endif
}

// Its returned true value indicates if the car is stopped.
bool Car_Turn(char cmd) {
  bool returned_value = false;
  if (cmd == 'f') {
    // Advance
    MotorWriting(230, 200);
    delay(700);
  } else if (cmd == 'b') {
    // U-Turn
    MotorWriting(200, -200);
    delay(700);
  } else if (cmd == 'r') {
    // Turn right
    MotorWriting(0, 230);
    delay(700);
  } else if (cmd == 'l') {
    // Turn left
    MotorWriting(200, 0);
    delay(700);
  } else if (cmd == 'h') {
    // Halt
    MotorWriting(0, 0);
    returned_value = true;
  } else {
    #ifdef DEBUG
    Serial.println("Invalid car direction. Stop the car.");
    #endif
    MotorWriting(0, 0);
    returned_value = true;
  }
  return returned_value;
}

void MotorCheck() {
	// forward for 0.5s
	MotorWriting(200, 200);
	delay(500);
	// stop for 0.5s
	MotorWriting(0, 0);
	delay(500);
	// backward for 0.5s
	MotorWriting(-200, -200);
	delay(500);
	MotorWriting(0, 0);
	delay(500);
	MotorWriting(200, 0);
	delay(500);
	MotorWriting(0, 0);
	delay(500);
	MotorWriting(0, 200);
}
#endif
