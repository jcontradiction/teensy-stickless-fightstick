//
//stickless fightstick button layout (4 direction, 8 attack, 4 control)
//================================================================================================== 
//control buttons      : POSL3(L3-pin21)  POSR3(R3-pin20)  POSSL(Select-pin19)  POSST(Start-pin18)
//==================================================================================================        
//punch buttons top row: POSB8(X--pin9)   POSB7(Y-pin10)   POSB6(RB-pin11)      POSB5(LB-pin12)
//kick buttons btm row:  POSB1(A-pin17)   POSB2(B-pin16)   POSB3(RT-pin15)      POSB4(LT-pin14)
//================================================================================================== 
//
//direction buttons
//
//POSLT(pin7) POSDN(pin5) POSRT(pin8)
//            POSUP(pin6)
//
//Includes
#include <Bounce.h>
#include "xinput.h"

//General Declarations
#define MILLIDEBOUNCE 10  //Debounce time in milliseconds
#define NUMBUTTONS 16  //Number of all buttons
#define LED_DISABLED 0 //disable led, change to 1 to enable led

//Pin Declarations
#define pinDN 5  //up 
#define pinUP 6  //down 
#define pinLT 7  //left 
#define pinRT 8  //right 
#define pinB1 9  //light punch
#define pinB2 10  //medium punch
#define pinB3 11  //heavy punch
#define pinB4 12  //all 3 punches
#define pinOBLED 13  //Onboard LED pin
#define pinB5 14  //all 3 kicks
#define pinB6 15  //heavy kick
#define pinB7 16  //medium kick
#define pinB8 17  //light kick
#define pinST 18  //start
#define pinSL 19  //select
#define pinR3 20  //R3(Gamepad right stick press)
#define pinL3 21  //L3(Gamepad left stick press)

//Position of a button in the button status array
#define POSUP 0
#define POSDN 1
#define POSLT 2
#define POSRT 3
#define POSB1 4 
#define POSB2 5
#define POSB3 6
#define POSB4 7
#define POSB5 8
#define POSB6 9
#define POSB7 10
#define POSB8 11
#define POSST 12
#define POSSL 13
#define POSR3 14
#define POSL3 15

//Global Variables
byte buttonStatus[NUMBUTTONS];  //array Holds a "Snapshot" of the button status to parse and manipulate

//Setup Button Debouncing
Bounce joystickUP = Bounce(pinUP, MILLIDEBOUNCE);
Bounce joystickDOWN = Bounce(pinDN, MILLIDEBOUNCE);
Bounce joystickLEFT = Bounce(pinLT, MILLIDEBOUNCE);
Bounce joystickRIGHT = Bounce(pinRT, MILLIDEBOUNCE);
Bounce button1 = Bounce(pinB1, MILLIDEBOUNCE);
Bounce button2 = Bounce(pinB2, MILLIDEBOUNCE);
Bounce button3 = Bounce(pinB3, MILLIDEBOUNCE);
Bounce button4 = Bounce(pinB4, MILLIDEBOUNCE);
Bounce button5 = Bounce(pinB5, MILLIDEBOUNCE);
Bounce button6 = Bounce(pinB6, MILLIDEBOUNCE);
Bounce button7 = Bounce(pinB7, MILLIDEBOUNCE);
Bounce button8 = Bounce(pinB8, MILLIDEBOUNCE);
Bounce buttonSTART = Bounce(pinST, MILLIDEBOUNCE);
Bounce buttonSELECT = Bounce(pinSL, MILLIDEBOUNCE);
Bounce buttonL3 = Bounce(pinL3, MILLIDEBOUNCE);
Bounce buttonR3 = Bounce(pinR3, MILLIDEBOUNCE);

//Initiate the xinput class and setup the LED pin
XINPUT controller(LED_DISABLED, pinOBLED);

//void Configure Inputs and Outputs
void setupPins()
{
    //Configure the direction of the pins
    //All inputs with internal pullups enabled
    pinMode(pinUP, INPUT_PULLUP);
    pinMode(pinDN, INPUT_PULLUP);
    pinMode(pinLT, INPUT_PULLUP);
    pinMode(pinRT, INPUT_PULLUP);
    pinMode(pinB1, INPUT_PULLUP);
    pinMode(pinB2, INPUT_PULLUP);
    pinMode(pinB3, INPUT_PULLUP);
    pinMode(pinB4, INPUT_PULLUP);
    pinMode(pinB5, INPUT_PULLUP);
    pinMode(pinB6, INPUT_PULLUP);
    pinMode(pinB7, INPUT_PULLUP);
    pinMode(pinB8, INPUT_PULLUP);
    pinMode(pinST, INPUT_PULLUP);
    pinMode(pinSL, INPUT_PULLUP);
    pinMode(pinL3, INPUT_PULLUP);
    pinMode(pinR3, INPUT_PULLUP);   
    pinMode(pinOBLED, OUTPUT);  
    //Set the LED to low to make sure it is off
    digitalWrite(pinOBLED, LOW);
}

