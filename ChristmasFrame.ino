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
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

//==============================================================================
#include "images.h"

#include "ChristmasFrame.h"



//==============================================================================
//==============================================================================
//==============================================================================
// Select yourconfiguration
#define PIN 13
#define NUMPIXELS FRAME_PIXELS

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.


//==============================================================================
//==============================================================================
//==============================================================================
void setup()
{
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  // to get a "truly" random data, use the seed with a "strange changing value"
  // i.e. an unused (not conected) analog input (will read "noise")
  randomSeed(analogRead(0));

  strip.begin();
  // not too bright to save energy and protect the eyes
  strip.setBrightness(40);
  strip.show(); // Initialize all pixels to 'off'

  delay(1000);
}



//==============================================================================
void loop()
{
  // you can change this to link animations at your will
  for(int Repetitions = 0; Repetitions < random(1, 4); Repetitions++)
  {
    LetItSnow();
    DelayBetweenAnimations();
    ShowRandomIcon();
    DelayBetweenAnimations();
  }
  Marquee(&FelizNavidad);
  DelayBetweenAnimations();
  
}

//==============================================================================
//==============================================================================
//==============================================================================


//==============================================================================
uint32_t BlackColor = strip.Color(0,0,0);
#define PixelOff BlackColor


//==============================================================================
// This function do the magic of convert the coordiantes to the pixel on the strip
// so this function will be dependant on how the matrix is composed (change arcording yours)
int Coor2Pix(int x, int y)
{
  // TODO: ensure the coordinates are inside the display

  // alternate direction of rows
  if((y & 0x01) == 0x01)
  {
    return (FRAME_LAST_X - x) + (FRAME_LAST_Y - y) * FRAME_HEIGHT;
  }
  else
  {
    return x + (FRAME_LAST_Y - y) * FRAME_HEIGHT;
  }
}


//==============================================================================
void DelayBetweenAnimations()
{
  // to mantain expectation and "magic" the time between animations will be random
  // from 1s to 5s, every animation has 1s of delay inside, so here it goes from 0s to 4s
  delay(random(9) * 500);
}




//==============================================================================
//==============================================================================
//==============================================================================
void DeleteImage()
{
  int Index;

  for(Index = 0; Index < NUMPIXELS; Index++)
  {
    strip.setPixelColor(Index, PixelOff);
  }
  strip.show(); 
}

//==============================================================================
void SendImage(int x, int y, int w, int h, const PROGMEM gimp_image *image, int ix, int iy)
{
  int ImageIndex;
  int dx, dy;

  for(dy = 0; dy < h; dy++)
  {
    for(dx = 0; dx < w; dx++)
    {
      // TODO: if ix < w or iy < h there is not image for that coordenate, so it need to be avoided to write
      ImageIndex = ((ix + dx)  + (iy + dy) * pgm_read_byte_near(&image->width)) * 3;
      strip.setPixelColor(Coor2Pix(x + dx, y + dy), strip.Color(pgm_read_byte_near(image->pixel_data + ImageIndex + 0), pgm_read_byte_near(image->pixel_data + ImageIndex + 1), pgm_read_byte_near(image->pixel_data + ImageIndex + 2)));
    }
  }
  strip.show(); 
}

//==============================================================================
void ShowIcon(const PROGMEM gimp_image *icon)
{
  SendImage(0, 0, FRAME_WIDTH, FRAME_HEIGHT, icon, 0, 0);
  delay(5000);
  DeleteImage();
  delay(1000);   
}


//==============================================================================
//==============================================================================
//==============================================================================
gimp_image *Icons[] =
{
  &ball,
  &tree,
  &candy,
  &bell,
  &candle,
  &snowflake,
  &hat
};

#define NUMBER_OF_ICONS (sizeof(Icons)/sizeof(gimp_image *))

//==============================================================================
void ShowRandomIcon()
{
  ShowIcon(Icons[random(NUMBER_OF_ICONS)]);
}



//==============================================================================
//==============================================================================
//==============================================================================
gimp_image *ObjectsToSnow[] =
{
  NULL,
  &house,
  &sled,
  &smallTree
};

#define NUMBER_OF_OBJECTS_TO_SNOW (sizeof(ObjectsToSnow)/sizeof(gimp_image *))


//==============================================================================
#define NUMBER_OF_SNOWFLAKES 20


//==============================================================================
type_Snowflake Snowflakes[NUMBER_OF_SNOWFLAKES];



