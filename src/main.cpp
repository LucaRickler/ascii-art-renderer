#include <iostream>
#include <string>
#include <glm/glm.hpp>


#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/intersect.hpp>

int main() {

    glm::vec3 p1 = glm::vec3(0,0,0);
    glm::vec3 p2 = glm::vec3(1,0,0);
    glm::vec3 p3 = glm::vec3(0,1,0);

    const int size = 10;
    std::string output = "";

    float mid = 0.5/(float)size;
    float step = 1.0/(float)size;

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            glm::vec3 origin = glm::vec3(i*step + mid, j*step + mid,0);
            glm::vec3 dir = glm::vec3(0,0,1);
            glm::vec3 point;
            if (glm::intersectLineTriangle(origin,dir,p1,p2,p3,point)) {
                output += "#";
            } else {
                output += " ";
            }
        }
        output +="\n";
    }
    
    std::cout << output << std::endl;

    return 0;
}