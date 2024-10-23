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
#define COLOR_CHANGE_DELAY  300
#define FADE_DELAY          3

void setup() {
    delay(3000); // 3 second delay for recovery

    // Tell FastLED about the LED strip configuration
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    // Set master brightness control
    FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
    // Define a broader array of colors to cycle through, including a placeholder for rainbow
    CRGB colors[] = {
        CRGB::Red, CRGB::Green, CRGB::Blue, CRGB::Yellow,
        CRGB::Cyan, CRGB::Magenta, CRGB::Orange, CRGB::Purple,
        CRGB::Lime, CRGB::Pink, CRGB::Teal, CRGB::Lavender,
        CRGB::Gold, CRGB::Turquoise, CRGB::White, CRGB::Black // Black will indicate the rainbow effect
    };
    static int colorIndex = 0;

    // If colorIndex corresponds to rainbow
    if (colors[colorIndex] == CRGB::Black) {
        // Apply rainbow effect
        for (int brightness = 0; brightness <= 255; brightness++) {
            fill_rainbow(leds, NUM_LEDS, 0, 255 / NUM_LEDS);
            for (int i = 0; i < NUM_LEDS; i++) {
                leds[i].fadeLightBy(255 - brightness);
            }
            FastLED.show();
            delay(FADE_DELAY);  // Adjust delay to control fade speed
        }
        delay(COLOR_CHANGE_DELAY);  // Keep the rainbow on

        // Gradually turn off all LEDs from the rainbow effect
        for (int brightness = 255; brightness >= 0; brightness--) {
            fill_rainbow(leds, NUM_LEDS, 0, 255 / NUM_LEDS);
            for (int i = 0; i < NUM_LEDS; i++) {
                leds[i].fadeLightBy(255 - brightness);
            }
            FastLED.show();
            delay(FADE_DELAY);  // Adjust delay to control fade speed
        }
    } else {
        // Gradually turn on all LEDs with solid colors
        for (int brightness = 0; brightness <= 255; brightness++) {
            for (int i = 0; i < NUM_LEDS; i++) {
                leds[i] = colors[colorIndex];
                leds[i].fadeLightBy(255 - brightness);
            }
            FastLED.show();
            delay(FADE_DELAY);  // Adjust delay to control fade speed
        }

        // Wait with all LEDs on
        delay(COLOR_CHANGE_DELAY);

        // Gradually turn off all LEDs with solid colors
        for (int brightness = 255; brightness >= 0; brightness--) {
            for (int i = 0; i < NUM_LEDS; i++) {
                leds[i] = colors[colorIndex];
                leds[i].fadeLightBy(255 - brightness);
            }
            FastLED.show();
            delay(FADE_DELAY);  // Adjust delay to control fade speed
        }
    }

    // Wait with all LEDs off
    delay(COLOR_CHANGE_DELAY);

    // Move to the next color
    colorIndex = (colorIndex + 1) % (sizeof(colors) / sizeof(colors[0]));
}