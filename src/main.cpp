#include <QTRSensors.h>
#include <Servo.h>

QTRSensorsRC qtr((unsigned char[]) {8, 9, 10}, 3);
Servo myservoright;
Servo myservoleft;

void setup()
{
        for (int i = 0; i < 250; i++) // calibration, take about 5 seconds
        {
                qtr.calibrate();
                delay(20);
        }

        myservoright.attach(5); // attach right servo to pin 5
        myservoleft.attach(6); // attach left servo to pin 6
}

void loop()
{
        unsigned int sensors[3];

        qtr.readLine(sensors); // read sensor

        if (sensors[0] > 750 && sensors[1] > 750 && sensors[2] > 750) // stop robot while all of the sensors are over the black line, or sensor is more than 6mm above the ground
        {
                myservoright.write(90);
                myservoleft.write(90);
                delay(15);
                return;
        }
        if (sensors[0] < 100 && sensors[1] < 100 && sensors[2] < 100) // stop robot while all of the sensors are over the reflective region, this means tha robot might have lost the track
        {
                myservoright.write(90);
                myservoleft.write(90);
                delay(15);
                return;
        }

        int right = sensors[0] + sensors[1];
        int left = sensors[1] + sensors[2];

        if (right > 1500) // the line is on the right
        {
                myservoright.write(87); // turn right
                myservoleft.write(110);
                delay(50);
        }
        if (left > 1500) // the line is on the left
        {
                myservoright.write(70); // turn left
                myservoleft.write(93);
                delay(50);
        }
}