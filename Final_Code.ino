/***** Final Code ******/
/***** isme koi bhi bakchodi nhi karni hai *****/

#include <SoftwareSerial.h>
#include <Cytron_PS2Shield.h>
#include <Servo.h>

int jxpwm=0,jypwm=0;
int fpwm=0, bpwm =0, rpwm =0;
int triangle=0,cross=0,circle=0,sqr=0,right_1=0,right_2=0, up = 0;

const int servoPin = 13;
const int Base_PWM = 200;
const int Gear_PWM = 255;

/*** Defining Pins for Motors ****/

int PWM_right_wheel = 46;
int DIR_right_wheel = 50;

int PWM_left_wheel = 44;
int DIR_left_wheel = 42;

int PWM_front = 32;
int DIR_front = 34;

int PWM_back = 36;
int DIR_back = 38;

/*************** Setup *************/

void setup() {
  pinMode(PWM_right_wheel,OUTPUT);
  pinMode(DIR_right_wheel,OUTPUT);
  pinMode(PWM_left_wheel,OUTPUT);
  pinMode(DIR_left_wheel,OUTPUT);
  pinMode(PWM_front,OUTPUT);
  pinMode(DIR_front,OUTPUT);
  pinMode(PWM_back,OUTPUT);
  pinMode(DIR_back,OUTPUT);
}

/****CHASSIS CONTROLS FUNCTIONS****/

// move the bot in the forward direction (speed of all four ground motors become high)...
void forward() {
  analogWrite(PWM_right_wheel,200); // direction
  digitalWrite(DIR_right_wheel , LOW);
  analogWrite(PWM_left_wheel, 200); // direction
  digitalWrite(DIR_left_wheel , LOW);
}

// move the bot in the backward direction (speed of all four ground motors become high)...
void backward() {
  analogWrite(PWM_right_wheel, 200); // direction
  digitalWrite(DIR_right_wheel , HIGH);
  analogWrite(PWM_left_wheel, 200); // direction
  digitalWrite(DIR_left_wheel , HIGH);
}

// stop the body of the bot (speed of all four ground motors become zero)...
void stop_chassis() {
  analogWrite(PWM_right_wheel, 0); // direction
  analogWrite(PWM_left_wheel, 0); // direction
  analogWrite(PWM_front, 0); // direction
  analogWrite(PWM_back, 0); // direction
}

// move the right part of bot in the forward direction (speed of right two ground motors become low)...
void right_forward(){
  analogWrite(PWM_right_wheel, 200); // direction
  digitalWrite(DIR_right_wheel , LOW);
}

// move the right part of bot in the backward direction (speed of right two ground motors become high)...
void right_backward(){
  analogWrite(PWM_right_wheel, 200); // direction
  digitalWrite(DIR_right_wheel , HIGH);
}

// move the left part of bot in the forward direction (speed of right two ground motors become low)...
void left_forward(){
  analogWrite(PWM_left_wheel, 200); // direction
  digitalWrite(DIR_left_wheel , LOW);
}

// move the left part of bot in the backward direction (speed of right two ground motors become high)...
void left_backward(){
  analogWrite(PWM_left_wheel, 200); // direction
  digitalWrite(DIR_left_wheel , HIGH);
}

// Function for the left_turn of the bot...
void right_turn(){
  left_forward();
  right_backward();
}

// Function for the right_turn of the bot...
void left_turn(){
  left_backward();
  right_forward();
}

//
void front_upward() {
  analogWrite(PWM_front, 200); // direction
  digitalWrite(DIR_front , LOW);
}

// 
void front_downward () {
  analogWrite(PWM_front, 200); // direction
  digitalWrite(DIR_front , HIGH);
}

// 
void back_upward() {
  analogWrite(PWM_back, 200); // direction
  digitalWrite(DIR_back , HIGH);
}

//
void back_downward () {
  analogWrite(PWM_back, 200); // direction
  digitalWrite(DIR_back , LOW);
}

//
void chassis_up(){
  front_downward();
  back_downward();
}

// 
void chassis_down(){
  front_upward();
  back_upward();
}



void loop() {
  delay(10);
  Cytron_PS2Shield ps2;
  ps2.begin(9600);
  jxpwm = (ps2.readButton(PS2_JOYSTICK_RIGHT_X_AXIS)-128);
  jypwm = -(ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS)-128);

  jxpwm = map(jxpwm,-128,128, -Base_PWM, Base_PWM);
  jypwm = map(jypwm,-128,128, -Base_PWM, Base_PWM);

  jxpwm = constrain(jxpwm,-255,255);
  jypwm = constrain(jypwm,-255,255);
  
  fpwm = jypwm; 
  bpwm = jypwm;
  rpwm = jxpwm;
  
  triangle = 1-ps2.readButton(PS2_TRIANGLE);
  cross = 1-ps2.readButton(PS2_CROSS);
  circle = 1-ps2.readButton(PS2_CIRCLE);
   sqr = 1-ps2.readButton(PS2_SQUARE);
   right_1 = 1-ps2.readButton(PS2_RIGHT_1);
   right_2 = 1-ps2.readButton(PS2_RIGHT_2);
   up = 1-ps2.readButton(PS2_UP);

//test

// Gear Motor controlled by L1 L2 for front AND R1 and R2 for back motor  
  if(ps2.readButton(PS2_UP)==0){
    forward();
  }
  else if(ps2.readButton(PS2_DOWN)==0){
    backward();
  }
  else if(ps2.readButton(PS2_RIGHT)==0){
    right_turn();
  }
  else if(ps2.readButton(PS2_LEFT)==0){
    left_turn();
  }
  else if(ps2.readButton(PS2_LEFT_1)==0){
    front_upward();
  }
  else if(ps2.readButton(PS2_LEFT_2)==0){
    front_downward();
  }
  else if(ps2.readButton(PS2_RIGHT_1)==0){
    back_upward();
  }
  else if(ps2.readButton(PS2_RIGHT_2)==0){
    back_downward();
  }
  else if(ps2.readButton(PS2_JOYSTICK_LEFT)==0){
     chassis_down(); 
  }
  else if(ps2.readButton(PS2_JOYSTICK_RIGHT)==0){
     chassis_up();
  }
  
//// Servo motor controlled by Select button   32
// 
//// Forward and Backward motion of chasis  
//  else if(jypwm >20){
//    forward();
//    digitalWrite(LED, HIGH); 
//    delay(500);
//  } 
//  else if(jypwm < -20){
//    backward();
//    digitalWrite(LED, HIGH);
//  }
//  else if (rpwm > 20){
//    left_turn();
//    digitalWrite(LED, HIGH);
//  }
//  else if (rpwm < -20){
//    right_turn();
//    digitalWrite(LED, HIGH);
//  }
//  
////   else if(ps2.readButton(PS2_TRIANGLE)==0){
////    servoStart(); 
////    digitalWrite(LED, HIGH);
////  }

  else{
    stop_chassis();
  } 
}
