//==============================================================================
#ifndef IMAGES_H
#define IMAGES_H

#include <stdint.h>

//==============================================================================
typedef struct 
{
  uint8_t width;
  uint8_t height;
  uint8_t pixel_data[];
} gimp_image;

//==============================================================================
// images for ShowIcon
extern const PROGMEM gimp_image ball;
extern const PROGMEM gimp_image tree;
extern const PROGMEM gimp_image candy;
extern const PROGMEM gimp_image bell;
extern const PROGMEM gimp_image candle;
extern const PROGMEM gimp_image snowflake;
extern const PROGMEM gimp_image hat;


//==============================================================================
// images for LetItSnow
extern const PROGMEM gimp_image house;
extern const PROGMEM gimp_image sled;
extern const PROGMEM gimp_image smallTree;


//==============================================================================
// image for Marquee
extern const PROGMEM gimp_image FelizNavidad;

#endif

