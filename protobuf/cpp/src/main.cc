#include <iostream>
#include "messages/school.pb.h"

using namespace std;


int main()
{
  google::protobuf::
  tutorial::Student student;
  student.set_age(20);
  student.set_name("wangdiqi");
  string *name = student.mutable_name();
  student.SetExtension(tutorial::classNo, 10);
  cout << student.name() << ":" << student.age() << ":" << student.GetExtension(tutorial::classNo) <<endl;
  string output;
  student.SerializeToString(&output);
  cout << output << endl;
  cout << output.size() << endl;

  return 0;
}
