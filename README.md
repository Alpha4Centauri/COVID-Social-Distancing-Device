This device utiilizes three sensors to obtain maximum accuracy in the detection of human presence. The three sensors are the ultrasonic proximity sensor, the mini PIR sensor, and the capacitive proximity sensor. The code is combined in this program. When the capacitive sensor detects an amplitude change, the PIR sensor will then check to see if there is any motion. If there is motion, then it will say that motion has been detected and then it will go to the ultrasonic proximity sensor's code. The ultrasonic proximity sensor will analyze the time it takes for the ultrasonic waves that hit the target it detects to reflect back to the receiver of the sensor. It will then use this to calculate the distance between the sensor and another person (it could be another object but the capacitive sensor and the PIR sensor work together with the ultrasonic sensor to limit as many inaccuracies as possible). If the distance is less than 6 feet (this is the guideline that one should stay 6 feet away from another person to limit the spread of the virus), then it calls the buzzer sensor which produces a sound telling the user that he or she must distance themselves from the other person for safety. 