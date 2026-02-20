#include <unistd.h>
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


int main() {
    int radius = 32;

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


    AWindow win = AWindow(scrDims.x, scrDims.y); //width, height, posX, posY, borderWidth, VisualAttributes (GLX), XEventMask (GLX)
    GLContext glc = GLContext(win); //allows for GL calls

    win.SetName("Window Name ts");

    //win.SetSize(240, 240);
    //win.GetSize(scrDims.x, scrDims.y);

    std::cout << scrDims << std::endl;

    //Texture2D tex = Texture2D(std::filesystem::current_path().string() + "/image.bmp");
    //tex.SetScale(10.0f, 10.0f);

    //ASound sound = ASound(std::filesystem::current_path().string() + "/sound.wav");

    char spinnor[] = "-\\|/";

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, scrDims.x, scrDims.y);

    int frameCount = 0;
    bool progShouldEnd = false;
    while(!progShouldEnd) {
        AEngine::Loop(win.GetSharedDisplay());

        cube.angle = 0.03f*frameCount;

        // CPU RENDERING

        /*win.GetSize(scrDims.x, scrDims.y);

        for(int x=0; x<scrDims.x; x++) {
        for(int y=0; y<scrDims.y; y++) {
            win.SetPenCol(((int)std::floor((x/(float)scrDims.x)*255.0f) << 16) + ((int)std::floor((((float)scrDims.y-y)/scrDims.y)*255.0f) << 8));
            win.Plot(x, y);
        }} // CPU SCREEN UV   TS WAS SO FUCKING SLOWWWWWWW!!!!

        //win.DrawTexture(tex, 0, 0);

        win.SetPenCol(0x000000);
        win.FillRect(0, 0, scrDims.x, scrDims.y);

        win.SetPenCol(0xFF8000);
        win.Rect(500, 400, 50, 50);
        win.Line(scrDims.x/2, scrDims.y/2, AEvent::MousePosX(), scrDims.y-AEvent::MousePosY());

        win.FillArc(AEvent::MousePosX(), scrDims.y-AEvent::MousePosY(), radius, radius, 0, 360);

        win.DisplayWindow();*/

        
        // GPU RENDERING

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
                    vertex += cube.pos;
                    glVertex3f(vertex.x, vertex.y, vertex.z);
                }
            }
		glEnd();

        glXSwapBuffers(win.GetSharedDisplay(), win.GetWindowObject());
        

        // EVERYTHING ELSE

        //sound.Play();

        std::cout << "  [" << spinnor[(frameCount % 16)/4] << "] " << ATime::deltaTime << "               " << std::endl;
        std::cout << "\033[1A";

        if(AWindow::GetWinCount() == 0) {
            progShouldEnd = true;
        } // you need this if you want your shit to end when the user clicks the x

        if(AEvent::IsKeyDown(XK_Escape)) {
            progShouldEnd = true;
        }

        if(AEvent::IsScroll()) {
            radius += (AEvent::ScrollDir() * 2)-1;
        }

        frameCount++;
        usleep(10000); // not using delta time here, bite me, but you should for physics. . .
        //delta time is in ATime::deltaTime :3
    }

    return 0;
}