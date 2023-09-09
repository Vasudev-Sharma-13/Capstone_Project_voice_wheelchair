void setup() {
  pinMode(6, OUTPUT);  //LEFT motor
  pinMode(7, OUTPUT);  //LEFT motor

  pinMode(8, OUTPUT);  //RIGHT motor
  pinMode(9, OUTPUT);  //RIGHT motor

  pinMode(A0, OUTPUT);   //Right motor
  pinMode(A1, OUTPUT);   //Left motor
  analogWrite(A0, 255);  //Right motor speed PWM
  analogWrite(A1, 255);  //Left motor speed PWM
}

void loop() {
  // put your main code here, to run repeatedly:
}


void forward(){
digitalWrite(7, HIGH);
digitalWrite(6, LOW);
digitalWrite(8, HIGH);
digitalWrite(9, LOW);
}

void backward(){
digitalWrite(6, HIGH);
digitalWrite(7, LOW);
digitalWrite(9, HIGH);
digitalWrite(8, LOW);
}

void right(){
digitalWrite(7, HIGH);
digitalWrite(6, LOW);
digitalWrite(8, LOW);
digitalWrite(9, LOW);

}

void left(){
digitalWrite(7, LOW);
digitalWrite(6, LOW);
digitalWrite(8, HIGH);
digitalWrite(9, LOW);

}

void brake(){
digitalWrite(7, LOW);
digitalWrite(6, LOW);
digitalWrite(8, LOW);
digitalWrite(9, LOW);

}