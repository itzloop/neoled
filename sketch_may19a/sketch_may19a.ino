#include "FastLED.h"
#include "DS1307RTC.h"
#define NUM_LEDS 320
#define PIN 22
#define LED_W 32
#define LED_H 10
#define DELAYMS 50
#define COL_MAX 8
#define STR "SINA SHABANI"
#define HOUR 23
#define MIN 24
CRGB leds[NUM_LEDS];

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
  5 // col
};

const unsigned char I[11]=
{
  0x00, //  0001    . . . . . . . . 
  0xE0, //  0002    # # # . . . . . 
  0x40, //  0003    . # . . . . . . 
  0x40, //  0004    . # . . . . . . 
  0x40, //  0005    . # . . . . . . 
  0x40, //  0006    . # . . . . . . 
  0x40, //  0007    . # . . . . . . 
  0x40, //  0008    . # . . . . . . 
  0xE0, //  0009    # # # . . . . . 
  0x00, //  000A    . . . . . . . . 
  3
};

const unsigned char N[11]=
{
  0x00, //  0001    . . . . . . . . 
  0x84, //  0002    # . . . . # . . 
  0xC4, //  0003    # # . . . # . . 
  0xA4, //  0004    # . # . . # . . 
  0x94, //  0005    # . . # . # . . 
  0x94, //  0006    # . . # . # . . 
  0x94, //  0007    # . . # . # . . 
  0x8C, //  0008    # . . . # # . . 
  0x84, //  0009    # . . . . # . . 
  0x00, //  000A    . . . . . . . .
  6 
};

const unsigned char A[11]=
{
  0x00, //  0001    . . . . . . . . 
  0x30, //  0002    . . # # . . . . 
  0x30, //  0003    . . # # . . . . 
  0x48, //  0004    . # . . # . . . 
  0x48, //  0005    . # . . # . . . 
  0x48, //  0006    . # . . # . . . 
  0xFC, //  0007    # # # # # # . . 
  0x84, //  0008    # . . . . # . . 
  0x84, //  0009    # . . . . # . . 
  0x00, //  000A    . . . . . . . . 
  6
};

const unsigned char H[11]=
{
  0x00, //  0001    . . . . . . . . 
  0x84, //  0002    # . . . . # . . 
  0x84, //  0003    # . . . . # . . 
  0x84, //  0004    # . . . . # . . 
  0xFC, //  0005    # # # # # # . . 
  0x84, //  0006    # . . . . # . . 
  0x84, //  0007    # . . . . # . . 
  0x84, //  0008    # . . . . # . . 
  0x84, //  0009    # . . . . # . . 
  0x00, //  000A   . . . . . . . . 
  6
};

const unsigned char B[11]=
{
  0x00, //  0001    . . . . . . . . 
  0xF0, //  0002    # # # # . . . . 
  0x88, //  0003    # . . . # . . . 
  0x88, //  0004    # . . . # . . . 
  0xF0, //  0005    # # # # . . . . 
  0x88, //  0006    # . . . # . . . 
  0x88, //  0007    # . . . # . . . 
  0x88, //  0008    # . . . # . . . 
  0xF0, //  0009    # # # # . . . . 
  0x00, //  000A    . . . . . . . . 
  5
};

const unsigned char ZERO[11]=
{
  0x00, //  0001    . . . . . . . . 
  0x70, //  0002    . # # # . . . . 
  0x88, //  0003    # . . . # . . . 
  0x88, //  0004    # . . . # . . . 
  0x88, //  0005    # . . . # . . . 
  0x88, //  0006    # . . . # . . . 
  0x88, //  0007    # . . . # . . . 
  0x88, //  0008    # . . . # . . . 
  0x70, //  0009    . # # # . . . . 
  0x00, //  000A    . . . . . . . .
  5
};

const unsigned char ONE[11]=
{
  0x00, //  0001    . . . . . . . . 
  0x20, //  0002    . . # . . . . . 
  0x60, //  0003    . # # . . . . . 
  0xA0, //  0004    # . # . . . . . 
  0x20, //  0005    . . # . . . . . 
  0x20, //  0006    . . # . . . . . 
  0x20, //  0007    . . # . . . . . 
  0x20, //  0008    . . # . . . . . 
  0x20, //  0009    . . # . . . . . 
  0x00, //  000A    . . . . . . . . 
  3
};

const unsigned char TWO[11]=
{
  0x00, //  0001    . . . . . . . . 
  0x70, //  0002    . # # # . . . . 
  0x88, //  0003    # . . . # . . . 
  0x08, //  0004    . . . . # . . . 
  0x10, //  0005    . . . # . . . . 
  0x20, //  0006    . . # . . . . . 
  0x40, //  0007    . # . . . . . . 
  0x80, //  0008    # . . . . . . . 
  0xF8, //  0009    # # # # # . . . 
  0x00, //  000A    . . . . . . . . 
  5
};

