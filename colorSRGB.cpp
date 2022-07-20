
#include "colorSRGB.h"

#include "colorRGB.h"
#include "colorHSL.h"
#include <math.h>

colorSRGB::colorSRGB(const colorRGB &color, float gamma) {
   assign(color, gamma);
}

colorSRGB::colorSRGB(const colorHSL &color) {
   assign(color);
}


static float hslValue(float m1, float m2, float hue) {
   hue = fmod(hue, 6.0f);
   if(hue < 1.0f)
      return m1 + ((m2-m1)*hue);
   if(hue < 3.0f)
      return m2;
   if(hue < 4.0f)
      return m1 + ((m2-m1)*(4.0f-hue));
   return m1;
}

void colorSRGB::assign(const colorHSL &source) {
   if(source.saturation == 0) {
      //achromatic case
      uint8_t val = (uint8_t)(source.lightness * 255.0f);
      red = val;
      green = val;
      blue = val;
   } else {
      float m2;
      if(source.lightness < 0.5f) {
         m2 = source.lightness * (1.0f + source.saturation);
      } else {
         m2 = source.lightness + source.saturation - (source.lightness*source.saturation);
      }
      float m1 = (2.0f * source.lightness) - m2;
      float hue = source.hue / 60.0f;
      red = (uint8_t)(255.0f * hslValue(m1, m2, source.hue + 2.0f));
      green = (uint8_t)(255.0f * hslValue(m1, m2, source.hue));
      blue = (uint8_t)(255.0f * hslValue(m1, m2, source.hue - 2.0f));
   }
}

void colorSRGB::assign(const colorRGB &source, const float gamma) {
   float invGamma = 1.0f / gamma;
   red =   (uint8_t)(pow(source.red,   invGamma) * 255.0f);
   green = (uint8_t)(pow(source.green, invGamma) * 255.0f);
   blue =  (uint8_t)(pow(source.blue,  invGamma) * 255.0f);
}

void colorSRGB::assignStandard(const colorRGB &source) {
   if(source.red <= 0.0031308) {
      red = (uint8_t)(255.0f * 12.92 * source.red);
   } else {
      red = (uint8_t)((1.055 * pow(source.red, 1.0f / 2.4f) - 0.055f)*255.0f);
   }
   if(source.green <= 0.0031308) {
      green = (uint8_t)(255.0f * 12.92 * source.green);
   } else {
      green = (uint8_t)((1.055 * pow(source.green, 1.0f / 2.4f) - 0.055f)*255.0f);
   }
   if(source.blue <= 0.0031308) {
      blue = (uint8_t)(255.0f * 12.92 * source.blue);
   } else {
      blue = (uint8_t)((1.055 * pow(source.blue, 1.0f / 2.4f) - 0.055f)*255.0f);
   }
}

//uses gamma 2.0 for faster conversions
void colorSRGB::assignFast(const colorRGB &source) {
   red =   (uint8_t)(sqrt(source.red) * 255.0f);
   green = (uint8_t)(sqrt(source.green) * 255.0f);
   blue =  (uint8_t)(sqrt(source.blue) * 255.0f);
}

