
#ifndef __COLORHANDLING_COLORHSL_H__
#define __COLORHANDLING_COLORHSL_H__

struct colorSRGB;

struct colorHSL {
   float hue;           //[0..1]
   float saturation;    //[0..1]
   float lightness;     //[0..1]

   colorHSL() {}
   explicit colorHSL(const colorSRGB &srgb);
   explicit colorHSL(float h, float s, float l) {
      hue = h; saturation = s; lightness = l;
   }

   void assign(const colorSRGB &source);
};

#endif   //#ifndef __COLORHANDLING_COLORHSL_H__

