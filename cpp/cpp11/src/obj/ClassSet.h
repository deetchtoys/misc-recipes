#ifndef CLASS_SET_H_
#define CLASS_SET_H_

#include <iostream>

class Person
{
 public:
  Person():age_(0)
  {
    std::cout << "Person()" << std::endl;
  }

  Person(int age):age_(age)
  {
    std::cout << "Person(int age)" << std::endl;
  }

  ~Person()
  {
    std::cout << "~Person(), age_:" << age_ << std::endl;
  }

  void setAge(int age)
  {
    age_ = age;
  }

  friend std::ostream & operator<< (std::ostream &os, Person &person);

 private:
  int age_;
  char *addr_;
};

std::ostream & operator<< (std::ostream &os, Person &person)
{
  os << person.age_ << std::endl;
  return os;
}

#endif
