#include <Arduino.h>

//#define OFF 0
//#define ON 1
//#define PIN_SENSOR A0
//#define PIN_CLICK 2
//#define PIN_STATE 12

#define OFF 0
#define ON 1
#define PIN_SENSOR A3
#define PIN_CLICK A4
#define PIN_STATE 3
#define PIN_LED_CLICK A1
#define PIN_LED_THRESH A2

int blackValue = -1;
int whiteValue = -1;

int threshold = -1;

bool lastState = OFF;
bool state = OFF;

unsigned long time;

int calibrate()
{
    blackValue = analogRead(PIN_SENSOR);

    digitalWrite(PIN_CLICK, HIGH);
    digitalWrite(PIN_LED_CLICK, HIGH);
    delay(500);

    whiteValue = analogRead(PIN_SENSOR);

    digitalWrite(PIN_CLICK, LOW);
    digitalWrite(PIN_LED_CLICK, LOW);
    delay(500);

    //threshold = whiteValue - ((whiteValue - blackValue) / 2);
    threshold = blackValue - ((blackValue - whiteValue) / 2);

    Serial.print("# black: ");
    Serial.print(blackValue);
    Serial.println();

    Serial.print("# white: ");
    Serial.print(whiteValue);
    Serial.println();
    
    Serial.print("# threshold: ");
    Serial.print(threshold);
    Serial.println();

    if(threshold < 100)
    {
        Serial.println("# error: low threshold");
        return 0;
    }
    
    return 1;
}

void setup()
{
    pinMode(PIN_SENSOR, INPUT);
    pinMode(PIN_CLICK, OUTPUT);
    pinMode(PIN_STATE, INPUT);
    pinMode(PIN_LED_CLICK, OUTPUT);
    pinMode(PIN_LED_THRESH, OUTPUT);

    Serial.begin(9600);

    randomSeed(analogRead(A5));

    delay(1000);
}

void loop()
{
    if(digitalRead(PIN_STATE) == HIGH)
    {
        lastState = OFF;
        delay(100);
        return;
    }
    else
    {
        if(lastState == OFF)
        {
            while(!calibrate())
            {
                delay(1000);
            }

            lastState = ON;
        }

        Serial.println("# click");
        digitalWrite(PIN_CLICK, HIGH);
        digitalWrite(PIN_LED_CLICK, HIGH);
        time = micros();

        while(1)
        {
            if(analogRead(PIN_SENSOR) < threshold)
            {
                Serial.println(micros() - time);
                digitalWrite(PIN_LED_THRESH, HIGH);

                delay(100);
                digitalWrite(PIN_CLICK, LOW);
                digitalWrite(PIN_LED_CLICK, LOW);

                while(analogRead(PIN_SENSOR) < threshold) delay(100);
                digitalWrite(PIN_LED_THRESH, LOW);

                break;
            }
        }

        //delay(random(100, 1000));
        delay(random(500, 1500));
    }
}
