#include <FastLED.h>

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    3
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    20
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          100
#define COLOR_WAVE_DELAY    500
#define FLASH_DELAY         500
#define PARTIAL_ON_DELAY    500
#define ODD_EVEN_DELAY      500

void setup() {
    delay(3000); // 3 second delay for recovery
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    randomSeed(analogRead(0)); // Initialize random seed
}

void rainbow() {
    fill_rainbow(leds, NUM_LEDS, random(255), random(5, 15));
    FastLED.show();
    delay(COLOR_WAVE_DELAY);
}

void flashRandom() {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
    }
    int randomLED = random(NUM_LEDS);
    leds[randomLED] = CRGB::White;
    FastLED.show();
    delay(FLASH_DELAY);
    leds[randomLED] = CRGB::Black;
    FastLED.show();
    delay(FLASH_DELAY);
}

void partialOn() {
    int start = random(NUM_LEDS);
    int end = random(start, NUM_LEDS);
    for (int i = start; i <= end; i++) {
        leds[i] = CHSV(random(255), 255, 255);
    }
    FastLED.show();
    delay(PARTIAL_ON_DELAY);
    for (int i = start; i <= end; i++) {
        leds[i] = CRGB::Black;
    }
    FastLED.show();
    delay(PARTIAL_ON_DELAY);
}

void oddEvenAlternating() {
    for (int i = 0; i < NUM_LEDS; i++) {
        if (i % 2 == 0) {
            leds[i] = CHSV(random(255), 255, 255);
        } else {
            leds[i] = CRGB::Black;
        }
    }
    FastLED.show();
    delay(ODD_EVEN_DELAY);
    for (int i = 0; i < NUM_LEDS; i++) {
        if (i % 2 != 0) {
            leds[i] = CHSV(random(255), 255, 255);
        } else {
            leds[i] = CRGB::Black;
        }
    }
    FastLED.show();
    delay(ODD_EVEN_DELAY);
}

void loop() {
    // Execute different patterns based on a random choice
    int pattern = random(4);

    switch (pattern) {
        case 0:
            rainbow();
            break;
        case 1:
            flashRandom();
            break;
        case 2:
            partialOn();
            break;
        case 3:
            oddEvenAlternating();
            break;
    }
}