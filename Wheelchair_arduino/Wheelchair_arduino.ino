# include <SoftwareSerial.h>
# include <NewPing.h>


SoftwareSerial bluetooth(4,5); //for Bluetooth module RX FOLLOWD BY TX

NewPing sonar1(10,11,100);
NewPing sonar2(12,13,100);

void setup() {
Serial.begin(9600);
bluetooth.begin(9600);  

pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
digitalWrite(2, HIGH);
digitalWrite(3, HIGH);



pinMode(6, OUTPUT); //LEFT motor
pinMode(7, OUTPUT); //LEFT motor

pinMode(8, OUTPUT); //RIGHT motor
pinMode(9, OUTPUT); //RIGHT motor
 
pinMode(A0, OUTPUT);  //Right motor    
pinMode(A1, OUTPUT);  //Left motor      
analogWrite(A0,255);  //Right motor speed PWM
analogWrite(A1,255);  //Left motor speed PWM
pinMode(A2,OUTPUT);  //BLUETOOTH AT-MODE
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
bluetooth.println("Moving Forward");
}
else if(one.equals("BACKWARD")==true){
backward();
flag=2;  
bluetooth.println("Moving Backward");

}
else if(one.equals("LEFT")==true){
left();
flag=3;
bluetooth.println("Moving Left");
}
else if(one.equals("RIGHT")==true){
right();
flag=4;
bluetooth.println("Moving Right");
}

else{
bluetooth.println("Brake");
brake();  
flag=0;
}
 
} //end of if containing serial.available()

if((sonar2.ping_cm()>15)&&(sonar1.ping_cm()>15)){
  if(flag==1){
  forward();
  }
  else if(flag==2){
  backward();
  }
  else if(flag==3){
  left();
  }
  else if(flag==4){
  right();
  }
}

else if((sonar2.ping_cm()<15)||(sonar1.ping_cm()<15)){
  brake();
}

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