#include <iostream>
#include <cstdio>

#include <array>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include "FaceKernel.h"

extern "C" {
  FaceManager * FaceManagerNew()
  {
    return new FaceManager();
  }

  void FaceManagerDelete(FaceManager * faceManager)
  {
    delete faceManager;
  }

  int FaceManagerReg(FaceManager *faceManager,
                     const char *imgData,
                     int imgDataLength,
                     char *jsonResponseBuffer,
                     int jsonResponseBufferSize)
  {
    faceManager->reg();

    return 0;
  }

  int FaceManagerIdentify(FaceManager *faceManager,
                          const char *jsonFeatures,
                          char *jsonResponseBuffer,
                          int jsonResponseBufferSize)
  {
    std::cout << "jsonFeatures: " << jsonFeatures << std::endl;


    rapidjson::Document features;
    features.Parse(jsonFeatures);
    std::cout << "age: " << features["age"].GetInt() << std::endl;
    std::cout << "imgId: " << features["imgId"].GetString() << std::endl;
    rapidjson::Document::Array array = features["data"].GetArray();
    std::cout << "imgId: " << features["imgId"].GetString() << std::endl;

    faceManager->identify();
    return 0;
  }
}
