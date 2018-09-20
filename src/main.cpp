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

#include <buffer.hpp>

float frag(const float& x, const float& y, const vec3& v0, const vec3& v1, const vec3& v2) {
    vec3 origin = vec3(x, y, 0);
    static const vec3 dir = vec3(0,0,1);
    vec2 point;
    float z;
    if (glm::intersectRayTriangle(origin,dir,v0,v1,v2,point,z)) {
        return z;
    } else {
        return 10;
    }
}

int main() {
    setlocale(LC_ALL,"");
    initscr();
    raw();
    cbreak();
    keypad(stdscr, true);
    noecho();

    vec4 p1 = vec4(0.2,0.2,1,0);
    vec4 p2 = vec4(0.8,0.2,0,0);
    vec4 p3 = vec4(0.2,0.8,0,0);

    const int size = 15;

    float mid = 0.5/(float)size;
    float step = 1.0/(float)size;

    float x = 0;

    Buffer buffer(size, size);

    while(true) {
        
        x += 0.1;
        glm::mat4x4 rot = glm::rotate(x, vec3(0.5,0.5,0.5));
        buffer.ResetZ();
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                vec3 pr1 = vec3(rot * p1);
                vec3 pr2 = vec3(rot * p2);
                vec3 pr3 = vec3(rot * p3);
                float z = frag(i*step + mid, j*step + mid, pr1, pr2, pr3);
                if (buffer.CompareZ(i,j,z)) {
                    buffer.SetPixel(i,j,z,z);
                }
            }
        }

        timeout(60);
        char c = getch();
        clear();
        printw("%f\n", x);

        printw(buffer.Print());
        refresh();
    }


    endwin();

    return 0;
}