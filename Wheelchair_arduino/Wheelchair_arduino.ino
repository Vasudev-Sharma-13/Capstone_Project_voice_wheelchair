# include <SoftwareSerial.h>
# include <NewPing.h>


SoftwareSerial bluetooth(2, 3); //for Bluetooth module

void setup() {
Serial.begin(9600);
bluetooth.begin(9600);  
pinMode(6, OUTPUT); //LEFT motor
pinMode(7, OUTPUT); //LEFT motor

pinMode(8, OUTPUT); //RIGHT motor
pinMode(9, OUTPUT); //RIGHT motor
 
pinMode(A0, OUTPUT);  //Right motor    
pinMode(A1, OUTPUT);  //Left motor      
analogWrite(A0,255);  //Right motor speed PWM
analogWrite(A1,255);  //Left motor speed PWM
}


String one; //global variable for inupt command
int flag=0; // flag

void loop() {

if(bluetooth.available()>0){

one  = bluetooth.readString();
one.trim();
one.toUpperCase();


if(one.equals("FORWARD")==true){
forward();
flag=1;
bluetooth.println("Forward_10");
}
else if(one.equals("BACKWARD")==true){
backward();
flag=2;  
bluetooth.println("Backward_10");

}
else if(one.equals("LEFT")==true){
left();
flag=3;
bluetooth.println("Left_10");
}
else if(one.equals("RIGHT")==true){
right();
flag=4;
bluetooth.println("Right_10");
}
else{
bluetooth.println("Brake_10");
brake();  
flag=0;
}
 
} //end of if containing serial.available()

/*
if((sonar1.ping_cm()>15)||((sonar2.ping_cm>15)&&(flag==2))){
  if(flag==1){
  forward();
  Serial.println("forward_1");
  }
  else if(flag==2){
  backward();
  Serial.println("backward_1");
  }
  else if(flag==3){
  left();
  Serial.println("left_1");
  }
  else if(flag==4){
  right();
  Serial.println("right_1");
  }
}

else{
  Serial.println(sonar.ping_cm()+" BRAKE");
  brake();
}
*/
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