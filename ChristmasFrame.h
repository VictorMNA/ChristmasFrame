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
#ifndef CHRISTMASFRAME_H
#define CHRISTMASFRAME_H


//==============================================================================
// data from the frame
#define FRAME_WIDTH  22
#define FRAME_HEIGHT 22
#define FRAME_LAST_X (FRAME_WIDTH - 1)
#define FRAME_LAST_Y (FRAME_HEIGHT - 1)
#define FRAME_PIXELS (FRAME_WIDTH * FRAME_HEIGHT)


//==============================================================================
typedef struct 
{
  bool used;
  char x;
  char y;
  uint32_t color;
} type_Snowflake; 


//==============================================================================
enum
{
  Snowflake_DOWN,
  Snowflake_DOWN_LEFT,
  Snowflake_DOWN_RIGHT,
  Snowflake_LANDED
};

//==============================================================================
typedef enum
{
  palette_SNOWFLAKES,
  palette_RED,
  palette_GREEN,
  palette_BLUE,
  palette_CONFETI,
  palette_MAX
} type_Palette;

//==============================================================================
typedef enum
{
  wind_RANDOM,
  wind_LEFT,
  wind_RIGHT,
  wind_MAX
} type_Wind;


#endif

