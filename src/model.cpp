#include <model.hpp>
#include <vertex.hpp>
#include <tri.hpp>

Model::Model() {

}

Model::~Model() {
  for(int i = 0; i < this->_nVertices; i++) {
    delete this->_vertices[i];
  }
  delete this->_vertices;
  for(int i = 0; i < this->_nTris; i++) {
    delete this->_tris[i];
  }
  delete this->_tris;

}

const Tri Model::GetTri(int index) {
  return Tri (
    this->_vertices[this->_tris[index][0]],
    this->_vertices[this->_tris[index][1]],
    this->_vertices[this->_tris[index][2]]
  );
}