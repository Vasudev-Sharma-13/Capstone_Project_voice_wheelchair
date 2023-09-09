#include <NewPing.h>
#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"
#include <AltSoftSerial.h>
VR myVR(2, 3);  // 2:RX 3:TX, you can choose your favourite pins.

uint8_t buf[64];

SoftwareSerial bluetooth(4, 5);  //for Bluetooth module RX FOLLOWD BY TX
NewPing sonar1(10, 11);
NewPing sonar2(12, 13);

String printSignature(uint8_t *buf, int len) {
  int i;
  String temp = "";
  for (i = 0; i < len; i++) {
    if (buf[i] > 0x19 && buf[i] < 0x7F) {

      temp = temp + char(buf[i]);
    }
  }
  return temp;
}

void setup() {

  pinMode(A4, OUTPUT);
  digitalWrite(A4, HIGH);

  myVR.begin(9600);
  Serial.begin(9600);
  myVR.load((uint8_t)0);
  myVR.load((uint8_t)1);
  myVR.load((uint8_t)2);
  myVR.load((uint8_t)3);
  myVR.load((uint8_t)4);
  myVR.load((uint8_t)5);
  myVR.load((uint8_t)6);

  bluetooth.begin(9600);
  pinMode(A2, OUTPUT);
  pinMode(A5, OUTPUT);
  digitalWrite(A2, HIGH);
  digitalWrite(A5, HIGH);


  pinMode(6, OUTPUT);  //LEFT motor
  pinMode(7, OUTPUT);  //LEFT motor

  pinMode(8, OUTPUT);  //RIGHT motor
  pinMode(9, OUTPUT);  //RIGHT motor

  pinMode(A0, OUTPUT);   //Right motor
  pinMode(A1, OUTPUT);   //Left motor
  analogWrite(A0, 255);  //Right motor speed PWM
  analogWrite(A1, 255);  //Left motor speed PWM
  pinMode(A2, OUTPUT);   //BLUETOOTH AT-MODE
}


String intake;  //global variable for inupt command
int flag = 0;   // flag
int ret;



void loop() {

  ultra();
  myVR.listen();
  ret = myVR.recognize(buf, 50);
  if (ret > 0) {
    intake = printSignature(buf + 4, buf[3]);
    Serial.println("Voice module said " + intake);

    intake.trim();
    intake.toUpperCase();
    if (intake == "BLUETOOTH") {
      BLUETOOTH();
    } else {
      Worker(intake);
    }
  }
}

void BLUETOOTH() {
  bluetooth.listen();
  while (true) {
    ultra();
    if (bluetooth.available() > 0) {
      intake = bluetooth.readString();
      intake.trim();
      Serial.println("This is the Bluetooth");
      intake.toUpperCase();
      if (intake == "VOICE") {
        break;
      } else {
        Worker(intake);
      }
    }
  }
}

void Worker(String one) {

  one.trim();
  one.toUpperCase();


  if (one.equals("FORWARD") == true) {
    forward();
    flag = 1;
    Serial.println("Moving Forward");
  } else if (one.equals("BACKWARD") == true) {
    backward();
    flag = 2;
    Serial.println("Moving Backward");

  } else if (one.equals("LEFT") == true) {
    left();
    flag = 3;
    Serial.println("Moving Left");
  } else if (one.equals("RIGHT") == true) {
    right();
    flag = 4;
    Serial.println("Moving Right");
  }

  else {
    Serial.println("Brake");
    brake();
    flag = 0;
  }
}

void ultra() {
  if (((sonar1.ping_cm() > 15) && (flag != 2)) || ((sonar2.ping_cm() > 15) && (flag == 2))) {
    if (flag == 1) {
      forward();
    } else if (flag == 2) {
      backward();
    } else if (flag == 3) {
      left();
    } else if (flag == 4) {
      right();
    }
  }

  else if (((sonar2.ping_cm() < 15) && (sonar2.ping_cm() != 0)) || ((sonar1.ping_cm() < 15) && (sonar1.ping_cm() != 0))) {
    brake();
    Serial.println(sonar2.ping_cm());
  }
}

void forward() {
  digitalWrite(7, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
}

void backward() {
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(8, LOW);
}

void right() {
  digitalWrite(7, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
}

void left() {
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
}

void brake() {
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
}
