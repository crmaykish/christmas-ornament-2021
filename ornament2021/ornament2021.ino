/**
 * @file ornament2021.ino
 * @author Colin Maykish (github.com/crmaykish/)
 * @brief Firmware for ATMEGA4809 on the Christmas Ornament 2021 board
 * 
 * Creates a "firework" effect on each LED bank - light up an unlit LED randomly and then slowly fade it off
 * 
 * @date 2021-12-17
 * @copyright Copyright (c) 2021
 */

// Six banks of LEDs, each controlled by one PWM pin
#define LED1 PIN_PB5
#define LED2 PIN_PC0
#define LED3 PIN_PC1
#define LED4 PIN_PC2
#define LED5 PIN_PC3
#define LED6 PIN_PC4

// PWM level for maximum brightness to light up an LED bank (out of 255)
#define MAX_BRIGHTNESS 255

// Time between lighting up an unlit LED
#define NEW_LIGHT_TIME_MS 200

// Time between each level of dimming
#define FADE_TIME_MS 10

#define LED_COUNT 6
const int LEDS[LED_COUNT] = {LED1, LED2, LED3, LED4, LED5, LED6};
int LEDLevels[LED_COUNT] = {0};

unsigned long time = 0;
unsigned long last_decrease_time = 0;
unsigned long last_light_time = 0;

void setup() {}

void loop()
{
    time = millis();

    // Slowly decrease brightness on any lit LEDs
    if ((time - last_decrease_time) >= FADE_TIME_MS)
    {
        for (int i = 0; i < LED_COUNT; i++)
        {
            if (LEDLevels[i] != 0)
            {
                LEDLevels[i]--;
            }

            analogWrite(LEDS[i], LEDLevels[i]);
        }

        last_decrease_time = time;
    }

    // Occasionally light up an unlit LED
    if ((time - last_light_time >= NEW_LIGHT_TIME_MS))
    {
        int r = random(LED_COUNT);

        if (LEDLevels[r] == 0)
        {
            LEDLevels[r] = MAX_BRIGHTNESS;
            analogWrite(LEDS[r], LEDLevels[r]);
        }

        last_light_time = time;
    }
}
