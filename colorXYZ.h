
#ifndef __COLORHANDLING_COLORXYZ_H__
#define __COLORHANDLING_COLORXYZ_H__

struct colorRGB;
struct colorLAB;

struct colorXYZ {
   colorXYZ() {}
   explicit colorXYZ(const colorRGB &rgb);
   explicit colorXYZ(const colorLAB &lab);

   float x, y, z;

   void assign(const colorRGB &rgb);
   void assign(const colorLAB &lab);
};

#endif   //#ifndef __COLORHANDLING_COLORXYZ_H__
