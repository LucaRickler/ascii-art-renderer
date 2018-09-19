#include <buffer.hpp>

Buffer::Buffer(int sizeX, int sizeY) {
  this->_sizeX = sizeX;
  this->_sizeY = sizeY;

  this->_cbuffer = new std::string*[sizeY];
  this->_zbuffer = new float*[sizeY];
  for (int j = 0; j < sizeY; j++) {
    this->_cbuffer[j] = new std::string[sizeX];
    this->_zbuffer[j] = new float[sizeX];
  }
}

Buffer::~Buffer() {
  for (int j = 0; j < this->_sizeY; j++) {
    delete[] this->_zbuffer[j];
    delete[] this->_cbuffer[j];
  }
  delete[] this->_zbuffer;
  delete[] this->_cbuffer;
}

void Buffer::ResetZ() {
  for (int j = 0; j < this->_sizeY; j++) {
    for (int i = 0; i < this->_sizeY; i++) {
      this->_zbuffer[j][i] = 10;
      this->_cbuffer[j][i] = ' ';
    }
  }
}

void Buffer::SetPixel(int x, int y, float z, const std::string c) {
  if (x >= 0 && x < this->_sizeX && y >= 0 && y < this->_sizeY) {
    if (this->_zbuffer[y][x] > z){
      this->_zbuffer[y][x] = z;
      this->_cbuffer[y][x] = c;
    } 
  }
}

bool Buffer::CompareZ(int x, int y, float z) {
  if (x >= 0 && x < this->_sizeX && y >= 0 && y < this->_sizeY) {
    return this->_zbuffer[y][x] > z;
  }
  return false;
}

const char* Buffer::Print() {
  std::string output = "";
  for (int j = 0; j < this->_sizeY; j++) {
    for (int i = 0; i < this->_sizeY; i++) {
      output += this->_cbuffer[j][i];
    }
    output += "\n";
  }
  return output.c_str();
}