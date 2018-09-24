#ifndef BUFFER_HPP
#define BUFFER_HPP

class Buffer {
public:
  Buffer(int sizeX, int sizeY);
  virtual ~Buffer();

  void ResetZ();
  void ResetZ(const float& maxz);
  void SetPixel(const int& x, const int& y, const float& z, const float& c);

  bool CompareZ(const int& x, const int& y, const float& z);

  const char* Print();
private:
  float** _zbuffer;
  float** _cbuffer;

  int _sizeX;
  int _sizeY;
};

#endif