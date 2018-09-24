#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <cmath>
#include <curses.h>


#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;

#include <buffer.hpp>

float frag(const float& x, const float& y, const vec3& v0, const vec3& v1, const vec3& v2) {
    vec3 origin = vec3(x, y, 0);
    static const vec3 dir = vec3(0,0,1);
    vec2 point;
    float z;
    if (glm::intersectRayTriangle(origin,dir,v0,v1,v2,point,z)) {
        return z;
    } else {
        return -1;
    }
}

float normalizeZ(const float& z, const float& min, const float& max) {
    return (z - min)/max;
}

int main() {
    int sizex = 24, sizey = 12;
    setlocale(LC_ALL,"");
    initscr();
    WINDOW * win = newwin(sizey,sizex,1,0);
    raw();
    cbreak();
    keypad(stdscr, true);
    noecho();
    curs_set(0);

    vec4 p1 = vec4(1,0,0,1);
    vec4 p2 = vec4(1,1,0,1);
    vec4 p3 = vec4(0,1,1,1);

    //getmaxyx(win,sizey,sizex);
    //sizey -= 1;
    float ratio = (float)sizex/(float)sizey;

    float midx = 0.5f/(float)sizex;
    float stepx = 1.0f/(float)sizex;

    float midy = 1.0f/(float)sizey;
    float stepy = 2.0f/(float)sizey;

    float x = 0.0f;
    float maxz = 10.0f;

    Buffer buffer(sizex, sizey);

    vec3 cameraPos = vec3(0.0f,0.0f,3.0f);
    vec3 cameraTarget = vec3(0.0f, 0.0f, 0.0f);
    vec3 up = vec3(0.0f, 1.0f, 0.0f);

    mat4 view = glm::lookAt(cameraPos, cameraTarget, up);
    mat4 projection = glm::perspective(glm::radians(45.0f), ratio, 0.1f, maxz);

    while(true) {
        
        x += 0.1;
        mat4 rot = glm::rotate(x, vec3(1,1,1));
        buffer.ResetZ(maxz);
        for(int i = 0; i < sizex; i++) {
            for(int j = 0; j < sizey; j++) {
                vec3 pr1 = vec3(projection * view * rot * p1);
                vec3 pr2 = vec3(projection * view * rot * p2);
                vec3 pr3 = vec3(projection * view * rot * p3);
                float z = frag(i*stepx + midx, j*stepy + midy, pr1, pr2, pr3);
                z = z != -1 ? normalizeZ(z,0.1f, maxz) : maxz;
                if (buffer.CompareZ(i,j,z)) {
                    buffer.SetPixel(i,j,z,z);
                }
            }
        }

        timeout(60);
        char c = getch();
        clear();
        printw("x%d, y%d, rot%f\n", sizex, sizey, x);
        refresh();
        wclear(win);
        waddstr(win,buffer.Print());
           
        wrefresh(win);

    }


    endwin();

    return 0;
}