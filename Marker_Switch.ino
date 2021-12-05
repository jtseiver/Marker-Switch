
/**********************************************

MARKER LIGHT SWITCH - 48
2021 Terry Seiver
 
 Written for ATTiny85. This program will cycle between 
 each of the lighting modes for marker lights, when either 
 headlight or rearlight functions are turned on / off.

 The program assume the decoder is programmed to alternate
 between headlight and rearlight based on direction.

 The modes are:
    1) off (default)
    2) directional - both markers 
    3) both red

  ATTiny pins used:
  
                       +====+
     rearlight (PB5) 1 |*   | 8 Fn common (Vcc)
     headlight (PB3) 2 |    | 7 frnt rd mrkr (PB2)
  frnt wh mrkr (PB4) 3 |    | 6 rear wh mrkr (PB1)
                 Gnd 4 |    | 5 rear rd mrkr (PB0)
                       +====+
  
 
 **********************************************/

//global constants and variables
const int hlPin = 3; //headlight input
const int rlPin = 5; //rearlight input
const int fwmPin = 4; //front white marker
const int frmPin = 2; //front red marker
const int rwmPin = 1; //rear white marker
const int rrmPin = 0; //rear red marker

bool change = false;
int mode = 0; //lights off
int curDirection = 1; //direction either 1 forward, 2 reverse
int lastDirection = 1; //default last direction forward
int lightOn = 0; //either headlight or rearlight are on


void setup() {
  pinMode(hlPin, INPUT_PULLUP);
  pinMode(rlPin, INPUT_PULLUP);
  pinMode(fwmPin, OUTPUT);
  pinMode(frmPin, OUTPUT);
  pinMode(rwmPin, OUTPUT);
  pinMode(rrmPin, OUTPUT); 
  actionMode(); //set markers to be off on startup
}

void loop() {
  
  //determine direction
  int hlOn = digitalRead(hlPin);
  int rlOn = digitalRead(rlPin);  
  
  if (hlOn==LOW||rlOn==LOW) {  
    
    //if either headlight or rearlight are on
    
    if (hlOn==LOW) curDirection = 1; //forward
    if (rlOn==LOW) curDirection = 2; //reverse  
    
    //if direction has changed and mode is directional, then trigger a change
    if (curDirection!=lastDirection&&mode==2) change = true;  
    lastDirection = curDirection;

    //change mode
    if (lightOn==0) {
      if (mode < 3) {
        mode = mode + 1; 
      } else {
        mode = 1;
      }
      change = true;
    }
    lightOn = 1;
  } else 
  {
    //neither headlight or rearlight are on
    lightOn = 0;
  }

  //if there's a change, then set markers accordingly
  if (change==true) {
    actionMode();
  }
  delay(200);
 }

void actionMode(){ 
  //This function will change the LEDs based on the current mode
  switch (mode){
    case 1: //all markers off
      digitalWrite(fwmPin, LOW);
      digitalWrite(frmPin, LOW);
      digitalWrite(rwmPin, LOW);
      digitalWrite(rrmPin, LOW);
      break;
    case 2: //directional control
      if (curDirection==1) {  //ie forward
        digitalWrite(fwmPin, HIGH);
        digitalWrite(frmPin, LOW);
        digitalWrite(rwmPin, LOW);
        digitalWrite(rrmPin, HIGH);     
      } else { //ie reverse
        digitalWrite(fwmPin, LOW);
        digitalWrite(frmPin, HIGH);
        digitalWrite(rwmPin, HIGH);
        digitalWrite(rrmPin, LOW);
      }
      break;
    case 3: //Front and rear red markers on
        digitalWrite(fwmPin, LOW);
        digitalWrite(frmPin, HIGH);
        digitalWrite(rwmPin, LOW);
        digitalWrite(rrmPin, HIGH);
      break;
    default: //all markers off
      digitalWrite(fwmPin, LOW);
      digitalWrite(frmPin, LOW);
      digitalWrite(rwmPin, LOW);
      digitalWrite(rrmPin, LOW);
      break;
  }
  
 }
