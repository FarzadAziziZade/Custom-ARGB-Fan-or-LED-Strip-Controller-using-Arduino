#include <FastLED.h>

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    3
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS    20
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          100
#define COLOR_CHANGE_DELAY  100
#define on_off  50

void setup() {
    delay(3000); // 3 second delay for recovery

    // Tell FastLED about the LED strip configuration
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    // Set master brightness control
    FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
    // Define the colors to cycle through
    CRGB colors[] = {CRGB::Red, CRGB::Green, CRGB::Blue, CRGB::Yellow, CRGB::Cyan, CRGB::Magenta};
    static int colorIndex = 0;

    // Turn on each LED sequentially, all LEDs stay on until the end of the sequence
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = colors[colorIndex];
        FastLED.show();
        delay(on_off);  // Adjust the delay to control the speed of the sequence
    }

    // Wait 3 seconds with all LEDs on
    delay(COLOR_CHANGE_DELAY);

    // Turn off each LED sequentially
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
        FastLED.show();
        delay(on_off);  // Adjust the delay to control the speed of the sequence
    }

    // Wait 3 seconds with all LEDs off
    delay(COLOR_CHANGE_DELAY);

    // Move to the next color
    colorIndex = (colorIndex + 1) % (sizeof(colors) / sizeof(colors[0]));
}