//Thisversion is writen for the Nano Arduino

// define the debug output
#define SERIAL_DEBUG
#ifdef SERIAL_DEBUG
#define debugPrint(arg) Serial.print(arg)
#define debugPrintln(arg) Serial.println(arg)
#else
#define debugPrint(arg) doNothing(arg)
#define debugPrintln(arg) doNothing(arg)
#endif

// Define Variables:

boolean RIGHT_SET = false; // This variable mark if we RC signal to left is allready active, untill this will go true neutral 
boolean LEFT_SET =  false; // This variable mark if we RC signal to right is allready active, untill this will go true neutral
boolean LEFT_ON = false;  // The blinker to left is off
boolean RIGHT_ON = false; // The blinker to right is off

boolean HIGH_BEAM_ON  = false;      
boolean HIGH_BEAM_SET = false; 
boolean LOW_BEAM_ON  = false;      
boolean LOW_BEAM_SET = false; 



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
unsigned long currentMilis = 0;
static int ledState = LOW;             // ledState used to set the LED

//Change the next values to values fiting for your RC Sender/receiver. Read them from the serial prints by defining the SERIAL_DEBUG
#define RC_LOW 1300 // the value of a chanel from where we consider that the RC sender stick is moved to links resp down
#define RC_HIGH 1500 // the value of a chanel from where we consider that the RC sender stick is moved to right resp up
#define RC_OFFSET 100 // OFFSET for the RC

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
  debugPrintln("Start--");
    
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
  
  blinker()   ; 
  beams() ;
  ch_STEERING = pulseIn (STEERING,HIGH);  //Read and store channel 1
  ch_THROTTLE = pulseIn (THROTTLE,HIGH);
  

  if (RIGHT_ON == true) blink(BLINK_RIGHT,1000);
  if (LEFT_ON == true) blink(BLINK_LEFT,1000);  
  
  
 /*   
  debugPrint ("STEERING:");  //Display text string on Serial Monitor to distinguish variables
  debugPrint (ch_STEERING);     //Print in the value of channel 3
  debugPrint ("|");
  debugPrint ("THROTTLE:");  //Display text string on Serial Monitor to distinguish variables
  debugPrint (ch_THROTTLE);     //Print in the value of channel 1
  debugPrint ("|");
  debugPrint ("AUX_TR:");  //Display text string on Serial Monitor to distinguish variables
  debugPrint (ch_AUX_TR);     //Print in the value of channel 2
  debugPrint ("|");
  debugPrint ("AUX_ST:");  //Display text string on Serial Monitor to distinguish variables
  debugPrint (ch_AUX_ST);     //Print in the value of channel 4
  debugPrint ("|");
  debugPrintln("--");
*/

/*
// For the Forward on RC we do nothing (at least now)
  if (ch_THROTTLE > RC_HIGH) 
  {
    debugPrintln ("WHITE LIGHT");
    digitalWrite(HIGH_BEAM,HIGH);
  }
  else
  {
    digitalWrite(HIGH_BEAM,LOW);
  }
*/
     
  // If we drive back we turn the white back LED on
  if (ch_THROTTLE < RC_LOW) 
  {
    debugPrintln ("Back LIGHT");
    digitalWrite(BACK_DRIVE,HIGH);
  }
  else
  {
    digitalWrite(BACK_DRIVE,LOW);
  }

}  // end Loop()