//==============================================================================
uint32_t GenerateColor(type_Palette palette)
{
  uint32_t ColorGenerated;
  
  switch(palette)
  {
      default:
      case palette_SNOWFLAKES:
        ColorGenerated = strip.Color(random(80, 150), random(80, 150), random(80, 220));
        break;

      case palette_RED:
        ColorGenerated = strip.Color(random(150, 255), random(10, 100), random(10, 10));
        break;

      case palette_GREEN:
        ColorGenerated = strip.Color(random(10, 100), random(150, 255), random(10, 10));
        break;

      case palette_BLUE:
        ColorGenerated = strip.Color(random(10, 100), random(10, 100), random(150, 255));
        break;
      case palette_CONFETI:
        ColorGenerated = strip.Color(random(5, 255), random(5, 255), random(5, 200));
        break;        
  }

    return ColorGenerated;
}

//==============================================================================
void ClearSnowflakes()
{
  for(int SnowflakeIndex = 0; SnowflakeIndex < NUMBER_OF_SNOWFLAKES; SnowflakeIndex++)
  {
    Snowflakes[SnowflakeIndex].used = false;
  }
}

//==============================================================================
void CreateSnowflake(type_Snowflake *Snowflake, type_Palette palette)
{
  bool ValidSnowFlake;

  do
  {
      Snowflake->x = random(FRAME_WIDTH);
      ValidSnowFlake = true;
    
      for(int SnowflakeIndex = 0; SnowflakeIndex < NUMBER_OF_SNOWFLAKES; SnowflakeIndex++)
      {
        if(Snowflakes[SnowflakeIndex].used)
        {  
          if(((Snowflake->y == 0) && (Snowflakes[SnowflakeIndex].x == Snowflake->x))
          || ((Snowflake->y == 1) && (Snowflakes[SnowflakeIndex].x == Snowflake->x))) // to avoid "chasing" between snowflakes
          {
            ValidSnowFlake = false;
            break;
          }
        }
      }
  } while (!ValidSnowFlake);

  Snowflake->y = 0;
  Snowflake->color = GenerateColor(palette);
  Snowflake->used = true;
}



//==============================================================================
int SnowflakeNextStep(type_Snowflake Snowflake)
{

  if(Snowflake.y >= FRAME_LAST_Y)
  {  
    return Snowflake_LANDED;
  }

  Snowflake.y++;
  
  if(strip.getPixelColor(Coor2Pix(Snowflake.x, Snowflake.y)) == BlackColor)
  {
    // TODO: check if the pixel is another snowflake to avoid "chasing" between them
    return Snowflake_DOWN;  
  }
    
  if((Snowflake.x > 0) && (strip.getPixelColor(Coor2Pix(Snowflake.x - 1, Snowflake.y)) == BlackColor))
  {
    return Snowflake_DOWN_LEFT;
  }

  if((Snowflake.x < FRAME_LAST_X) && (strip.getPixelColor(Coor2Pix(Snowflake.x + 1, Snowflake.y)) == BlackColor))
  {
    return Snowflake_DOWN_RIGHT;
  }
  
  return Snowflake_LANDED;
}

