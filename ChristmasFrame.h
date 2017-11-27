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

