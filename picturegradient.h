
#ifndef __PICTUREGRADIENT_H__
#define __PICTUREGRADIENT_H__

#include "eastl/types.h"

/* uses a picture as gradientbase */
class PictureGradient {
public:
   PictureGradient() 
      : mPixel(NULL)
   {}
   PictureGradient(const char *filename);
   ~PictureGradient();

   bool init(const char *filename);

   // 0 <= t <= 1.0
   uint32_t getColor(float t) {
      int pos = (int)(t*mWidth);
      return mPixel[pos];
   }

protected:
   int_t mWidth, mHeight;
   uint32_t* mPixel;
};

#endif
