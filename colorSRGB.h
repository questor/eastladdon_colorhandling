
#ifndef __COLORHANDLING_COLORSRGB_H__
#define __COLORHANDLING_COLORSRGB_H__

#include "stdint.h"

struct colorRGB;
struct colorHSL;

//this is the same as sRGB which is already gamma corrected!
// linearRGB is without gamma correction!
struct colorSRGB {
   //DO NOT DO CALCULATIONS WITH THIS DATA-TYPES!
   // these are gamma corrected and r/2 is not half the brightness of r!

   uint8_t red, green, blue;

   colorSRGB() {}
   explicit colorSRGB(const uint8_t red, const uint8_t green, const uint8_t blue) {
      this->red = red;
      this->green = green;
      this->blue = blue;
   }
   explicit colorSRGB(const colorRGB &color, float gamma = 2.2f);
   explicit colorSRGB(const colorHSL &color);

   void assign(const colorHSL &source);
   void assign(const colorRGB &source, const float gamma = 2.2f);
   void assignStandard(const colorRGB &source);
   void assignFast(const colorRGB &source);  ///<uses gamma 2.0 for faster conversions
   uint32_t getAsUInt32(const uint8_t alpha = 0xff) {
      return (alpha << 24) | (red << 16) | (green << 8) | blue;
   }
};

#endif   //#ifndef __COLORHANDLING_COLORSRGB_H__

