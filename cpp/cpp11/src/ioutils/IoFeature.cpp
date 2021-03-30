#include "IoFeature.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int IoFeature::examples(int argc, char **argv)
{
  return ReadFile(argc, argv);
}

int IoFeature::ReadFile(int argc, char **argv)
{
  std::ifstream fileHandler("/home/seventh/feature-data.txt");
  std::stringstream buffer;
  buffer << fileHandler.rdbuf();
  std::string contents(buffer.str());
  fileHandler.close();
  cout << contents.size() << endl;
  std::ofstream outfileHandler;
  outfileHandler.open("/tmp/kernel.log");
  outfileHandler << "file length: " << contents.size() << std::endl;
  outfileHandler << "contents: " << contents;
  outfileHandler.close();

  return 0;
}
