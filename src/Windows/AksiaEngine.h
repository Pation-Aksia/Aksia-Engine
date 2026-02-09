#ifndef _AKSI_ENGINE_MAIN_HEADER_
#define _AKSI_ENGINE_MAIN_HEADER_

#include "AMath.h"

#include "AWindow.h"
#include "AEvent.h"

#include "BitmapHandler.h"
#include "Texture2D.h"

#include "ASound.h"

#include "GLContext.h"

class ATime {
public:
    static double startTime;
    static double elapsedTime;
    static double systemTime;
    static double deltaTime;
};

class AEngine {
public:
    //static void Init();

    static void Loop(HWND& handle, bool& programShouldEnd);
};

#endif