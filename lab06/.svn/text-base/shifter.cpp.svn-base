#include "shifter.h"

/**
 * Makes an animation of an image shifting to the left
 * @param image - the image to be shifted
 * @return - an animation of the image being shifted
 */
animation Shifter::shiftSerial(const PNG & toShift)
{
    PNG image = toShift;
    animation anim;
    int width = image.width();
    int height = image.height();
    int shiftAmount = 32;

	// shift image to the left by 32 pixels each iteration
    for(int destCol = 0; destCol < width; destCol += 32)
    {
        for(int x = 0; x < width - 32; ++x)
        {
            for(int y = 0; y < height; ++y)
            {
                *image(x, y) = *image(x + 32, y);
            }
        }
        if(destCol % shiftAmount == 0)
        {
            anim.addFrame(image);
        }
    }
    return anim;
}

/**
 * Makes an animation of an image shifting to the left
 * @param image - the image to be shifted
 * @return - an animation of the image being shifted
 */
animation Shifter::shiftParallel(const PNG & toShift)
{
    // TODO: parallelize this code

    PNG image = toShift;
    animation anim;
    int width = image.width();
    int height = image.height();
    int shiftAmount = 32;

	// shift image to the left by 32 pixels each iteration

    for(int destCol = 0; destCol < width; destCol += 32)
    {
        
        #pragma omp parallel for
        for(int y = 0; y < height; ++y)       
        {
            for(int x = 0; x < width - 32; ++x)
            {
                *image(x, y) = *image(x + 32, y);
            }
        }
        if(destCol % shiftAmount == 0)
        {
            anim.addFrame(image);
        }
    }
    return anim;
}

/**
 * Makes sure that shifted.gif matches soln_shifted.gif
 * @return - whether all the frames match
 */
bool Shifter::checkCorrectness()
{
    return system("./checkShifter.sh") == 0;
}
