#include <model.hpp>
#include <vertex.hpp>
#include <tri.hpp>

Model::Model() {

}

Model::Model(float* vertices, int nVertices, int* tris, int nTris) {
  this->_nVertices = nVertices;
  this->_nTris = nTris;
  this->_vertices = new Vertex*[this->_nVertices];
  this->_tris = new int*[nTris];

  for(int i = 0; i < this->_nVertices; i++) {
    this->_vertices[i] = new Vertex(
      glm::vec4(vertices[i*9], vertices[i*9 +1], vertices[i*9 +2], 1.0f),
      glm::vec3(vertices[i*9 +3], vertices[i*9 +4], vertices[i*9 +5]),
      glm::vec3(vertices[i*9 +6], vertices[i*9 +7], vertices[i*9 +8])
    );
  }

  for (int j = 0; j < this->_nTris; j++) {
    this->_tris[j] = new int[3];
    this->_tris[j][0] = tris[j*3];
    this->_tris[j][1] = tris[j*3+1];
    this->_tris[j][2] = tris[j*3+2];
  }
}

Model::~Model() {
  for(int i = 0; i < this->_nVertices; i++) {
    delete this->_vertices[i];
  }
  delete this->_vertices;
  for(int i = 0; i < this->_nTris; i++) {
    delete[] this->_tris[i];
  }
  delete this->_tris;

}

Model::iterator* Model::Begin() {
  return new Model::iterator(0, this);
}

Model::iterator* Model::End() {
  return new Model::iterator(this->_nTris, this);
}


const Tri Model::GetTri(int index) const {
  if (index >= 0 || index < this->_nTris)
    return Tri (
      this->_vertices[this->_tris[index][0]],
      this->_vertices[this->_tris[index][1]],
      this->_vertices[this->_tris[index][2]]
    );
  return NULL_TRI;
}