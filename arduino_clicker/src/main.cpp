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

#define MODE_IDLE 0
#define MODE_CALIBRATE 1
#define MODE_MEASURE 2
#define MODE_SEND 3

int MODE = MODE_IDLE;

int threshold = -1;

unsigned long last_measurement;

int calibrate()
{
    int blackValue = -1;
    int whiteValue = -1;

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

unsigned long measure()
{
    digitalWrite(PIN_CLICK, HIGH);
    digitalWrite(PIN_LED_CLICK, HIGH);
    unsigned long time = micros();
    unsigned long result;

    while(1)
    {
        if(analogRead(PIN_SENSOR) < threshold)
        {
            result = micros() - time;
            digitalWrite(PIN_LED_THRESH, HIGH);

            delay(100);
            digitalWrite(PIN_CLICK, LOW);
            digitalWrite(PIN_LED_CLICK, LOW);

            while(analogRead(PIN_SENSOR) < threshold) delay(100);

            digitalWrite(PIN_LED_THRESH, LOW);

            break;
        }
    }

    return result;
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

    delay(100);
}

void loop()
{
    if(MODE == MODE_IDLE)
    {
        char message = Serial.read();

        if(message == 'c') MODE = MODE_CALIBRATE;
        else if(message == 'm') MODE = MODE_MEASURE;
        else if(message == 's') MODE = MODE_SEND;
    }
    else if(MODE == MODE_CALIBRATE)
    {
        calibrate();
        MODE = MODE_IDLE;
    }
    else if(MODE == MODE_MEASURE)
    {
        delay(random(500, 1500));
        last_measurement = measure();
        Serial.println(last_measurement);
        MODE = MODE_IDLE;
    }
    else if(MODE == MODE_SEND)
    {
        Serial.println(last_measurement);
        MODE = MODE_IDLE;
    }
    delay(50);
}