//Update the debounced button statuses
//We are looking for falling edges since the boards are built
//for common ground sticks
void buttonRead()
{
  if (joystickUP.update()) {buttonStatus[POSUP] = joystickUP.fallingEdge();}
  if (joystickDOWN.update()) {buttonStatus[POSDN] = joystickDOWN.fallingEdge();}
  if (joystickLEFT.update()) {buttonStatus[POSLT] = joystickLEFT.fallingEdge();}
  if (joystickRIGHT.update()) {buttonStatus[POSRT] = joystickRIGHT.fallingEdge();}
  if (button1.update()) {buttonStatus[POSB1] = button1.fallingEdge();}
  if (button2.update()) {buttonStatus[POSB2] = button2.fallingEdge();}
  if (button3.update()) {buttonStatus[POSB3] = button3.fallingEdge();}
  if (button4.update()) {buttonStatus[POSB4] = button4.fallingEdge();}
  if (button5.update()) {buttonStatus[POSB5] = button5.fallingEdge();}
  if (button6.update()) {buttonStatus[POSB6] = button6.fallingEdge();}
  if (button7.update()) {buttonStatus[POSB7] = button7.fallingEdge();}
  if (button8.update()) {buttonStatus[POSB8] = button8.fallingEdge();}
  if (buttonSTART.update()) {buttonStatus[POSST] = buttonSTART.fallingEdge();}
  if (buttonSELECT.update()) {buttonStatus[POSSL] = buttonSELECT.fallingEdge();}
  if (buttonL3.update()) {buttonStatus[POSL3] = buttonL3.fallingEdge();}
  if (buttonR3.update()) {buttonStatus[POSR3] = buttonR3.fallingEdge();}
}

//ProcessInputs

void processInputs()
{
  //Update the DPAD
  controller.dpadUpdate(buttonStatus[POSUP], buttonStatus[POSDN], buttonStatus[POSLT], buttonStatus[POSRT]);

  //XBOX LOGO
  if (buttonStatus[POSST]&&buttonStatus[POSSL]){controller.buttonUpdate(BUTTON_LOGO, 1);}
  else if (buttonStatus[POSST]){controller.buttonUpdate(BUTTON_START, 1);}
  else if (buttonStatus[POSSL]){controller.buttonUpdate(BUTTON_BACK, 1);}
  else {controller.buttonUpdate(BUTTON_LOGO, 0); controller.buttonUpdate(BUTTON_START, 0); controller.buttonUpdate(BUTTON_BACK, 0);}

  //Buttons
  if (buttonStatus[POSB8]) {controller.buttonUpdate(BUTTON_X, 1);} 
  else {controller.buttonUpdate(BUTTON_X, 0);}
  if (buttonStatus[POSB7]) {controller.buttonUpdate(BUTTON_Y, 1);} 
  else {controller.buttonUpdate(BUTTON_Y, 0);}
  if (buttonStatus[POSB6]) {controller.buttonUpdate(BUTTON_RB, 1);} 
  else {controller.buttonUpdate(BUTTON_RB, 0);}
  if (buttonStatus[POSB5]) {controller.buttonUpdate(BUTTON_LB, 1);} 
  else {controller.buttonUpdate(BUTTON_LB, 0);}
  if (buttonStatus[POSB1]) {controller.buttonUpdate(BUTTON_A, 1);} 
  else  {controller.buttonUpdate(BUTTON_A, 0);}
  if (buttonStatus[POSB2]) {controller.buttonUpdate(BUTTON_B, 1);} 
  else {controller.buttonUpdate(BUTTON_B, 0);}
  if (buttonStatus[POSL3]) {controller.buttonUpdate(BUTTON_L3, 1);}
  else {controller.buttonUpdate(BUTTON_L3, 0);}
  if (buttonStatus[POSR3]) {controller.buttonUpdate(BUTTON_R3, 1);}
  else {controller.buttonUpdate(BUTTON_R3, 0);}

  //Triggers
  uint8_t leftTrigger = 0;
  uint8_t rightTrigger = 0;
  if (buttonStatus[POSB4]) {leftTrigger = 0xFF;}  
  if (buttonStatus[POSB3]) {rightTrigger = 0xFF;} 
  controller.triggerUpdate(leftTrigger, rightTrigger);
}

//Setup
void setup() 
{
  setupPins();
}

void loop() 
{
  //Poll Buttons
  buttonRead();
  
  //Process all inputs and load up the usbData registers correctly
  processInputs();
  
  //Check for bootloader jump - press up, button1 and select all together to reboot Teensy
  if (buttonStatus[POSUP] & buttonStatus[POSB1] & buttonStatus[POSR3]) 
  {
    controller.bootloaderJump();
  }

  //Update the LED display
  controller.LEDUpdate();

  //Send data
  controller.sendXinput();

  //Receive data
  controller.receiveXinput();
}