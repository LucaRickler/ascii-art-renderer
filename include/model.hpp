#ifndef MODEL_HPP
#define MODEL_HPP

#include <iterator>
#include <vertex.hpp>
#include <tri.hpp>


class Model  {
public:
  Model();
  virtual ~Model();
  // std::iterator Begin();
  // std::iterator End();

private:
  Vertex** _vertices;
  int _nVertices;
  int** _tris;
  int _nTris;

  const Tri GetTri(int index);
};

#endif