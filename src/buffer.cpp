#include <buffer.hpp>

Buffer::Buffer(int sizeX, int sizeY) {
  this->_sizeX = sizeX;
  this->_sizeY = sizeY;

  this->_cbuffer = new float*[sizeY];
  this->_zbuffer = new float*[sizeY];
  for (int j = 0; j < sizeY; j++) {
    this->_cbuffer[j] = new float[sizeX];
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
      this->_cbuffer[j][i] = 0;
    }
  }
}

void Buffer::SetPixel(const int& x, const int& y, const float& z, const float& c) {
  if (x >= 0 && x < this->_sizeX && y >= 0 && y < this->_sizeY) {
    if (this->_zbuffer[y][x] > z) {
      this->_zbuffer[y][x] = z;
      this->_cbuffer[y][x] = c;
    } 
  }
}

bool Buffer::CompareZ(const int& x, const int& y, const float& z) {
  if (x >= 0 && x < this->_sizeX && y >= 0 && y < this->_sizeY) {
    return this->_zbuffer[y][x] > z;
  }
  return false;
}

const char* Buffer::Print() {
  std::string output = "";
  for (int j = 0; j < this->_sizeY; j++) {
    for (int i = 0; i < this->_sizeY; i++) {
      if (this->_cbuffer[j][i] == 0)
        output += " ";
      else if (this->_cbuffer[j][i] < 0.25)
        output += "\u2589";      
      else if (this->_cbuffer[j][i] < 0.5)
        output += "\u2593";
      else if (this->_cbuffer[j][i] > 0.75)
        output += "\u2591";
      else
        output += "\u2592";
       ;
    }
    output += "\n";
  }
  return output.c_str();
}