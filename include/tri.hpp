#ifndef TRI_HPP
#define TRI_HPP

#include <termg.hpp>

class Tri {
public:
  Tri(Vertex* v0, Vertex* v1, Vertex* v2) {
    this->v0 = v0;
    this->v1 = v1;
    this->v2 = v2;
  }
  Vertex *v0, *v1, *v2;
};

const Tri NULL_TRI = Tri(nullptr, nullptr, nullptr);

#endif