/*
  This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
  It won't work with v1.x motor shields! Only for the v2's with built in PWM
  control

  For use with the Adafruit Motor Shield v2
  ---->	http://www.adafruit.com/products/1438
*/


#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"


void calcule_pas(void);
void programme_1(void);
void programme_BACKWARD_1(void);
const int buttonPin = 2;     // the number of the pushbutton pin
int buttonState = 0; // variables will change:
char uart_rd;


// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// stepper moteur connecté à #2 (M2 and M3)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(972, 2);


//----------------------------------------------------------------------
// initialize serial:
//----------------------------------------------------------------------
void setup() {

  Serial.begin(9600);
  Serial.println(" !!!!  Moteur pas à pas  !!!!");    // prints a tab
  Serial.println("intruire le numéro du programme");    // prints a tab
  Serial.println("1 => calcule_pas ");    // prints a tab
  Serial.println("2 => programme 1 ");    // prints a tab
  Serial.println("3 => programme_BACKWARD_1  ");    // prints a tab
  pinMode(buttonPin, INPUT);
  AFMS.begin();  // create with the default frequency 1.6KHz
  myMotor->setSpeed(255);  // vitesse à 10 tour par minutes
}


//----------------------------------------------------------------------
// main
//----------------------------------------------------------------------

void loop()

{

char lettre = 0;

  if(Serial.available()>0)
  {
    lettre = Serial.read();
    if(lettre == '1'){
    Serial.println(" !!!!  calcule_pas  !!!!");    // prints a tab
    calcule_pas();
    }
    else if (lettre == '2'){
    Serial.println(" !!!!  programme 1  !!!!");    // prints a tab
    programme_1();
    } 

    else if (lettre == '3'){
     Serial.println(" !!!!  programme_BACKWARD_1  !!!!");    // prints a tab
     programme_BACKWARD_1();
    } 

  }
  else
  {myMotor->step(0, BACKWARD, SINGLE);}


}






/**************************************************************************************************
*Envoyer une  variables d�cimale sur l'UART
**************************************************************************************************/

void ScanDecimal(int *t)
{
  while (1) {                     // Endless loop
    if (Serial.available()>0) {     // If data is received
      uart_rd = Serial.read();     // read the received data
      Serial.println(uart_rd);
  *t = uart_rd ;
      break;       // and send data via UART
    }
  }
  }


void calcule_pas()
{
  int cont = 0;
  
  while (digitalRead(buttonPin) == HIGH)
  {

    // read the state of the pushbutton value:

    myMotor->step(1, BACKWARD, DOUBLE);

    Serial.println(cont++, DEC);  // print as an ASCII-encoded decimal
  }
}
//-------------------------------------------------------------------------------------------------
void programme_1()

{



  while (digitalRead(buttonPin) == HIGH)
  {
    myMotor->step(10, BACKWARD, SINGLE);//1480
    // delay(3);
  }

  myMotor->step(0, BACKWARD, DOUBLE);
}
//-------------------------------------------------------------------------------------------------
void programme_BACKWARD_1()

{



  while (digitalRead(buttonPin) == HIGH)
  {
    myMotor->step(1485, BACKWARD, SINGLE);//1480
    break;
  }


}



