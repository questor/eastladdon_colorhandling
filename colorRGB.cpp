
#include "colorRGB.h"

#include "colorXYZ.h"
#include "colorSRGB.h"
#include <math.h>

colorRGB::colorRGB(const colorXYZ &xyz) {
   assign(xyz);
}

colorRGB::colorRGB(const colorSRGB &srgb, const float gamma) {
   assign(srgb, gamma);
}

void colorRGB::assign(const colorXYZ &source) {
   //D65 white point
   red   =  (source.x * 3.2406255f) - (source.y * 1.5372080f) - (source.z * 0.4986286f);
   green = -(source.x * 0.9689307f) + (source.y * 1.8757561f) + (source.z * 0.0415175f);
   blue  =  (source.x * 0.0557101f) - (source.y * 0.2040211f) + (source.z * 1.0569959f);
}


void colorRGB::assign(const colorSRGB &source, const float gamma) {
   float scale = 1.0f / 255.0f;
   red =   pow(source.red   * scale, gamma);
   green = pow(source.green * scale, gamma);
   blue =  pow(source.blue  * scale, gamma);
}

void colorRGB::assignStandard(const colorSRGB &source) {
   if(source.red <= 0.04045f) {
      red = source.red / 12.92f;
   } else {
      red = pow((source.red+0.055f)/1.055f, 2.4f);
   }
   if(source.green <= 0.04045f) {
      green = source.green / 12.92f;
   } else {
      green = pow((source.green+0.055f)/1.055f, 2.4f);
   }
   if(source.blue <= 0.04045f) {
      blue = source.blue / 12.92f;
   } else {
      blue = pow((source.blue+0.055f)/1.055f, 2.4f);
   }
}

//uses gamma 2.0 for faster conversions
void colorRGB::assignFast(const colorSRGB &source) {
   float scale = 1.0f / 255.0f;
   float r = source.red * scale;
   float g = source.green * scale;
   float b = source.blue * scale;
   red = r * r;
   green = g * g;
   blue = b * b;
}
