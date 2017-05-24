//Thisversion is writen for the Nano Arduino

// Define Variables:

// Input Chanels from RC receiver
const int STEERING = 2;  
const int THROTTLE = 3;
const int AUX_TR   = 4;
const int AUX_ST  = 5;

// Output chanels for the LED's

const int BACK_DRIVE  = 6;
const int BRAKE_LIGHT = 7;
const int HIGH_BEAM = 8;
const int LOW_BEAM = 9;
const int PARK_LIGHT = 10;
const int BLINK_LEFT  = 11;
const int BLINK_RIGHT = 12;

//Varibles to store and display the values of each channel
int ch_STEERING;  
int ch_THROTTLE;
int ch_AUX_TR;
int ch_AUX_ST;
// Aditional Variables and constants
unsigned long previousMilis =0;
int ledState = LOW;             // ledState used to set the LED
//Change the next values to values fiting for your RC Sender/receiver. Read them from the serial prints by defining the SERIAL_DEBUG
#define RC_LOW 1300 // the value of a chanel from where we consider that the RC sender stick is moved to links resp down
#define RC_HIGH 1450 // the value of a chanel from where we consider that the RC sender stick is moved to right resp up

#define SERIAL_DEBUG // comment/uncomment this define if you need/do not need the serial debug, for example to read the values from the RC chanell inputs


// the setup routine runs once when you press reset:
void setup() {
#ifdef SERIAL_DEBUG     
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
#endif  
  // Set input pins
  pinMode(STEERING, INPUT);
  pinMode(THROTTLE,INPUT);
  pinMode(AUX_TR,INPUT);
  pinMode(AUX_ST,INPUT);
  Serial.println("Start--");
    
unsigned long previousMillis = 0;        // will store last time LED was updated

// Set Output pins    
  pinMode(BLINK_LEFT,OUTPUT);
  pinMode(BLINK_RIGHT,OUTPUT);
  pinMode(BACK_DRIVE,OUTPUT);
  pinMode(BRAKE_LIGHT,OUTPUT);
  pinMode(HIGH_BEAM,OUTPUT);
  pinMode(LOW_BEAM,OUTPUT);
  pinMode(PARK_LIGHT,OUTPUT);
 
}

//Main Program
void loop() {
  /* read the input channels 
  * First I Utry to use the ugly slow method fron the built in functions
  * For time critical operation the fast lib should be used, see the articles from 
  * http://rcarduino.blogspot.de/2012/11/how-to-read-rc-channels-rcarduinofastlib.html
  */
  
    
  ch_STEERING = pulseIn (STEERING,HIGH);  //Read and store channel 1
  ch_THROTTLE = pulseIn (THROTTLE,HIGH);
  ch_AUX_TR = pulseIn (AUX_TR,HIGH);
  ch_AUX_ST = pulseIn (AUX_ST,HIGH);
  
#ifdef SERIAL_DEBUG    
  Serial.print ("STEERING:");  //Display text string on Serial Monitor to distinguish variables
  Serial.print (ch_STEERING);     //Print in the value of channel 1
  Serial.print ("|");
  Serial.print ("THROTTLE:");  //Display text string on Serial Monitor to distinguish variables
  Serial.print (ch_THROTTLE);     //Print in the value of channel 1
  Serial.print ("|");
  Serial.print ("AUX_TR:");  //Display text string on Serial Monitor to distinguish variables
  Serial.print (ch_AUX_TR);     //Print in the value of channel 1
  Serial.print ("|");
  Serial.print ("AUX_ST:");  //Display text string on Serial Monitor to distinguish variables
  Serial.print (ch_AUX_ST);     //Print in the value of channel 1
  Serial.print ("|");
  Serial.println("--");
 #endif
/* 
 *  Blinker
 *  
 */
  if (ch_AUX_ST < RC_LOW) 
  {
 #ifdef SERIAL_DEBUG     
    Serial.println ("LEFT BLINK");
 #endif     
    blink(BLINK_LEFT,1000);
      
  }
  else
  {
    digitalWrite(BLINK_LEFT,LOW);
    
  }
  if (ch_AUX_ST > RC_HIGH) 
  {
    Serial.println ("RIGHT");
    blink(BLINK_RIGHT,1000);
  }
  else
  {
    digitalWrite(BLINK_RIGHT,LOW);
  }
  
  if (ch_THROTTLE > RC_HIGH) 
  {
    Serial.println ("WHITE LIGHT");
    digitalWrite(HIGH_BEAM,HIGH);
  }
  else
  {
    digitalWrite(HIGH_BEAM,LOW);
  }   
  
  // If we drive back we turn the white back LED on
  if (ch_THROTTLE < RC_LOW) 
  {
    Serial.println ("Back LIGHT");
    digitalWrite(BACK_DRIVE,HIGH);
  }
  else
  {
    digitalWrite(BACK_DRIVE,LOW);
  }

}
// This function turn on off a LED for interval miliseconds (for example 1000 represents 1 second)
void blink(int port,long interval)
  {
      unsigned long currentMilis;
      currentMilis = millis();
      if (currentMilis - previousMilis >= interval)
      {
          
      //save last switch
          previousMilis = currentMilis;
      //switch the LED to oposite state as before
          if (ledState == LOW) {
            ledState = HIGH;
          } else {
            ledState = LOW;
          }
          // set the LED with the ledState of the variable:
          digitalWrite(port, ledState);
      }
  }  
