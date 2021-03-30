#ifndef FACE_KERNEL_H_
#define FACE_KERNEL_H_

#include <iostream>

class FaceManager{
 public:
  int registerFace(char *imageBuffer,
                   int imageBufferSize,
                   char *featureBuffer,
                   int featureBufferSize)
  {
    std::cout << "registerFace" << std::endl;

    return 0;
  }

  int registerFace(int age, const char *buffer)
  {
    std::cout << "registerFace" << "; age:" << age << "; buffer:" << buffer << std::endl;

    return 0;
  }
};


#endif
