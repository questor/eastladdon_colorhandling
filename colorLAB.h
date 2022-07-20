
#ifndef __COLORHANDLING_COLORLAB_H__
#define __COLORHANDLING_COLORLAB_H__

#include <math.h>

struct colorXYZ;

struct colorLAB {
   float l;    //light - dark
   float a;    //red - green
   float b;    //yellow - blue

   colorLAB() {}
   explicit colorLAB(const colorXYZ &xyz);

   void assign(const colorXYZ &xyz);

   float cie1994difference(const colorLAB &a, const colorLAB &b) {
      const float kL = 1;  //2 textiles
      const float kC = 1;
      const float kH = 1;
      const float K1 = 0.045f;   //graphic arts, 0.048 for textiles
      const float K2 = 0.015f;   //graphic arts, 0.014 for textiles

      float deltaL = a.l - b.l;
      float deltaA = a.a - b.a;
      float deltaB = a.b - b.b;
      float c1 = sqrtf(a.a*a.a + a.b*a.b);
      float c2 = sqrtf(b.a*b.a + b.b*b.b);
      float deltaC = c1-c2;
      float temp = deltaA*deltaA + deltaB*deltaB - deltaC*deltaC;
      float deltaH;
      if (temp > 0)
         deltaH = sqrt(temp);
      else
         deltaH = 0.0f;
      float sL = 1;
      float sC = 1 + K1*c1;
      float sH = 1 + K2*c1;

      float first = deltaL / (kL*sL);
      float second = deltaC / (kC*sC);
      float third = deltaH / (kH*sH);

      return sqrt(first*first + second*second + third*third);
   }
};

#endif   //#ifndef __COLORHANDLING_COLORLAB_H__
