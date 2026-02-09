#ifndef _AKSI_EVENT_CH_
#define _AKSI_EVENT_CH_

#include <X11/Xlib.h>

#include <unordered_map>
#include <vector>

struct KeyState {
    bool held = false;
    bool pressed = false;
    bool released = false;
};

class AEvent {
private:
    static int mouseX, mouseY;
    static int mouseXLastFrame, mouseYLastFrame;
    static bool scroll, scrollDir;
    static bool mouseButton[];
    static bool mouseButtonLastFrame[];

    static std::unordered_map<int, KeyState> keys;
    static std::vector<int> keysChangedThisFrame;

    static bool configNotifyThisFrame;

    static bool IsAutoRepeat(Display* dis, XEvent* e);

public:
    static void MandatoryUpdate(Display* dis);

    static int MousePosX();
    static int MousePosY();
    static int MouseXDelta();
    static int MouseYDelta();

    static bool IsKey(int i); //maybe move these to an Input class
    static bool IsKeyDown(int i);
    static bool IsKeyUp(int i);

    static bool IsButton(int i);
    static bool IsButtonDown(int i);
    static bool IsButtonUp(int i);

    static bool IsScroll();
    static bool ScrollDir();

    static void WaitUntilConfigNotify(Display* dis);
};

#endif