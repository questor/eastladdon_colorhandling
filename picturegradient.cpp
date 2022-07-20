
#ifdef ENABLE_PICTUREGRADIENT

#include "picturegradient.h"

#include "stb_image/stb_image.h"

PictureGradient::PictureGradient(const char *filename) {
   init(filename);
}

PictureGradient::~PictureGradient() {
   if(mPixel) {
      stbi_image_free(mPixel);
   }
}

bool PictureGradient::init(const char *filename) {
   int n;
   mPixel = (uint32_t*)stbi_load(filename, &mWidth, &mHeight, &n, 4);
   if(mPixel != NULL) {
      //abgr => argb
      uint32_t *src = mPixel;
      for(int_t i=0; i<mWidth; ++i) {
         uint32_t pixel = *src;
         uint32_t r = 0x000000ff & pixel;
         uint32_t b = 0x00ff0000 & pixel;
         *(src++) = (pixel & 0xff00ff00) + (r<<16) + (b>>16);
      }
   }
   return mPixel != NULL;
}

#endif   //#ifdef ENABLE_PICTUREGRADIENT
