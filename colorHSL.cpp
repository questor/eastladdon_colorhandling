
#include "colorHSL.h"
#include "colorSRGB.h"

#include "eastl/algorithm.h"

colorHSL::colorHSL(const colorSRGB &srgb) {
   assign(srgb);
}

void colorHSL::assign(const colorSRGB &source) {
   float min, max;
   if(source.red > source.green) {
      max = eastl::max(source.red, source.blue);
      min = eastl::min(source.green, source.blue);
   } else {
      max = eastl::max(source.green, source.blue);
      min = eastl::min(source.red, source.blue);
   }

   lightness = (max+min) / 2.0f;

   if(max == min) {
      //achromatic (gray)
      saturation = 0.0f;
      hue = 0.0f;
   } else {
      float delta = max - min;
      if(lightness < 0.5f) {
         saturation = delta / (max+min);
      } else {
         saturation = delta / (2.0f - max - min);
      }

      float dr = (max-source.red) / delta;
      float dg = (max-source.green) / delta;
      float db = (max-source.blue) / delta;

      if(source.red == max) {
         hue = db - dg;
      } else if(source.green == max) {
         hue = 2.0f + dr - db;
      } else {
         hue = 4.0f + dg - dr;
      }

      hue = fmod(hue*60.0f, 360.0f);
   }
}
