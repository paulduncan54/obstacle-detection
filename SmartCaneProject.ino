#include <Servo.h>
//#include <UnoWiFiDevEd.h>
//#include <GoogleMapsApi.h>
#define trigPin 11
#define echoPin 12
#define servoPin 9
#define  buzzer 8

#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_C5 523

int pot = A0, servoPosition = 0, potstate, interval = 1000, angle = 20;
unsigned long previousTime = 0, currentTime = 20;
long duration, distance;


Servo myservo;

void setup()
{ 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin,  INPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(pot, INPUT);
  myservo.attach(servoPin);
  myservo.write(servoPosition);
  Serial.begin(9600);
}

int rotateServo(){
  // Get the current time in milliseconds
  unsigned long currentTime = millis();
  // Check if the interval has elapsed
  if (currentTime - previousTime >= interval) {
    // Update the previous time variable
    previousTime = currentTime;
    // Increment the servo position by the angle
    servoPosition += angle;
    // Wrap the servo position if it exceeds 180 degrees
    if (servoPosition > 180) {
      servoPosition -= 180;
    }
    // Write the servo position
    myservo.write(servoPosition);
    return angle;
  }
}

long measureDistance()
{
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin,  LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034/2;

  return distance;
}





void loop()
{  
  distance = measureDistance();
  Serial.println(distance);
  delay(700);

  if (distance < 20) // Checking the distance, you can change the value
  { 
  digitalWrite(servoPin,HIGH);  // When the the distance below 100cm
  digitalWrite(buzzer,HIGH);
  tone(buzzer, NOTE_C4, 500);
  delay(200);
  rotateServo();  
  } else
  {
  digitalWrite(servoPin,LOW);//  when greater than 100cm
  digitalWrite(buzzer,LOW); 
  }

} 




