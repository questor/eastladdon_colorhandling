
#include "colorLAB.h"
#include "colorXYZ.h"

#include <math.h>

colorLAB::colorLAB(const colorXYZ &xyz) {
   assign(xyz);
}


void colorLAB::assign(const colorXYZ &xyz) {
   const float e = 216.0f / 24389.0f;
   const float k = 24389.0f / 27.0f;

   float x;
   if(xyz.x > e) {
      x = pow(xyz.x, 1.0f / 3.0f);
   } else {
      x = (k / 116.0f) * xyz.x + 16.0f / 116.0f;
   }

   float y;
   if(xyz.y > e) {
      y = pow(xyz.y, 1.0f / 3.0f);
   } else {
      y = (k / 116.0f) * xyz.y + 16.0f / 116.0f;
   }

   float z;
   if(xyz.z > e) {
      z = pow(xyz.z, 1.0f / 3.0f);
   } else {
      z = (k / 116.0f) * xyz.z + 16.0f / 116.0f;
   }

   l = 116.0f * y - 16.0f;
   a = 500.0f * (x - y);
   b = 200.0f * (y - z);
}
