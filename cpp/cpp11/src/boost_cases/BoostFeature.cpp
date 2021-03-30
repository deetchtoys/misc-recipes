#include "BoostFeature.h"
#include "../obj/ClassSet.h"

#include <iostream>
#include <vector>
#include <execinfo.h>
#include <utility>

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/any.hpp>

using namespace std;

template<typename T>
void printContainer(T t)
{
  for(typename T::value_type &value : t)
  {
    cout << *value;
  }
  cout << endl;
}

int ptrContainer(int argc, char **argv)
{
  // {
  //   std::vector<Person *> vecPersonPoint;
  //   vecPersonPoint.push_back(new Person(1));
  //   printContainer(vecPersonPoint);
  // }
  // Person p;
  // cout << p << endl;

  // {
  //   typedef boost::ptr_vector<Person> ptrVecPerson;
  //   ptrVecPerson pv1;
  //   pv1.push_back(new Person(1));
  //   pv1.push_back(new Person(2));
  //   pv1.push_back(new Person(3));
  //   pv1.erase(pv1.begin());
  //   // ptrVecPerson::iterator it= pv1.begin();
  //   printContainer<ptrVecPerson>(pv1);

  //   cout << "=====================" << endl;

  // }

  // boost::any a;
  // cout << a.empty() << endl;

  return 0;
}

int testBoostAny(int argc, char **argv)
{
  vector<boost::any> anyVec;
  anyVec.push_back(string("hello"));
  anyVec.push_back(12);
  anyVec.push_back(Person(10));
  anyVec.push_back(shared_ptr<Person>(new Person(20)));
  anyVec.push_back(make_shared<Person>(10));

  for (vector<boost::any>::iterator it = anyVec.begin(); it != anyVec.end(); ++it)
  {
    if (string *s = boost::any_cast<string>(&(*it)))
    {
      cout << "string ---> " << *s << endl;
    }
    else if(Person *p = boost::any_cast<Person>(&(*it)))
    {
      cout << "person ---> " << *p << endl;
    }
    else
    {
      try
      {
        cout << "int ---> " << boost::any_cast<int>(*it) << endl;
      }
      catch(boost::bad_any_cast &)
      {
        cout << "Oops! \n" << endl;
      }
    }
  }

  return 0;
}

int BoostFeature::examples(int argc, char **argv)
{
  return testBoostAny(argc, argv);
}
