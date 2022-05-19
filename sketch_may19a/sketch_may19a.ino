#include "FastLED.h"
#define NUM_LEDS 320
#define PIN 22
CRGB leds[NUM_LEDS];

const unsigned short int image_width = 32;
const unsigned short int image_height = 10;
const unsigned short int text_length = 4;
const unsigned char Sina[41]=
{
  0x00,0x00,0x00,0x00,  //  0004    . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
  0x7A,0x00,0x00,0x00,  //  0008    . # # # # . # . . . . . . . . . . . . . . . . . . . . . . . . . 
  0x80,0x00,0x00,0x00,  //  000C    # . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
  0x82,0xF1,0xC0,0x00,  //  0010    # . . . . . # . # # # # . . . # # # . . . . . . . . . . . . . . 
  0x72,0x88,0x20,0x00,  //  0014    . # # # . . # . # . . . # . . . . . # . . . . . . . . . . . . . 
  0x0A,0x89,0xE0,0x00,  //  0018    . . . . # . # . # . . . # . . # # # # . . . . . . . . . . . . . 
  0x0A,0x8A,0x20,0x00,  //  001C    . . . . # . # . # . . . # . # . . . # . . . . . . . . . . . . . 
  0x0A,0x8A,0x20,0x00,  //  0020    . . . . # . # . # . . . # . # . . . # . . . . . . . . . . . . . 
  0xF2,0x89,0xE0,0x00,  //  0024    # # # # . . # . # . . . # . . # # # # . . . . . . . . . . . . . 
  0x00,0x00,0x00,0x00,  //  0028    . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
  4
};

const unsigned char S[11]=
{
  0x00, //  0001    . . . . . . . . 
  0x78, //  0002    . # # # # . . . 
  0x80, //  0003    # . . . . . . . 
  0x80, //  0004    # . . . . . . . 
  0x70, //  0005    . # # # . . . . 
  0x08, //  0006    . . . . # . . . 
  0x08, //  0007    . . . . # . . . 
  0x08, //  0008    . . . . # . . . 
  0xF0, //  0009    # # # # . . . . 
  0x00,  //  000A    . . . . . . . .
  1 // col
};

unsigned char* get_symbol(char ch, int* len) {
  if (len == NULL) return NULL;
  switch (ch) {
    case 'S':
      *len = sizeof(S) / sizeof(S[0]);
      return S;
    break;
    default:
      *len = sizeof(Sina) / sizeof(Sina[0]);
      return Sina;
  }
}

void setup() { FastLED.addLeds<NEOPIXEL, PIN>(leds, NUM_LEDS); }
int i = 0, j = 0, k = 0, idx = 0, res = 0, value = 0;
void loop() {
    int len =0;
    unsigned char* symbol= get_symbol('S', &len);
    int col = symbol[len - 1];
    for (i = 0; i < image_height; i++)
    {
        for (j = 0; j < image_width; j++)
        {
            if ( j > 7 ) break;
            idx = i * col + (j / 8);
            value = symbol[idx];
            int shift = 7 - (j % 8); // 7 - 0
            value = value >> shift;
            value = value & 0x01;
            leds[i * image_width + j] = value == 1 ? CRGB::Red : CRGB::Black;
        }
    }

    FastLED.show();
/* for( i = 0; i < NUM_LEDS; i++ ) {
    if (image_code[i)
        leds[i] = CRGB::Red;
    // delay(30);
    //leds[0] = CRGB::Black; FastLED.show(); delay(30);
 } */ 
 
}
