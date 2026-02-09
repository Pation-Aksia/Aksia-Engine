#include <cmath>

#include <iostream>
#include <filesystem>

#include "AksiaEngine.h"


Vector2Int scrDims = Vector2Int(640, 640);


struct RenderObj {
    Vector3 pos = Vector3(0.0f, 0.0f, 0.0f);
    float angle = 0.0f;

    std::vector<Vector3> vertices;
    std::vector<Vector3Int> faces;
};

void Translate(Vector3& point, const Vector3& pos) {
    point += pos;
}


int WinMain(HINSTANCE hInstance, HINSTANCE hInsancetPrev, PSTR cmdline, int cmdshow) {
    RenderObj cube;

    cube.pos.z = 0.3f;

    cube.vertices.push_back(Vector3(-0.2f, -0.2f, -0.2f));
    cube.vertices.push_back(Vector3(-0.2f, -0.2f,  0.2f));
    cube.vertices.push_back(Vector3(-0.2f,  0.2f, -0.2f));
    cube.vertices.push_back(Vector3(-0.2f,  0.2f,  0.2f));
    cube.vertices.push_back(Vector3( 0.2f, -0.2f, -0.2f));
    cube.vertices.push_back(Vector3( 0.2f, -0.2f,  0.2f));
    cube.vertices.push_back(Vector3( 0.2f,  0.2f, -0.2f));
    cube.vertices.push_back(Vector3( 0.2f,  0.2f,  0.2f));

    cube.faces.push_back(Vector3Int(1, 0, 4));
    cube.faces.push_back(Vector3Int(1, 4, 5));
    cube.faces.push_back(Vector3Int(0, 2, 6));
    cube.faces.push_back(Vector3Int(0, 6, 4));
    cube.faces.push_back(Vector3Int(4, 6, 7));
    cube.faces.push_back(Vector3Int(4, 7, 5));
    cube.faces.push_back(Vector3Int(5, 7, 3));
    cube.faces.push_back(Vector3Int(5, 3, 1));
    cube.faces.push_back(Vector3Int(1, 3, 2));
    cube.faces.push_back(Vector3Int(1, 2, 0));
    cube.faces.push_back(Vector3Int(2, 3, 7));
    cube.faces.push_back(Vector3Int(2, 7, 6));

    Vector3 uvCols[] = {Vector3(1.0f, 0.0f, 0.0f),
                        Vector3(0.0f, 1.0f, 0.0f),
                        Vector3(0.0f, 0.0f, 1.0f)};


    AWindow win = AWindow(hInstance, scrDims.x, scrDims.y); //width, height, posX, posY, borderWidth, VisualAttributes (GLX), XEventMask (GLX)
    GLContext glc = GLContext(win); //Currently does nothing

    win.SetName("Window Name ts");

    //win.SetSize(240, 240);
    //win.GetSize(scrDims.x, scrDims.y);

    std::cout << scrDims << std::endl;

    //Texture2D tex = Texture2D(std::filesystem::current_path().string() + "/image.bmp");
    //ASound sound = ASound(std::filesystem::current_path().string() + "/sound.wav");

    char spinnor[] = "-\\|/";

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, scrDims.x, scrDims.y);

    int frameCount = 0;
    bool progShouldEnd = false;
    while(!progShouldEnd) {
        AEngine::Loop(win.GetWindowObject(), progShouldEnd);

        cube.angle = 0.03f*frameCount;

        /*for(int x=0; x<640; x++) {
        for(int y=0; y<scrDims.y; y++) {
            win.SetPenCol(((int)std::floor((x/640.0f)*255.0f) << 16) + ((int)std::floor(((479-y)/480.0f)*255.0f) << 8));
            win.Plot(x, y);
        }}*/ // TS SO FUCKING SLOWWWWWWW!!!!
        
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CW);

        glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
            for(int f=0; f<cube.faces.size(); f++) {
                for(int fi=0; fi<3; fi++) {
                    glColor3f(uvCols[fi].x, uvCols[fi].y, uvCols[fi].z);

                    Vector3 vertex = cube.vertices[cube.faces[f][fi]];
                    vertex = vertex.RotateY(-cube.angle);
                    vertex = vertex.RotateX(-0.31415926f);
                    Translate(vertex, cube.pos);
                    glVertex3f(vertex.x, vertex.y, vertex.z);
                }
            }
		glEnd();

        SwapBuffers(win.GetHDC());


        //win.DrawTexture(tex, 0, 0, 10, 10);
        //sound.Play();


        /*if(AEvent::MouseXDelta() != 0 || AEvent::MouseYDelta() != 0) {
            std::cout << "(" << AEvent::MousePosX() << ", " << AEvent::MousePosY() << ")          " << std::endl;
            std::cout << "\033[1A";
        }
        if(AEvent::IsKey(XK_a)) {
            std::cout << "a          " << std::endl;
            std::cout << "\033[1A";
        }
        if(AEvent::IsKeyUp(XK_b)) {
            std::cout << "b          " << std::endl;
            std::cout << "\033[1A";
        }
        if(AEvent::IsKeyDown(XK_c)) {
            std::cout << "c          " << std::endl;
            std::cout << "\033[1A";
        }
        if(AEvent::IsButtonDown(0)) {
            std::cout << "click!          " << std::endl;
            std::cout << "\033[1A";
        }
        if(AEvent::IsButtonDown(1)) {
            std::cout << "right click!          " << std::endl;
            std::cout << "\033[1A";
        }
        if(AEvent::IsButtonDown(2)) {
            std::cout << "middle click!          " << std::endl;
            std::cout << "\033[1A";
        }
        if(AEvent::IsButtonDown(3)) {
            std::cout << "side button!          " << std::endl;
            std::cout << "\033[1A";
        }
        if(AEvent::IsButtonDown(4)) {
            std::cout << "side button 2!          " << std::endl;
            std::cout << "\033[1A";
        }
        if(AEvent::IsScroll()) {
            if(AEvent::ScrollDir()) {
                std::cout << "scroll up!          " << std::endl;
                std::cout << "\033[1A";
            } else {
                std::cout << "scroll down!          " << std::endl;
                std::cout << "\033[1A";
            }
        }*/

        std::cout << "  [" << spinnor[(frameCount % 16)/4] << "] " << ATime::deltaTime << "               " << std::endl;
        std::cout << "\033[1A";

        /*if(AEvent::IsKeyDown(VK_Escape)) {
            //std::cout << std::filesystem::current_path().string() + "/image.bmp" << std::endl;
            progShouldEnd = true;
        }*/

        frameCount++;
        //win.FlushDisplay();
        //Sleep(20000); // not using delta time here, bite me, but you should for physics. . .
    }

    return 0;
}