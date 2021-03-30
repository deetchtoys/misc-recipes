#ifndef FACE_KERNEL_H_
#define FACE_KERNEL_H_

#include <iostream>

class FaceFeature
{
 public:
  double data[255];
  int age;
  int imgId;
};

class FaceManager
{
 public:
  int reg()
  {
    std::cout << "FaceManager:reg()" << std::endl;

    return 0;
  }

  int identify()
  {
    std::cout << "FaceManager:identify()" << std::endl;

    return 0;
  }
};



#endif
