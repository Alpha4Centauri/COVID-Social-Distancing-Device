/* Roneet Dhar's code for Social Distancing Arduino Device. This device utiilizes three sensors to obtain maximum accuracy in the detection of human presence. The three sensors are the ultrasonic proximity sensor,
   the mini PIR sensor, and the capacitive proximity sensor. The code is combined in this program. When the capacitive sensor detects an amplitude change, the PIR sensor will then check to see if there is any motion. 
   If there is motion, then it will say that motion has been detected and then it will go to the ultrasonic proximity sensor's code. The ultrasonic proximity sensor will analyze the time it takes for the ultrasonic waves 
   that hit the target it detects to reflect back to the receiver of the sensor. It will then use this to calculate the distance between the sensor and another person (it could be another object but the capacitive 
   sensor and the PIR sensor work together with the ultrasonic sensor to limit as many inaccuracies as possible). If the distance is less than 6 feet (this is the guideline that one should stay 6 feet away from another
   person to limit the spread of the virus), then it calls the buzzer sensor which produces a sound telling the user that he or she must distance themselves from the other person for safety. 
   
   */

#include <CapacitiveSensor.h> // This is the  function to call the capacitive library. This library has many built-in functions for capacitance. I will use one of the methods to set the sensitivity of the sensor below

// I need to initalize the pins to their set values. On the arduino board, there are digital pins. I use wires to connect the sensor to the board and plug them into the pins on the board. Each value is a pin on the board.

const int triggerPin = 10; // I initialize the trigger pin of the ultrasonic sensor which generates the trigger to pin number 10 on the arduino board.
const int echoPin = 9; // I initialize the echo pin which receives the ultrasonic waves to the 9th pin on the arduino baord.
const int buzzerPin = 6; // I initialize the buzzer pin which produces that sound to the 6th pin on the board.
 
 long Time; // I declare the long variable (long variables are datatypes used for number storage which is 32 bit) time. It will see the time it takes for the waves to return. I have just declared it, I will set a value later.
 int distance; // I declare an integer variable named distance. This will give the total distance between the object and the ultrasonic sensor.

/* It is very important to note that all arduino codes have two basic functions : void setup() and void loop(). Void setup() is where everything is "set up" and is assigned as INPUT or OUTPUT. This is also where one starts the 
serial communications between the board and the sensor. The code in the void setup() only runs once. The void loop() function is where the main code is written that will be repeated over and over again into a loop. 
This is where the main code is run. This is where the code for the sensors is run. To stop it from running, you have to unplug the usb cable which connects the code to the board.
*/
void setup(){

  pinMode(triggerPin, OUTPUT); // I call the pinMode function which sets the specific pin as INPUT or OUTPUT. I have set the trigger pin as OUTPUT since the trigger should be the output.
  pinMode(echoPin, INPUT); // I assign the echo pin of the ultrasonic sensor to be INPUT. It should be input since the echo pin receives the waves which have already been reflected back.
  Serial.begin(115200); // I start serial communications between the board and the sensors;

 
}

void loop() {

  CapacitiveSensor capacitiveProximitySensor = CapacitiveSensor(3,4); /* This is a very important object oriented programming concept. The object type is the CapacitiveSensor and then I name it. 
                                                                         I use a constructor which has (3,4) which are the pins on the arduino board in which the capacitive sensor is connected to. */

  long sensitivity = capacitiveProximitySensor.capacitiveSensor(80); // I declare a long variable named sensitivity. I assign it the value of the sensitivity of the sensor. The sensor's sensitivity is right now at 80.

  Serial.println(sensitivity);  // I print or display the sensitivity. It will show the waves and the amplitude. When something approaches the sensor, the amplitude will increase.

  if (sensitivity > 0) { // Here I use an if condition. I say that if the sensitivity is greater than 0 (which it will be unless there is no one around the vicinity), then it will have to detect motion which is the PIR's job.

    int PIR = 2; // I initialize the PIR sensor to the second pin on the board.

    pinMode(PIR, INPUT); // I make the PIR sensor as INPUT

    if((digitalRead(PIR) == HIGH)) // digitalRead is a function which tells whether the pin is HIGH (at 5 volts) or LOW (at 0 volts)
      {

        int motion = 1; // I assign the integer variable motion the value of 1 to indicate that the PIR sensor has detected motion.
        Serial.println("Motion was detected from the object sensed"); // I print on the terminal window / command prompt the fact that motion was sensed

        digitalWrite(triggerPin, LOW); /* I set the trigger pin of the ultrasonic senser as low assuming that it doesn't detect anything when it starts. I've coded this in a way so that the ultrasonic sensor code will only 
                                          execute if the capacitive proximity sensor detects an amplitude change and the PIR sensor detects motion. */

        delayMicroseconds(2); // I wait for two microseconds before turning on the trigger pin.

        digitalWrite(triggerPin, HIGH); // I turn on the trigger pin here
  
        delayMicroseconds(10); // I wait for 10 microseconds

        Time = pulseIn(echoPin, HIGH); /* I start the time the waves take to reach the object. I use the pulseIn function. The pulseIn function will measure the time period of the signal. The echo pin has a 
                                          high signal meaning that it is turned on. While the echo pin is on, the arduino will now start measuring the teime it takes for the waves to return back to the sensor. */

        distance = (0.0343 / 2)* Time; /* calculate the distance between the sensor and the object it detects. The mathematical formula for calculating distance is distance = rate * time. My rate is the speed of sound 
                                         (ultrasonic waves are sound waves). Sound travels at 343 meters per second. Since the pulseIn function measures in centimeters per microseconds, the rate is 0.043. 
                                          I divide the rate by two since ultrasonic waves will travel to the object it detects AND BACK. This will acount for double the rate. Therefore, I need to divide by 2. 
                                          I then multiply the rate by the time which is calculated through my Time variable to get the final distance. */

        // I print the distance in these next two lines
        Serial.print("The distance between you and what was detected is: "); 
        Serial.println(distance);

        if (distance <= 182.88) { // I know account for when the distance is less than 6 feet as that is the warning sign. Since my output distance will be in centimeters, I converted 6 feet into centimeters (6 feet = 182.88 cm)
          digitalWrite(buzzerPin, HIGH); // I set the buzzer pin to HIGH and turn it on to make that sound
          Serial.println("You are too close to the person. Distance yourself please!"); // I give the user a kind message to socially distance himself or herself from the person whom he or she is less than 6 feet apart from.
          }
      }
   }
}  

// This is the end of my code. I hoped you enjoyed it.
