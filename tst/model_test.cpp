#include <test.hpp>
#include <algorithm>

void ModelTest() {
  float vertices[] = {
    1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 1.0f,  0.0f, 0.0f, 0.0f,
  };
  int tris[] = {
    0,1,2,
    0,1,3
    };
  Model m(vertices, 4, tris, 2);

  // auto i = m.Begin();
  
  // printf("v0.x %f", i->GetTri().v0->pos.x);
  std::for_each(m.Begin(), m.End(), [](Model::iterator& i){
    printf("v0.x %f", i.GetTri().v0->pos.x);
  });
}