#ifndef _SHIFTER_H_
#define _SHIFTER_H_

#include "easypng.h"
#include "animation.h"

namespace Shifter
{
    /**
     * Makes an animation of an image shifting to the left 
     * @param image - the image to be shifted
     * @return - an animation of the image being shifted
     */
    animation shiftSerial(const PNG & toShift);

    /**
     * Makes an animation of an image shifting to the left 
     * @param image - the image to be shifted
     * @return - an animation of the image being shifted
     */
    animation shiftParallel(const PNG & toShift);

    /**
     * Makes sure that the shifted.gif matches soln_shifted.gif
     * @return - whether all the frames match
     */
    bool checkCorrectness();

}

#endif
