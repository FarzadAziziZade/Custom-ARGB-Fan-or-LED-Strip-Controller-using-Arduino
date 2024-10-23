#include <FastLED.h>

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    3
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    6
CRGB leds[NUM_LEDS];

#define BRIGHTNESS  100
#define COLOR_DELAY 500

void setup() {
    delay(3000); // 3 second delay for recovery
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
    // Set each LED to a different color
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(i * (255 / NUM_LEDS), 255, 255); // Distribute hues evenly across LEDs
    }
    FastLED.show();
    delay(COLOR_DELAY);

    // Loop to update colors continuously
    static uint8_t hueOffset = 0;
    hueOffset += 1;

    // Update colors with an offset to animate the rainbow
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV((i * (255 / NUM_LEDS)) + hueOffset, 255, 255);
    }
    FastLED.show();
    delay(COLOR_DELAY);
}