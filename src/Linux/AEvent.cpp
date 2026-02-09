#include "AEvent.h"
#include "AWindow.h"


std::unordered_map<int, KeyState> AEvent::keys;
std::vector<int> AEvent::keysChangedThisFrame;

int AEvent::mouseX = 0;
int AEvent::mouseY = 0;
int AEvent::mouseXLastFrame = 0;
int AEvent::mouseYLastFrame = 0;
bool AEvent::mouseButton[5];
bool AEvent::mouseButtonLastFrame[5];
bool AEvent::scroll = false;
bool AEvent::scrollDir = false;

bool AEvent::configNotifyThisFrame = false;


void AEvent::MandatoryUpdate(Display* dis) {
    //Display* dis = win.GetSharedDisplay();

    configNotifyThisFrame = false;

    mouseXLastFrame = mouseX;
    mouseYLastFrame = mouseY;

    for(int i=0; i<5; i++) {
        mouseButtonLastFrame[i] = mouseButton[i];
    }
    scroll = false;

    for(int key : keysChangedThisFrame) {
        keys.at(key).pressed = false;
        keys.at(key).released = false;
    }
    keysChangedThisFrame.clear();

    int currxkeysym;

    XEvent e; //handling events
    while(XPending(dis) > 0) {
        XNextEvent(dis, &e);
        switch(e.type) {
        case KeyPress:
            currxkeysym = XkbKeycodeToKeysym(dis, e.xkey.keycode, 0, 0);

            if(keys.find(currxkeysym) != keys.end()) {
                if(!keys.at(currxkeysym).held) {
                    keys.at(currxkeysym).held = true;
                    keys.at(currxkeysym).pressed = true;
                }
            } else {
                keys.insert({currxkeysym, KeyState{true, true, false}});
            }
            keysChangedThisFrame.push_back(currxkeysym);
            break;


        case KeyRelease:
            currxkeysym = XkbKeycodeToKeysym(dis, e.xkey.keycode, 0, 0);

            if(keys.find(currxkeysym) != keys.end()) {
                keys.at(currxkeysym).held = false;
                keys.at(currxkeysym).released = true;
            } else {
                keys.insert({currxkeysym, KeyState{false, false, true}});
            }
            keysChangedThisFrame.push_back(currxkeysym);
            break;


        case ButtonPress:
            switch(e.xbutton.button) {
            case 1:
                AEvent::mouseButton[0] = true;
                break;
            case 3:
                AEvent::mouseButton[1] = true;
                break;
            case 2:
                AEvent::mouseButton[2] = true;
                break;
            case 4:
                AEvent::scroll = true;
                AEvent::scrollDir = true;
                break;
            case 5:
                AEvent::scroll = true;
                AEvent::scrollDir = false;
                break;
            case 9:
                AEvent::mouseButton[3] = true;
                break;
            case 8:
                AEvent::mouseButton[4] = true;
                break;
            }
            break;

        case ButtonRelease:
            switch(e.xbutton.button) {
            case 1:
                AEvent::mouseButton[0] = false;
                break;
            case 3:
                AEvent::mouseButton[1] = false;
                break;
            case 2:
                AEvent::mouseButton[2] = false;
                break;
            case 9:
                AEvent::mouseButton[3] = false;
                break;
            case 8:
                AEvent::mouseButton[4] = false;
                break;
            }
            break;

        case MotionNotify:
            mouseX = e.xmotion.x;
            mouseY = e.xmotion.y;
            break;
        case ConfigureNotify:
            configNotifyThisFrame = true;
        default:
            break;
        }
    }
}


int AEvent::MousePosX() {
    return mouseX;
}

int AEvent::MousePosY() {
    return mouseY;
}

int AEvent::MouseXDelta() {
    return mouseX - mouseXLastFrame;
}

int AEvent::MouseYDelta() {
    return mouseY - mouseYLastFrame;
}


bool AEvent::IsKey(int i) { // will take const char* to be mapped to XKeysyms
    if(keys.find(i) != keys.end()) {
        return keys.at(i).held;
    } else {
        return false;
    }
}

bool AEvent::IsKeyDown(int i) {
    if(keys.find(i) != keys.end()) {
        return keys.at(i).pressed;
    } else {
        return false;
    }
}

bool AEvent::IsKeyUp(int i) {
    if(keys.find(i) != keys.end()) {
        return keys.at(i).released;
    } else {
        return false;
    }
}

bool AEvent::IsButton(int i) {
    return mouseButton[i];
}

bool AEvent::IsButtonDown(int i) {
    return (mouseButton[i] && !mouseButtonLastFrame[i]);
}

bool AEvent::IsButtonUp(int i) {
    return (!mouseButton[i] && mouseButtonLastFrame[i]);
}

bool AEvent::IsScroll() {
    return scroll;
}

bool AEvent::ScrollDir() {
    return scrollDir;
}

void AEvent::WaitUntilConfigNotify(Display* dis) {
    int tryCount = 0;
    while (!configNotifyThisFrame) {
        if(tryCount >= 500) {
            break;
        }
        MandatoryUpdate(dis);
        tryCount++;
    }
}