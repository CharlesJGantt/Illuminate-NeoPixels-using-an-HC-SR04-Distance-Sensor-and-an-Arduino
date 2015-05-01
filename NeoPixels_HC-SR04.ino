// Turning NeoPixels on and off using a HC-SRO4 Ping Sensor

/*

   This sketch reads a HC-SR04 ultrasonic rangefinder and returns the

   distance to the closest object in range. To do this, it sends a pulse

   to the sensor to initiate a reading, then listens for a pulse 

   to return.  The length of the returning pulse is proportional to 

   the distance of the object from the sensor.


   The Arduino then takes this information and illuminates a strip of 
   NeoPixel's based on the distance of the object from the sensor. 

   This code was developed partially from Ping))) code found in the public domain
   written by David A. Mellis, and adapted to the HC-SRO4 by Tautvidas Sipavicius, 
   while other portions were written by Charles Gantt and Curtis Gauger from
   http://www.themakersworkbench.com. 
 */

 //Tell the Arduino IDE to include the FastLED library
 #include <FastLED.h>
 
 //Setup the variables for the HC-SR04
const int trigPin = 8;
const int echoPin = 7;

//Setup the variables for the NeoPixel Strip
#define NUM_LEDS 7 // How many leds in your strip?
#define DATA_PIN 6 // What pin is the NeoPixel's data line connected to?
CRGB leds[NUM_LEDS]; // Define the array of leds
 
void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}
 
void loop()
{
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, inches, cm;
 
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
   if (inches <= 20)  {fill_solid( &(leds[0]), NUM_LEDS /*number of leds*/, CRGB::Blue); //{whitestrobe(30);
     FastLED.show();
   
}
  else if (inches >= 21) {fill_solid( &(leds[0]), NUM_LEDS /*number of leds*/, CRGB::Black);
     FastLED.show();
  }
  
  delay(100);
}
 
long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}
 
long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