const unsigned char THREE[11]=
{
  0x00, //  0001    . . . . . . . . 
  0x70, //  0002    . # # # . . . . 
  0x88, //  0003    # . . . # . . . 
  0x08, //  0004    . . . . # . . . 
  0x30, //  0005    . . # # . . . . 
  0x08, //  0006    . . . . # . . . 
  0x08, //  0007    . . . . # . . . 
  0x88, //  0008    # . . . # . . . 
  0x70, //  0009    . # # # . . . . 
  0x00, //  000A    . . . . . . . . 
  5
};

const unsigned char FOUR[11]=
{
  0x00, //  0001    . . . . . . . . 
  0x10, //  0002    . . . # . . . . 
  0x30, //  0003    . . # # . . . . 
  0x50, //  0004    . # . # . . . . 
  0x90, //  0005    # . . # . . . . 
  0xF8, //  0006    # # # # # . . . 
  0x10, //  0007    . . . # . . . . 
  0x10, //  0008    . . . # . . . . 
  0x10, //  0009    . . . # . . . . 
  0x00, //  000A    . . . . . . . . 
  5
};

const unsigned char FIVE[11]=
{
  0x00, //  0001    . . . . . . . . 
  0xF8, //  0002    # # # # # . . . 
  0x80, //  0003    # . . . . . . . 
  0x80, //  0004    # . . . . . . . 
  0xF0, //  0005    # # # # . . . . 
  0x08, //  0006    . . . . # . . . 
  0x08, //  0007    . . . . # . . . 
  0x88, //  0008    # . . . # . . . 
  0x70, //  0009    . # # # . . . . 
  0x00, //  000A    . . . . . . . . 
  5
};

const unsigned char SIX[11]=
{
  0x00, //  0001    . . . . . . . . 
  0x30, //  0002    . . # # . . . . 
  0x40, //  0003    . # . . . . . . 
  0x80, //  0004    # . . . . . . . 
  0xF0, //  0005    # # # # . . . . 
  0x88, //  0006    # . . . # . . . 
  0x88, //  0007    # . . . # . . . 
  0x88, //  0008    # . . . # . . . 
  0x70, //  0009    . # # # . . . . 
  0x00, //  000A    . . . . . . . . 
  5
};

const unsigned char SEVEN[11]=
{
  0x00, //  0001    . . . . . . . . 
  0xF8, //  0002    # # # # # . . . 
  0x08, //  0003    . . . . # . . . 
  0x10, //  0004    . . . # . . . . 
  0x10, //  0005    . . . # . . . . 
  0x20, //  0006    . . # . . . . . 
  0x20, //  0007    . . # . . . . . 
  0x40, //  0008    . # . . . . . . 
  0x40, //  0009    . # . . . . . . 
  0x00, //  000A    . . . . . . . . 
  5
};

const unsigned char EIGHT[11]=
{
  0x00, //  0001    . . . . . . . . 
  0x70, //  0002    . # # # . . . . 
  0x88, //  0003    # . . . # . . . 
  0x88, //  0004    # . . . # . . . 
  0x70, //  0005    . # # # . . . . 
  0x88, //  0006    # . . . # . . . 
  0x88, //  0007    # . . . # . . . 
  0x88, //  0008    # . . . # . . . 
  0x70, //  0009    . # # # . . . . 
  0x00, //  000A    . . . . . . . . 
  5
};

const unsigned char NINE[11]=
{
  0x00, //  0001    . . . . . . . . 
  0x70, //  0002    . # # # . . . . 
  0x88, //  0003    # . . . # . . . 
  0x88, //  0004    # . . . # . . . 
  0x88, //  0005    # . . . # . . . 
  0x78, //  0006    . # # # # . . . 
  0x08, //  0007    . . . . # . . . 
  0x10, //  0008    . . . # . . . . 
  0x60, //  0009    . # # . . . . . 
  0x00, //  000A    . . . . . . . . 
  5
};

const unsigned char DOT[11]=
{
  0x00, //  0001    . . . . . . . . 
  0x00, //  0002    . . . . . . . . 
  0xC0, //  0003    # # . . . . . . 
  0xC0, //  0004    # # . . . . . . 
  0x00, //  0005    . . . . . . . . 
  0x00, //  0006    . . . . . . . . 
  0xC0, //  0007    # # . . . . . . 
  0xC0, //  0008    # # . . . . . . 
  0x00, //  0009    . . . . . . . . 
  0x00, //  000A    . . . . . . . . 
  2
};

