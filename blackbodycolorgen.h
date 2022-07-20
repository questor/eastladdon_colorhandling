
#ifndef __COLORHANDLING_BLACKBODYCOLORGEN_H__
#define __COLORHANDLING_BLACKBODYCOLORGEN_H__

//taken from here: https://github.com/mmacklin/sandbox

#include "vector"
#include "colorRGB.h"

class BlackBodyColorGenerator {
public:
   void generate(float startTemperature, float endTemperature, int steps);

protected:
   stl::vector<colorRGB> mColors;
};

#endif   //#define __COLORHANDLING_BLACKBODYCOLORGEN_H__
