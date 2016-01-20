#include <stdafx.h>







AVoid FPS::Compute(){



    frames++;
    ADouble currentTime = glfwGetTime();


    if (AFloat(currentTime - lastTime) > 0.1f)
    {

        fps = AFloat(frames) / 0.1f;
        lastTime = currentTime;
        frames = 0;

    }



}