//================================================================================================================
void LetItSnow()
{
  int NextStep;
  int Old_X, Old_Y;
  int MaxHeight;
  int Palette;  
  int SnowflakesLanded = 0;
  bool MoreSnowflakes = true;
  bool AllSnowflakesLanded = false;
  int FallDelay = random(10,120);
  int ProbabilityOfSnowflakes = random(1, 100);  
  int ProbabilityOfWind = random(2,35);
  type_Wind DirectionalityOfWind = random(wind_MAX);
  int ImageToGetSnowed = random(NUMBER_OF_OBJECTS_TO_SNOW);


  DeleteImage();

  switch(ImageToGetSnowed)
  {
    case 0:
      // No image on which to snow
      MaxHeight = random(2,16); 
      Palette = random(palette_MAX);
      break;

    default:
      uint8_t height, width;
      
      width = pgm_read_byte_near(&ObjectsToSnow[ImageToGetSnowed]->width);
      height = pgm_read_byte_near(&ObjectsToSnow[ImageToGetSnowed]->height);
      
      SendImage(random(FRAME_WIDTH - width), FRAME_HEIGHT - height, width, height, ObjectsToSnow[ImageToGetSnowed], 0, 0); 
      MaxHeight = random(1, FRAME_HEIGHT - pgm_read_byte_near(&ObjectsToSnow[ImageToGetSnowed]->height));
      Palette = palette_SNOWFLAKES;   
      break;                
  }

  // To let the object been seen for a while before the snow start
  // so if there is not an image, do not wait
  if(ImageToGetSnowed != 0)
  {    
    delay(500);
  }

  // clear de array, could be used from previously, and generate the first snowflake
  ClearSnowflakes();
  CreateSnowflake(&Snowflakes[0], Palette);

  // it should be finished before NUMPIXELS iterations
  // but to have an exit point if something goes wrong
  while(SnowflakesLanded < NUMPIXELS)
  {
    for(int SnowflakeIndex = 0; SnowflakeIndex < NUMBER_OF_SNOWFLAKES; SnowflakeIndex++)
    {
      if(Snowflakes[SnowflakeIndex].used)
      {
        Old_X = Snowflakes[SnowflakeIndex].x;
        Old_Y = Snowflakes[SnowflakeIndex].y;

        //the wind makes its own
        switch(random(ProbabilityOfWind))
        {
          case 0:
            if(DirectionalityOfWind != wind_RIGHT)
            {
              if(Snowflakes[SnowflakeIndex].x > 0)
              {
                if((strip.getPixelColor(Coor2Pix(Snowflakes[SnowflakeIndex].x - 1, Snowflakes[SnowflakeIndex].y)) == BlackColor))
                {
                  Snowflakes[SnowflakeIndex].x--;
                }
              }
            }
            break;

          case 1:
            if(DirectionalityOfWind != wind_LEFT)
            {              
              if(Snowflakes[SnowflakeIndex].x < FRAME_LAST_X)
              {
                if((strip.getPixelColor(Coor2Pix(Snowflakes[SnowflakeIndex].x + 1, Snowflakes[SnowflakeIndex].y)) == BlackColor))
                {
                  Snowflakes[SnowflakeIndex].x++;
                }
              }
            }
            break;

          default:
            // No wind
            break;
        }             
        
        NextStep = SnowflakeNextStep(Snowflakes[SnowflakeIndex]);

        if(NextStep == Snowflake_LANDED)
        {
          SnowflakesLanded++;
          Snowflakes[SnowflakeIndex].used = false;
          if(Snowflakes[SnowflakeIndex].y < MaxHeight)
          {
            // the snow has gone up a lot
            MoreSnowflakes = false;
          }            
        }
        else
        {
          // delete the snowflake from the old position
          strip.setPixelColor(Coor2Pix(Old_X, Old_Y), BlackColor); 
          
         Snowflakes[SnowflakeIndex].y++;
         if(NextStep == Snowflake_DOWN_LEFT)
         {
            Snowflakes[SnowflakeIndex].x--;            
         }
         else if(NextStep == Snowflake_DOWN_RIGHT)
         {
            Snowflakes[SnowflakeIndex].x++;
         }

          strip.setPixelColor(Coor2Pix(Snowflakes[SnowflakeIndex].x, Snowflakes[SnowflakeIndex].y), Snowflakes[SnowflakeIndex].color);
        }
      }
    }
    strip.show();

  if(MoreSnowflakes)
  {
      // check if need to generate Snowflake
      for(int SnowflakeIndex = 0; SnowflakeIndex < NUMBER_OF_SNOWFLAKES; SnowflakeIndex++)
      {
        if(!Snowflakes[SnowflakeIndex].used)
        {
          if(random(100) < ProbabilityOfSnowflakes)          
          {
            CreateSnowflake(&Snowflakes[SnowflakeIndex], Palette);
            if(random(100) < ProbabilityOfSnowflakes)
            {
              break;
            }
          }  
        }      
      }
    }
    else
    {
      AllSnowflakesLanded = true;
      for(int SnowflakeIndex = 0; SnowflakeIndex < NUMBER_OF_SNOWFLAKES; SnowflakeIndex++)
      {
        if(Snowflakes[SnowflakeIndex].used)
        { 
          AllSnowflakesLanded = false;
        }
      } 

      if(AllSnowflakesLanded)
      {
        // finished, admire the landscape for a while
        delay(2000);
        DeleteImage();
        delay(1000);              
        return ;
      }
     }
    
    delay(FallDelay); 
  }
}





//==============================================================================
//==============================================================================
//==============================================================================
void Marquee(const PROGMEM gimp_image *image)
{
  int StepsDelay = random(50,151);
  
  for(int offset = FRAME_LAST_X; offset > 0; offset--)
  {
    SendImage(offset, 0, FRAME_WIDTH - offset, FRAME_HEIGHT, image, 0, 0);
    delay(StepsDelay);
  }
  
  for(int offset = 0; offset < (pgm_read_byte_near(&image->width) - FRAME_WIDTH); offset++)
  {
    SendImage(0, 0, FRAME_WIDTH, FRAME_HEIGHT, image, offset, 0);
    delay(StepsDelay);
  }

  for(int offset = FRAME_LAST_X; offset > 0; offset--)
  {
    SendImage(0, 0, offset, FRAME_HEIGHT, image, (pgm_read_byte_near(&image->width) - FRAME_WIDTH) + FRAME_LAST_X - offset, 0);
    // WARNING: at this moment, the image should have the right column with black pixels
    // otherwise that colunm will be dragged
    // TODO: thinking about this
    delay(StepsDelay);
  }
  DeleteImage();
  delay(1000);
}