unsigned char *get_symbol(char ch, int *len)
{
  if (len == NULL)
    return NULL;
  switch (ch)
  {
  case 'A':
    *len = sizeof(A) / sizeof(A[0]);
    return A;
  case 'B':
    *len = sizeof(B) / sizeof(B[0]);
    return B;
  case 'I':
    *len = sizeof(I) / sizeof(I[0]);
    return I;
  case 'N':
    *len = sizeof(N) / sizeof(N[0]);
    return N;
  case 'S':
    *len = sizeof(S) / sizeof(S[0]);
    return S;
  case 'H':
    *len = sizeof(H) / sizeof(H[0]);
    return H;
   case '1':
    *len = sizeof(ONE) / sizeof(ONE[0]);
    return ONE;
  case '2':
    *len = sizeof(TWO) / sizeof(TWO[0]);
    return TWO;
  case '3':
    *len = sizeof(THREE) / sizeof(THREE[0]);
    return THREE;
  case '4':
    *len = sizeof(FOUR) / sizeof(FOUR[0]);
    return FOUR;
  case '5':
    *len = sizeof(FIVE) / sizeof(FIVE[0]);
    return FIVE;
  case '6':
    *len = sizeof(SIX) / sizeof(SIX[0]);
    return SIX;
  case '7':
    *len = sizeof(SEVEN) / sizeof(SEVEN[0]);
    return SEVEN;
  case '8':
    *len = sizeof(EIGHT) / sizeof(EIGHT[0]);
    return EIGHT;
  case '9':
    *len = sizeof(NINE) / sizeof(NINE[0]);
    return NINE;
  case '.':
    *len = sizeof(DOT) / sizeof(DOT[0]);
    return DOT;
  case ' ':
    *len = 0;
    return NULL;
  }
}

tmElements_t rtime;
int i = 0, j = 0, k = 0, idx = 0, res = 0, value = 0;
unsigned long int currentms, prevms = 0;
int current_chr = 0, current_col = 0, counter = 0;
unsigned char* str = NULL;
enum State { NAME, CLEAR_SCREEN, CLOCK };
enum State state = NAME;
bool invert = false;

void reset_with_color(CRGB color) {
    for (i = 0; i < LED_H; i++)
  {
    for (j = 0; j < LED_W - 1; j++)
    {
      int idx = i * LED_W + j;
      leds[idx] = color;
    }
  }
}

void insert_blank() {
  for (i = 0; i < LED_H; i++)
  {
    int idx = i * LED_W + (LED_W - 1);
    leds[idx] = CRGB::Black;
  }
}

void show_name() {
   // get the current character
  char ch = str[current_chr];

  // get the matrix representing this character
  int len = 0;
  unsigned char *symbol = get_symbol(ch, &len);

  // if it's the space char insert two blanks
  if ( ch == ' ' ) {
    insert_blank();
    insert_blank();
    current_chr++;
    return;
  }

  // if we typed character insert blank
  if (current_col >= symbol[len - 1]) {
     insert_blank();
     current_col = 0; 
     current_chr++;
     return;
  } 

  // fill in the last column with symbol
  for (i = 0; i < LED_H; i++) {
    value = symbol[i];

    // shift value to get the bit pointed by current col      
    int shift = (COL_MAX - 1) - current_col;
    value = value >> shift;
    value = value & 0x01;
    
    // get index of last col for led
    idx = i * LED_W + (LED_W - 1);
    leds[idx] = value == 1 ? CRGB::Red : CRGB::Black;
  }

  // move to the next column for this character
  current_col++;

  // if we showed the character reset col and move current_chr forward
 // if (current_col >= COL_MAX) {
 //   current_col = 0; current_chr++;
 // }
}

void shift_leds() {
  // shift last column of the leds by 1 to the left
  for (i = 0; i < LED_H; i++)
  {
    for (j = 0; j < LED_W - 1; j++)
    {
      int idx = i * LED_W + j;
      leds[idx] = leds[idx + 1];
    }
  }
}

void show_clock(int m, int h){
  // h1h2:m1m2
  char t[] = {(char)(h / 10) + '0', (char)(h % 10) + '0', (char)(m / 10) + '0', (char)(m % 10) + '0'};

  for (k = 0; k < 4; k++){
    int len = 0;
    unsigned char* symbol = get_symbol(t[k], &len);
    for (i = 0; i < LED_H; i++) {
      for (j = k * COL_MAX; j < (k + 1) * COL_MAX; j++) {
        value = symbol[i];
        // shift value to get the bit pointed by current col      
        int shift = (COL_MAX - 1) - (j % COL_MAX);
        value = value >> shift;
        value = value & 0x01;
        
        // get index of last col for led
        idx = i * LED_W + j;
        leds[idx] = value == 1 ? CRGB::Red : CRGB::Black;
      }
    }    
  }

}

void setup()
{
  str = STR;
  FastLED.addLeds<NEOPIXEL, PIN>(leds, NUM_LEDS);
  reset_with_color(CRGB::Black);
  FastLED.show();
  pinMode(HOUR, INPUT);
  pinMode(MIN, INPUT);
}

void loop()
{
  unsigned long int currentms = millis();
  if (currentms - prevms < DELAYMS) return;
  
  prevms = currentms;

  switch ( state ){
  case NAME: 
    shift_leds();
    show_name(); 
    // if it's the end of string, wait for LED_W shifts and switch to clock
    if ( str[current_chr] == '\0' ) {
      state = CLEAR_SCREEN;
      counter = 0; 
    }
    break;
  case CLEAR_SCREEN:
    shift_leds();
    if (counter++ == LED_W) state = CLOCK;
    break;
  case CLOCK:
    if( RTC.read(rtime) ) {
      show_clock(rtime.Minute, rtime.Hour); 
    }
    break;
  }

  // show shifted leds
  FastLED.show();
}