#include "FaceKernel.h"


extern "C" {
  FaceManager * FaceManagerNew() {
    return new FaceManager();
  }

  void FaceManagerDelete(FaceManager * faceManager) {
    delete faceManager;
  }

  // int FaceManagerRegisterFace(FaceManager * faceManager,
  //                             char *imageBuffer,
  //                             int imageBufferSize,
  //                             char *featureBuffer,
  //                             int featureBufferSize) {

  //   return faceManager->registerFace(imageBuffer, imageBufferSize, featureBuffer, featureBufferSize);
  // }

  int FaceManagerRegisterFace(FaceManager * faceManager, int age, const char *buffer) {

    return faceManager->registerFace(age, buffer);
  }
}
