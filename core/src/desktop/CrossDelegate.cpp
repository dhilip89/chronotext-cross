/*
 * THE NEW CHRONOTEXT TOOLKIT: https://github.com/arielm/new-chronotext-toolkit
 * COPYRIGHT (C) 2012-2015, ARIEL MALKA ALL RIGHTS RESERVED.
 *
 * THE FOLLOWING SOURCE-CODE IS DISTRIBUTED UNDER THE SIMPLIFIED BSD LICENSE:
 * https://github.com/arielm/new-chronotext-toolkit/blob/master/LICENSE.md
 */

#include "desktop/CrossDelegate.h"
#include "cross/Context.h"

using namespace std;

namespace chr
{
    namespace intern
    {
        CrossDelegate *instance = nullptr;
    }

    CrossDelegate& delegate()
    {
        return checkedReference(intern::instance);
    }
    
    // ---
    
    bool CrossDelegate::performInit()
    {
        if (!initialized_)
        {
            if (glfwInit())
            {
                glfwWindowHint(GLFW_SAMPLES, initInfo.windowInfo.aaSamples);
                glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

                initInfo.window = glfwCreateWindow(initInfo.windowInfo.size.x, initInfo.windowInfo.size.y, "", NULL, NULL);

                if (initInfo.window)
                {
                    glfwSetKeyCallback(initInfo.window, keyCallback);

                    glfwMakeContextCurrent(initInfo.window);
                    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

                    // ---

                    intern::instance = this;
                    initialized_ = _init();
                }
            }
        }
        
        return initialized_;
    }
    
    void CrossDelegate::performUninit()
    {
        if (initialized_ && !setup_)
        {
            _uninit();

            initialized_ = false;
            intern::instance = nullptr;
        }
    }
    
    void CrossDelegate::performSetup()
    {
        if (!setup_ && initialized_)
        {
            _setup();

            // ---

            setup_ = true;
        }
    }
    
    void CrossDelegate::performShutdown()
    {
        if (setup_)
        {
            _shutdown();

            // ---

            setup_ = false;
        }
    }
    
    void CrossDelegate::performResize(const glm::vec2 &size)
    {
        setupInfo.windowInfo.size = size;
        sketch->performResize(size);
    }
    
    void CrossDelegate::performUpdate()
    {
        /*
         * SUBSEQUENT CALLS TO FrameClock::getTime() DURING THE FRAME WILL RETURN THE SAME TIME-SAMPLE
         */
        sketch->clock()->update(true);

        sketch->performUpdate();
        updateCount++;
    }
    
    void CrossDelegate::performDraw()
    {
        sketch->draw();
    }

    void CrossDelegate::run(int width, int height, int aaSamples)
    {
        initInfo.windowInfo = setupInfo.windowInfo = WindowInfo(width, height, aaSamples);

        performInit();
        performSetup();
        performResize(setupInfo.windowInfo.size);

        sketch->performStart(CrossSketch::START_REASON_VIEW_SHOWN);

        while (!glfwWindowShouldClose(initInfo.window))
        {
            performUpdate();
            performDraw();

            glfwSwapBuffers(initInfo.window);
            glfwPollEvents();
        }

        sketch->performStop(CrossSketch::STOP_REASON_VIEW_HIDDEN);

        performShutdown();
        performUninit();
    }

    void CrossDelegate::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if ((action == GLFW_PRESS) && (key == GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(window, true);
        }
    }
}
