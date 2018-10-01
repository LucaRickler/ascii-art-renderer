#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <termg.hpp>

struct Vertex {
  glm::vec4 pos;
  glm::vec3 color;
  glm::vec3 normal;
  Vertex() : Vertex(
    glm::vec4(0,0,0,1),
    glm::vec3(0,0,0),
    glm::vec3(0,0,0)
    ) {}
  Vertex(glm::vec4 pos, glm::vec3 color, glm::vec3 normal) {
    this->pos = pos;
    this->color = color;
    this->normal = normal;
  }
};

#endif