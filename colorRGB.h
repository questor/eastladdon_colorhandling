
#ifndef __COLORHANDLING_COLORRGB_H__
#define __COLORHANDLING_COLORRGB_H__

#include "stdint.h"

//this is in linear-space (non gamma corrected!)

struct colorXYZ;
struct colorSRGB;

struct colorRGB {
   float red, green, blue;

   colorRGB() {}
   colorRGB(const float red, const float green, const float blue) {
      this->red = red;
      this->green = green;
      this->blue = blue;
   }
   explicit colorRGB(const colorXYZ &xyz);
   explicit colorRGB(const colorSRGB &srgb, const float gamma = 2.2f);

   void assign(const colorXYZ &source);
   void assign(const colorSRGB &source, const float gamma = 2.2f);
   void assignStandard(const colorSRGB &source);
   void assignFast(const colorSRGB &source); ///<uses gamma 2.0 for faster conversions

   uint32_t getAsUInt32(const uint8_t alpha = 0xff) {
      uint8_t r = (uint8_t)(red*255.0f);
      uint8_t g = (uint8_t)(green*255.0f);
      uint8_t b = (uint8_t)(blue*255.0f);
      return (alpha << 24) | (r << 16) | (g << 8) | b;
   }
};

#endif   //#ifndef __COLORHANDLING_COLORRGB_H__
