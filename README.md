# tamiya-man-arduino-lights
In Order to fire the lights for a MAN 18.540 from tamiya I use a arduine (nano) to "read" the RC receiver and turn on the LED's

First Configuration:
A 4 Chanel RC 

               Forward                                  --HIGH_BEAM--
                  ^                                             ^
                  |                                             |
              THROTTLE                                       AUX_TR
                  |                                             |
 Blink left  < - AUX_ST - > Blink Right      Steering    < - STEERING  - >  Steering
                  |                           left              |        right
                  |                                             |
                  v                                             v
         Brake/Backward                                 -- LOW_BEAM --
   - Light Backward (White LED)-
         - BRAKE_LIGHT - 
         
 Connect the ouputs of the receiver to the digital ports  STEERING, THROTTLE, AUX_TR and AUX_ST 
