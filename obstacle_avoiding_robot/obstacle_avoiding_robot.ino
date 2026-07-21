#include <Servo.h>    
#include <AFMotor.h>  
#include <NewPing.h>  

#define Trig A0 
#define Echo A1 
#define MaxDist 200 

#define SpeedMax 170 

NewPing sonar(Trig, Echo, MaxDist); 

AF_DCMotor motor1(3, MOTOR12_1KHZ); 
AF_DCMotor motor2(4, MOTOR12_1KHZ);
Servo myservo;   

boolean goesForward=false;
int distance = 100;
int speedSet = 0;

void setup() {

  myservo.attach(9);  
  myservo.write(115); 
  delay(2000); 
  

  for(int i=0; i<4; i++){
    distance = readPing();
    delay(100);
  }
}

void loop() {
 int distanceR = 0;
 int distanceL =  0;
 delay(40);
 
 if(distance <= 20) {
  moveStop();
  delay(200);
  moveBackward();
  delay(400);
  moveStop();
  delay(200);
  
  distanceR = lookRight();
  delay(300);
  distanceL = lookLeft();
  delay(300);

  if(distanceR >= distanceL) {
    turnRight();
    moveStop();
  } else {
    turnLeft();
    moveStop();
  }
 } else {
  moveForward();
 }
 distance = readPing();
}

int lookRight() {
    myservo.write(50); 
    delay(700); 
    int d = readPing();
    delay(100);
    myservo.write(115); 
    return d;
}

int lookLeft() {
    myservo.write(170); 
    delay(700); 
    int d = readPing();
    delay(100);
    myservo.write(115); 
    return d;
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm == 0) {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  goesForward = false;
} 
  
void moveForward() {
 if(!goesForward) {
    goesForward = true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);  
   
    for (speedSet = 0; speedSet < SpeedMax; speedSet += 2) {
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);
      delay(3);
    }
  }
}

void moveBackward() {
    goesForward = false;
    motor1.run(BACKWARD);      
    motor2.run(BACKWARD);
    for (speedSet = 0; speedSet < SpeedMax; speedSet += 2) {
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);
      delay(3);
    }
}  

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(BACKWARD);    
  delay(600); 
  motor1.run(FORWARD);      
  motor2.run(FORWARD);    
} 
 
void turnLeft() {
  motor1.run(BACKWARD);     
  motor2.run(FORWARD); 
  delay(600); 
  motor1.run(FORWARD);     
  motor2.run(FORWARD);
}
