#ifndef MODEL_HPP
#define MODEL_HPP

#include <termg.hpp>

#include <iterator>


class Model  {
public:
  Model();
  Model(float* vertices, int nVertices, int* tris, int nTris);
  virtual ~Model();

class iterator : public std::iterator<std::random_access_iterator_tag, Tri> {
  public:
    iterator() : iterator(0, nullptr) {}
    iterator(int p, Model* m): _p(p), _model(m) {}
    iterator(const iterator& other): iterator(other._p, other._model) {}
    const iterator& operator=(const iterator& other) {
      _p = other._p;
      _model = other._model;
      return other;
    }

    iterator& operator++()    {_p++; return *this;} // prefix++
    iterator  operator++(int) {iterator tmp(*this); ++(*this); return tmp;} // postfix++
    iterator& operator--()    {_p--; return *this;} // prefix--
    iterator  operator--(int) {iterator tmp(*this); --(*this); return tmp;} // postfix--

    void     operator+=(const std::size_t& n)  {_p += n;}
    void     operator+=(const iterator& other) {_p += other._p;}
    iterator operator+ (const std::size_t& n)  {iterator tmp(*this); tmp += n; return tmp;}
    iterator operator+ (const iterator& other) {iterator tmp(*this); tmp += other; return tmp;}

    void        operator-=(const std::size_t& n)  {_p -= n;}
    void        operator-=(const iterator& other) {_p -= other._p;}
    iterator    operator- (const std::size_t& n)  {iterator tmp(*this); tmp -= n; return tmp;}
    std::size_t operator- (const iterator& other) {return _p - other._p;}

    bool operator< (const iterator& other) {return (_p-other._p)< 0;}
    bool operator<=(const iterator& other) {return (_p-other._p)<=0;}
    bool operator> (const iterator& other) {return (_p-other._p)> 0;}
    bool operator>=(const iterator& other) {return (_p-other._p)>=0;}
    bool operator==(const iterator& other) {return  _p == other._p; }
    bool operator!=(const iterator& other) {return  _p != other._p; }

    const Tri GetTri() const {return this->_model->GetTri(_p);}
  private:
    int _p;
    Model* _model;
  };

  iterator* Begin();
  iterator* End();

private:
  Vertex** _vertices;
  int _nVertices;
  int** _tris;
  int _nTris;

  const Tri GetTri(int index) const;
};

#endif