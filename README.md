# ChristmasFrame

An arduino controlled matrix of WS2812B leds (aka NeoPixels). Mounted on a frame and displaying chritsmas stuff.

Here you can find the Instructable for building the frame: Under construction...


- The system used is an Arduino nano
- The leds matrix is 22x22 (484 pixels) from BTF-LIGHTING.
- The icons obtained from [ICONFINDER](https://www.iconfinder.com/iconsets/christmas-icon-set-3), by Anastasiia Ivanova under Creative Commons licence, and then adapted for the display.
- the tree for LetItSnow from [ICONFINDER](https://www.iconfinder.com/icons/128380/eco_ecology_flora_forest_green_nature_oak_plant_tree_wood_icon) by Aha-Soft under Creative Commons licence, and then adapted for the display.
- The house and "Feliz navidad" text (Merry christmas) drawn by myself.
- Images converted to c source with GIMP. And then adapted as needed.
- to mantain expectation and "magic" most parameter are randomly generated when every animation starts.


Ideas / Bugs / To do:
- Change images from RGB to indexed saving space.
- And/or store images in external memory (i.e. I2C EEPROM), this require extra hardware.
- The Marquee effect has a bug which make the right colunm of the image to be dragged, so make that colunm black to avoid it.
- Improve colision's check


