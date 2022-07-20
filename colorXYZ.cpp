
#include "colorXYZ.h"
#include "colorRGB.h"
#include "colorLAB.h"

colorXYZ::colorXYZ(const colorRGB &rgb) {
   assign(rgb);
}

colorXYZ::colorXYZ(const colorLAB &lab) {
   assign(lab);
}


void colorXYZ::assign(const colorRGB &rgb) {
   //D65 white point
   x = rgb.red * 0.412453f + rgb.green * 0.357580f + rgb.blue * 0.180423f;
   y = rgb.red * 0.212671f + rgb.green * 0.715160f + rgb.blue * 0.072169f;
   z = rgb.red * 0.019334f + rgb.green * 0.119193f + rgb.blue * 0.950227f;
}

void colorXYZ::assign(const colorLAB &lab) {
   const float e = 216.0f / 24389.0f;
   const float k = 24389.0f / 27.0f;

   float fy = (lab.l + 16.0f) / 116.0f;
   float fz = fy - lab.b / 200.0f;
   float fx = lab.a / 500.0f + fy;

   float fxfxfx = fx*fx*fx;
   if(fxfxfx > e) {
      x = fxfxfx;
   } else {
      x = (116.0f*fx-16.0f)/k;
   }

   if(lab.l > k*e) {
      y = ((lab.l+16.0f)/116.0f);
      y = y * y * y;
   } else {
      y = lab.l / k;
   }

   float fzfzfz = fz * fz * fz;
   if(fzfzfz > e) {
      z = fzfzfz;
   } else {
      z = (116.0f * fz - 16.0f)/k;
   }
}
