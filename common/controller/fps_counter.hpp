#ifndef FPS_COUNTER_HPP
#define FPS_COUNTER_HPP




#include <stdafx.h>





/**
Class used to calculate framerate and time between frames
*/
class FPS
{



    AFloat fps;
    AInt frames;
    ADouble lastTime;




public:


    /**
    simple constructor
    */
    inline FPS() : fps(0.0f), frames(0), lastTime(0.0) {}
    /**
    Returns current framerate
    */
    inline AFloat Get() { return fps; }
    /**
    Returns current time between frames
    */
    inline ADouble Delta() { return 1.0 / fps; }
    /**
    computes fps
    */
    AVoid Compute();



};







#endif
