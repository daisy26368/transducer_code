#include <Servo.h> //include servo library

Servo LeftJaw;
Servo RightJaw;

// Eyes pins
int LeftEye = 5;
int RightEye = 6;

// Jaws pins
int LeftJawPin = 1;
int RightJawPin = 2;

int Echo = 4;
int Trigger = 3;

int Toggle = 0;

// The rotations of both jaws.
int JawSpin = 0;

void setup() {

    LeftJaw.attach(LeftJawPin);
    RightJaw.attach(RightJawPin);

    pinMode(LeftJawPin, OUTPUT);
    pinMode(RightJawPin, OUTPUT);

    pinMode(LeftEye, OUTPUT);
    pinMode(RightEye, OUTPUT);

    Serial.begin(9600);
}

// This a function, will be called on the loop function to turn the eyes on.
void TurnEyesOn() {
    digitalWrite(LeftEye, HIGH);
    digitalWrite(RightEye, HIGH);
}

// This a function, will be called on the loop function to turn the eyes off.
void TurnEyesOff() {
    digitalWrite(LeftEye, LOW);
    digitalWrite(RightEye, LOW);
}

// This a function, will be called on the loop function to make the jaws move.
void UpdateJaws(int rotation) {
    LeftJaw.write(rotation);
    RightJaw.write(rotation);
}


long microsecondsToInches(long microseconds)
{
    // According to Parallax's datasheet for the PING))), there are
    // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
    // second). This gives the distance travelled by the ping, outbound
    // and return, so we divide by 2 to get the distance of the obstacle.
    // See: http://www.parallax.com/dl/docs/prod/acc/28015-PI...
    return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
    // The speed of sound is 340 m/s or 29 microseconds per centimeter.
    // The ping travels out and back, so to find the distance of the
    // object we take half of the distance travelled.
    return microseconds / 29 / 2;
}


void loop() {

    // establish variables for duration of the ping,
    // and the distance result in inches and centimeters:
    long duration, inches, cm;

    // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    pinMode(Trigger, OUTPUT);
    digitalWrite(Trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(Trigger, HIGH);
    delayMicroseconds(5);
    digitalWrite(Trigger, LOW);

    // The same pin is used to read the signal from the PING))): a HIGH
    // pulse whose duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    pinMode(Echo, INPUT);
    duration = pulseIn(Echo, HIGH);

    // convert the time into a distance
    inches = microsecondsToInches(duration);
    cm = microsecondsToCentimeters(duration);

    delay(100);

    //if distance is greater than 10 inches
    if (inches > 10) {
        UpdateJaws(0);
    }

    //if distance is greater than 10 inches
    if (inches < 10 && inches > 4) {
        UpdateJaws(90);
    }

    //if distance is greater than 10 inches
    if (inches < 4) {
        UpdateJaws(180);
    }


}