// This function turn on off a LED for interval miliseconds (for example 1000 represents 1 second)
void blink(int port,long interval)
  {
//      unsigned long currentMilis;
      currentMilis = millis();
      debugPrintln(" =================================== ");    
      debugPrint("curent: "); debugPrint(currentMilis);   debugPrint(" prev: ");   debugPrint(previousMilis);
      debugPrint(" --- "); debugPrintln(currentMilis-previousMilis);   
      debugPrintln(" =================================== ");    
 
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

// Handler for the blinking
 /* 
 *  Blinker
 *  
 */
void blinker()
{ 
  ch_AUX_ST = pulseIn (AUX_ST,HIGH);
/*    debugPrint ("LEFT SET ");
    debugPrint (LEFT_SET); 
    debugPrint (" RIGHT SET ");
    debugPrintln (RIGHT_SET);      */
  if (ch_AUX_ST < RC_LOW) //RC AUX_ST is on LEFT
  {
    digitalWrite(BLINK_RIGHT,LOW);
    RIGHT_ON = false;
    if( LEFT_SET == false )
    {
      if(LEFT_ON == false)
      {
      blink(BLINK_LEFT,1000);
//        digitalWrite(BLINK_LEFT,HIGH);
        LEFT_ON = true;
      }
      else
      {
        digitalWrite(BLINK_LEFT,LOW);
        LEFT_ON = false;
      }
       LEFT_SET = true; 
    }
    debugPrintln ("LEFT BLINK ");

  }
  
  else // RC AUX_ST is on Neutral
  {
    LEFT_SET = false;
    
  }

  
    if (ch_AUX_ST > RC_HIGH) //RC AUX_ST is on RIGHT
    {
//      digitalWrite(BLINK_LEFT,LOW);
      LEFT_ON = false;
      if( RIGHT_SET == false )
      {
        if(RIGHT_ON == false)
        {
//          blink(BLINK_RIGHT,1000);
//          digitalWrite(BLINK_RIGHT,HIGH);
          RIGHT_ON = true;
        }
        else
        {
          digitalWrite(BLINK_RIGHT,LOW);
          RIGHT_ON = false;
        }
         RIGHT_SET = true; 
      }
      debugPrintln ("RIGHT BLINK ");
    }
    else // RC AUX_ST is on Neutral
    {
      RIGHT_SET = false;
      
    }
  }

void beams()
{ 
  ch_AUX_TR = pulseIn (AUX_TR,HIGH);
/*    
HIGH_BEAM,OUTPUT
LOW_BEAM,OUTPUT
PARK_LIGHT  
*/
  if (ch_AUX_TR < RC_LOW - RC_OFFSET) //RC AUX_TR is to front
  {
    
    LOW_BEAM_ON = false;
    if( HIGH_BEAM_SET == false )
    {
      if(HIGH_BEAM_ON == false)
      {

      digitalWrite(HIGH_BEAM,HIGH);
      digitalWrite(LOW_BEAM,HIGH);
      digitalWrite(PARK_LIGHT,HIGH);
      
        HIGH_BEAM_ON = true;
      }
      else
      {
        digitalWrite(HIGH_BEAM,LOW);
        digitalWrite(LOW_BEAM,LOW);
        digitalWrite(PARK_LIGHT,LOW);
        
        HIGH_BEAM_ON  = false;
      }
       HIGH_BEAM_SET = true; 
    }
    debugPrintln ("HIGH BEAM ");

  }
  
  else // RC AUX_TR is on Neutral
  {
    HIGH_BEAM_SET = false;
    
  }

  
    if (ch_AUX_TR > RC_HIGH + RC_OFFSET) //RC AUX_ST is on RIGHT
    {

      HIGH_BEAM_ON = false;
      if( LOW_BEAM_SET == false )
      {
        if(LOW_BEAM_ON == false)
        {
          digitalWrite(LOW_BEAM,HIGH);
          digitalWrite(PARK_LIGHT,HIGH);
          LOW_BEAM_ON = true;
        }
        else
        {
          digitalWrite(LOW_BEAM,LOW);
          digitalWrite(PARK_LIGHT,LOW);
          digitalWrite(HIGH_BEAM,LOW);
          LOW_BEAM_ON = false;
        }
         LOW_BEAM_SET = true; 
      }
      debugPrintln ("LOW BEAM ");
    }
    else // RC AUX_TR is on Neutral
    {
      LOW_BEAM_SET = false;
      
    }
  }  

  void doNothing(int)
  {
    //do Nothing
  }
// Program end
