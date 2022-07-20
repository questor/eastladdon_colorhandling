
#ifndef __COLORHANDLING_COLORGENERATOR_H__
#define __COLORHANDLING_COLORGENERATOR_H__

// taken from here:
// http://devmag.org.za/2012/07/29/how-to-choose-colours-procedurally-algorithms/

// many color conversions taken from here: http://www.brucelindbloom.com/index.html

#include "eastl/vector.h"
#include "eastl/extra/floatutils.h"
#include "colorRGB.h"
#include "colorSRGB.h"
#include "colorHSL.h"

class ColorGenerator {
public:
   /** This algorithm computes a palette by computing a small random offset from a given colour.
    * - Not good for small palettes where high contrast is desired.
    * - Good for enriching a scene where the base colours are defined and repeated many times.
    * - Good for colouring tiles with seams **/
   template<class Random> void byRandomOffset(Random &randGen, colorRGB base, float maxOffset, int numberColors) {
      float value = (base.red + base.green + base.blue) / 3.0f;
      for(int i=0; i<numberColors; ++i) {
         float newValue = value + 2*randGen.randf() * maxOffset - maxOffset;
         float valueRatio = newValue / value;

         float newR = base.red * valueRatio;
         float newG = base.green * valueRatio;
         float newB = base.blue * valueRatio;
         if(newR < 0.0f) {
            newR = 0.0f;
         } else if(newR > 1.0f) {
            newR = 1.0f;
         }
         if(newG < 0.0f) {
            newG = 0.0f;
         } else if(newG > 1.0f) {
            newG = 1.0f;
         }
         if(newB < 0.0f) {
            newB = 0.0f;
         } else if(newB > 1.0f) {
            newB = 1.0f;
         }
         colorRGB newColor;
         newColor.red = newR;
         newColor.green = newG;
         newColor.blue = newB;
         mColors.pushBack(newColor);
      }
   }
   template<class Random> void byRandomOffsetPerElement(Random &randGen, colorRGB base, float maxOffset, int numberColors) {
      for(int i=0; i<numberColors; ++i) {
         float newR = base.red + randGen.randf() * 2.0f * maxOffset - maxOffset;
         float newG = base.green + randGen.randf() * 2.0f * maxOffset - maxOffset;
         float newB = base.blue + randGen.randf() * 2.0f * maxOffset - maxOffset;
         if(newR < 0.0f) {
            newR = 0.0f;
         } else if(newR > 1.0f) {
            newR = 1.0f;
         }
         if(newG < 0.0f) {
            newG = 0.0f;
         } else if(newG > 1.0f) {
            newG = 1.0f;
         }
         if(newB < 0.0f) {
            newB = 0.0f;
         } else if(newB > 1.0f) {
            newB = 1.0f;
         }
         colorRGB newColor;
         newColor.red = newR;
         newColor.green = newG;
         newColor.blue = newB;
         mColors.pushBack(newColor);
      }
   }

   /** This algorithm is useful for selecting colours for contrast in an interface,
    * where high contrast between successive colours is guaranteed. **/
   template<class Random> void byGoldenRatio(Random &randGen, float saturation, float luminance, int numberColors) {
      float currentHue = randGen.randf();
      for(int i=0; i<numberColors; ++i) {
         colorHSL hslColor(currentHue, saturation, luminance);
         colorSRGB tempColor;
         colorRGB newColor;
         tempColor.assign(hslColor);
         newColor.assign(tempColor);
         mColors.pushBack(newColor);

         currentHue += eastl::GOLDEN_RATIO;
         currentHue = fmod(currentHue, 1.0f);
      }
   }

   /** With suitable parameters, we can generate common colour schemes:
      - Analogous: Choose second and third ranges 0.
      - Complementary: Choose the third range 0, and first offset angle 180.
      - Split Complementary: Choose offset angles 180 +/- a small angle. The second and third ranges must be smaller than the difference between the two offset angles.
      - Triad: Choose offset angles 120 and 240.
   **/
   template<class Random> void byHarmony(Random &randGen, float offsetAngle1, float offsetAngle2,
                                         float rangeAngle0, float rangeAngle1, float rangeAngle2,
                                         float saturation, float luminance, int numberColors) {
      float referenceAngle = randGen.randf() * 360.0f;
      for(int i=0; i<numberColors; ++i) {
         float randomAngle = randGen.randf() * (rangeAngle0 + rangeAngle1 + rangeAngle2);
         if(randomAngle > rangeAngle0) {
            if(randomAngle < rangeAngle0 + rangeAngle1) {
               randomAngle += offsetAngle1;
            } else {
               randomAngle += offsetAngle2;
            }
         }
         colorHSL tempColor;
         tempColor.hue = fmod(((referenceAngle + randomAngle) / 360.0f), 1.0f);
         tempColor.saturation = saturation;
         tempColor.lightness = luminance;
         colorSRGB convColor;
         colorRGB newColor;
         convColor.assign(tempColor);
         newColor.assign(convColor);
         mColors.pushBack(newColor);
      }
   }

   /** This algorithm takes three colours, and mixes them randomly to create a palette.
      The standard algorithm produces many grey colours. If this is not desired, the amount
      of greyness can be controlled by limiting the contribution of one of the three colours.
      This version of the algorithm is given here (if the greyControl is 1, it is equivalent
      to the standard algorithm).
   **/
   template<class Random> void byTriadMixing(Random &randGen, colorRGB &c1, colorRGB &c2, colorRGB &c3, float greyControl, int numberColors) {
      for(int i=0; i<numberColors; ++i) {
         int randomIndex = randGen.rand() % 3;

         float mixRatio1 = (randomIndex == 0) ? randGen.randf()*greyControl : randGen.randf();
         float mixRatio2 = (randomIndex == 1) ? randGen.randf()*greyControl : randGen.randf();
         float mixRatio3 = (randomIndex == 2) ? randGen.randf()*greyControl : randGen.randf();

         float sum = mixRatio1 + mixRatio2 + mixRatio3;

         mixRatio1 /= sum;
         mixRatio2 /= sum;
         mixRatio3 /= sum;

         colorRGB newColor;
         newColor.red = mixRatio1 * c1.red + mixRatio2 * c2.red + mixRatio3 * c3.red;
         newColor.green = mixRatio1 * c1.green + mixRatio2 * c2.green + mixRatio3 * c3.green;
         newColor.blue = mixRatio1 * c1.blue + mixRatio2 * c2.blue + mixRatio3 * c3.blue;
         mColors.pushBack(newColor);
      }
   }

   colorRGB &getColor(int index) {
      return mColors[index];
   }

protected:
   eastl::vector<colorRGB> mColors;
};

#endif   //#ifndef __COLORHANDLING_COLORGENERATOR_H__
