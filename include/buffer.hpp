#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <string>

class Buffer {
public:
  Buffer(int sizeX, int sizeY);
  virtual ~Buffer();

  void ResetZ();
  void SetPixel(const int& x, const int& y, const float& z, const std::string& c);

  bool CompareZ(const int& x, const int& y, const float& z);

  const char* Print();
private:
  float** _zbuffer;
  std::string** _cbuffer;

  int _sizeX;
  int _sizeY;
};

#endif