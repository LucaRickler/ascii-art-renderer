#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <cmath>
#include <curses.h>


#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

int main() {
    setlocale(LC_ALL,"");
    initscr();
    raw();
    cbreak();
    keypad(stdscr, true);
    noecho();

    glm::vec4 p1 = glm::vec4(0.2,0.2,1,0);
    glm::vec4 p2 = glm::vec4(0.8,0.2,0,0);
    glm::vec4 p3 = glm::vec4(0.2,0.8,0,0);

    const int size = 15;
    std::string output = "";

    float mid = 0.5/(float)size;
    float step = 1.0/(float)size;

    float x = 0;

    while(true) {
        
        x += 0.1;
        glm::mat4x4 rot = glm::rotate(x,glm::vec3(0.5,0.5,0.5));
        output = "";
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                glm::vec3 origin = glm::vec3(i*step + mid, j*step + mid, 0);
                glm::vec3 dir = glm::vec3(0,0,1);
                glm::vec2 point;
                glm::vec3 pr1 = glm::vec3(rot * p1);
                glm::vec3 pr2 = glm::vec3(rot * p2);
                glm::vec3 pr3 = glm::vec3(rot * p3);
                float distance;
                if (glm::intersectRayTriangle(origin,dir,pr1,pr2,pr3,point,distance)) {
                    if(distance < 0.25)
                        output += "\u2589";
                    else if (distance < 0.5)
                        output += "\u2593";
                    else if (distance > 0.75)
                        output += "\u2591";
                    else
                        output += "\u2592";
                } else {
                    output += " ";
                }
            }
            output +="\n";
        }
        output +="\n";

        timeout(60);
        char c = getch();
        clear();
        printw("%f\n", x);

        printw(output.c_str());
        refresh();
    }


    endwin();

    return 0;
}