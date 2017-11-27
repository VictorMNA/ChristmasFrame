//==============================================================================
//
//  Copyright (C) 2017 Víctor Navarro <victormna.developer@gmail.com>
//
//  This file is part of ChristmasFrame.
//
//  ChristmasFrame is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  ChristmasFrame is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with ChristmasFrame.  If not, see <http://www.gnu.org/licenses/>.
//

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

