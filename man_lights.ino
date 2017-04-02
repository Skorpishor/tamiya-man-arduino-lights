    

// Define Variables:
const int STEERING = 0;  
const int THROTTLE = 1;
const int AUX_TR   = 2;
const int AUX_ST  = 3;


const int BLINK_LEFT  = 4;
const int BLINK_RIGHT = 5;
const int BACK_DRIVE  = 6;
const int BRAKE_LIGHT = 7;
const int HIGH_BEAM = 8;
const int LOW_BEAM = 9;
const int PARK_LIGHT = 10;


int ch_STEERING;  //Varibles to store and display the values of each channel
int ch_THROTTLE;
int ch_AUX_TR;
int ch_AUX_ST;

unsigned long previousMilis =0;
int ledState = LOW;             // ledState used to set the LED

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  
  // Set input pins
  pinMode(STEERING, INPUT);
  pinMode(THROTTLE,INPUT);
  pinMode(AUX_TR,INPUT);
  pinMode(AUX_ST,INPUT);
  Serial.println("Start--");
unsigned long previousMillis = 0;        // will store last time LED was updated

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
  // read the input channels
  ch_STEERING = pulseIn (STEERING,HIGH);  //Read and store channel 1
  ch_THROTTLE = pulseIn (THROTTLE,HIGH);
  ch_AUX_TR = pulseIn (AUX_TR,HIGH);
  ch_AUX_ST = pulseIn (AUX_ST,HIGH);
  
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
 
/* 
 *  Blinker
 *  
 */
  if (ch_AUX_ST < 1300) 
  {
    Serial.println ("LEFT");
   // digitalWrite(BLINK_LEFT,HIGH);
   blink(BLINK_LEFT,1000);
  }
  else
  {
    digitalWrite(BLINK_LEFT,LOW);
    
  }
  if (ch_AUX_ST) 
  {
    Serial.println ("RIGHT");
    blink(BLINK_RIGHT,1000);
  }
  else
  {
    digitalWrite(BLINK_RIGHT,LOW);
  }
  
  // If we drive back we turn the white back LED on
  if (ch_THROTTLE > 1450) 
  {
    Serial.println ("WHITE LIGHT");
    blink(BACK_DRIVE,1000);
  }
  else
  {
    digitalWrite(BACK_DRIVE,LOW);
  } 
   

}

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
