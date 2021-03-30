#include "ContainerFeature.h"

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <array>
#include <deque>
#include <iterator>
#include <list>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <cstdio>
#include <regex>
#include <locale>

using namespace std;

template<typename T>
void printElement(T &t)
{
  for(auto i : t)
  {
    cout << i << endl;
  }
  cout << "===========================" << endl;
}

template<typename T, typename T1>
class FunctionObj
{
 public:
  void operator()(T1 &t)
  {
    t_.push_back(t);
  }
  FunctionObj(T &t):t_(t)
  {
  }
 private:
  T &t_;
};

int vectorTest(int argc, char **argv)
{
  vector<int> vectorInt = {2,5,9,1,6,7,4,8,3};
  printElement(vectorInt);
  sort(vectorInt.begin(), vectorInt.end());
  printElement(vectorInt);

  cout << "size:" << vectorInt.size() << "capacity:" << vectorInt.capacity() << "max_size:" << vectorInt.max_size() << endl;

  vectorInt.reserve(100);
  cout << "size:" << vectorInt.size() << "capacity:" << vectorInt.capacity() << "max_size:" << vectorInt.max_size() << endl;

  vectorInt.reserve(10);
  cout << "size:" << vectorInt.size() << "capacity:" << vectorInt.capacity() << "max_size:" << vectorInt.max_size() << endl;

  vectorInt.resize(20);
  cout << "size:" << vectorInt.size() << "capacity:" << vectorInt.capacity() << "max_size:" << vectorInt.max_size() << endl;

  /* invalid example, it become invalid after erase
  for(vector<int>::iterator it = vectorInt.begin(); it != vectorInt.end(); ++it)
  {
    if (*it == 3)
    {
      cout << *it << endl;
      vectorInt.erase(it);
      cout << *it << endl;
      cout << "--------" << endl;
    }
  }
  */

  /* invalid example, it become invalid after insert
  for(vector<int>::iterator it = vectorInt.begin(); it != vectorInt.end(); ++it)
  {
    if (*it == 3)
    {
      cout << *it << endl;
      vectorInt.insert(it, 111);
      cout << *it << endl;
      cout << "--------" << endl;
    }
  }
  */

  printElement(vectorInt);
  // vector<int> vectorInt2;
  // for_each(vectorInt.begin(), vectorInt.end(), [&vectorInt2] (int value)
  //          {
  //            vectorInt2.push_back(value);
  //          });

  // printElement(vectorInt2);
  // sort(vectorInt2.begin(), vectorInt2.end(), greater<int>());
  // printElement(vectorInt2);

  vector<int> vectorInt3;
  for_each(vectorInt.begin(), vectorInt.end(), FunctionObj<vector<int>, int>(vectorInt3));
  printElement(vectorInt3);

  vector<int> vectorInt4;
  transform(vectorInt.begin(),
            vectorInt.end(),
            insert_iterator<vector<int>>(vectorInt3, vectorInt3.begin()),
            [](int a)
            {
              return a+10;
            });
  printElement(vectorInt3);

  return 0;
}

int arrayTest(int argc, char **argv)
{
  array<int, 10> arrInt = {};
  printElement(arrInt);

  return 0;
}

int dequeTest(int argc, char **argv)
{
  deque<int> dequeInt;
  cout << "size:" << dequeInt.size() << endl;
  back_insert_iterator<deque<int>> it = back_inserter(dequeInt);
  for(int i = 0; i != 10; ++i)
  {
    *it = i;
  }

  copy(dequeInt.begin(), dequeInt.end(), ostream_iterator<int>(cout, "\n"));

  dequeInt = deque<int>();
  copy(istream_iterator<int>(cin), istream_iterator<int>(), insert_iterator<deque<int>>(dequeInt, dequeInt.begin()));
  copy(dequeInt.begin(), dequeInt.end(), ostream_iterator<int>(cout, "\n"));

  return 0;
}

int listTest(int argc, char **argv)
{
  list<int> listInt = {9,2,12,3,4,6,7,85,1};
  printElement(listInt);
  listInt.sort([](int lValue, int rValue)
               {
                 return lValue > rValue;
               });
  listInt.remove(2);
  printElement(listInt);
  auto newEnd = remove(listInt.begin(), listInt.end(), 3);
  if (newEnd != listInt.end())
  {
    listInt.erase(newEnd, listInt.end());
  }

  printElement(listInt);

  listInt = {1,2,3,4,5,6,7,8,9};
  auto destIt = find(listInt.begin(), listInt.end(), 5);
  cout << *listInt.rbegin() << endl;
  if (destIt != listInt.end())
  {
    cout << *destIt << "####" << *reverse_iterator<list<int>::iterator>(destIt) << endl;
  }

  return 0;
}

int setTest(int argc, char **argv)
{
  set<int> setInt;
  for (int i = 1; i < 10; ++i)
  {
    pair<set<int>::iterator, bool> result = setInt.insert(i);
    cout << *result.first << ":" << (result.second ? "true" : "false") << endl;
  }

  for (int i = 1; i < 10; ++i)
  {
    pair<set<int>::iterator, bool> result = setInt.insert(i);
    cout << *result.first << ":" << (result.second ? "true" : "false") << endl;
  }

  return 0;
}

int mapTest(int argc, char **argv)
{
  map<string, int> stringMapInt;
  for (int i = 1; i < 10; ++i)
  {
    pair<map<string, int>::iterator, bool> result = stringMapInt.insert({"wangdiqi", 1});
    cout << result.first->first << ":" << result.first->second << "###" << (result.second ? "true" : "false") << endl;
  }
  cout << stringMapInt["hello"] << endl;
  for_each(stringMapInt.begin(), stringMapInt.end(), [] (pair<string, int> value)
           {
             cout << value.first << ":" << value.second << endl;
           });

  return 0;
}

int stringTest(int argc, char **argv)
{
  string s("123456789");
  // cout << s << "; s.size:" << s.size() << endl;
  // const char *cStr = s.data();
  // printf("%s\n", cStr);
  // cout << cStr << "; strlen size:" << strlen(cStr) << endl;

  // const char *cStr1 = s.c_str();
  // printf("%s\n", cStr);
  // cout << cStr1 << "; strlen size:" << strlen(cStr1) << endl;
  // s = "hello";
  // cout << cStr1 << "; strlen size:" << strlen(cStr1) << endl;

  // const char *tStr = "123456";
  // char *p = (char *)memchr(tStr, '3', strlen(tStr));

  // if (0 == nullptr)
  // {
  //   cout << "0 == nullptr" << endl;
  // }
  // char a[10];
  // a[9] = 'a';
  // strcpy(a, s.data());
  // cout << a << endl;

  // memset(a, 0, 10);
  // a[9] = 'a';
  // strcpy(a, s.c_str());
  // cout << a << endl;
  string::size_type pos = s.find("456");
  s = s.substr(pos, 3);
  cout << s << endl;

  return 0;
}

int regexTest(int argc, char **argv)
{
  string s = "<name>wang</name>\n<age>2011111</age>\n";
  regex sampleRegex("<([a-zA-Z]*)>(.*?)</[a-zA-Z]*>");
  smatch sm;
  auto pos = s.cbegin();
  for( ; regex_search(pos, s.cend(), sm, sampleRegex); pos = sm.suffix().first)
  {
    cout << "match:" << sm.str() << endl;
    cout << "tag:" << sm.str(1) << endl;
    cout << "value:" << sm.str(2) << endl;
  }

  // string data = "<person>\n"
  //               " <first>Nico</first>\n"
  //               " <last>Josuttis</last>\n"
  //               "</person>\n";
  // regex reg("<(.*)>(.*)</\\1>");
  // auto pos = data.cbegin();
  // auto end = data.cend();
  // smatch m;
  // for ( ; regex_search(pos, end, m, reg); pos = m.suffix().first)
  // {
  //   cout << "match: " << m.str() << endl;
  //   cout << "m.suffix():" << m.suffix() << endl;
  //   cout << " tag:" << m.str(1) << endl;
  //   cout << " value: " << m.str(2) << endl;
  // }

  return 0;
}

template<typename T1, typename T2>
class WrapperPair
{
 public:
  WrapperPair(std::pair<T1, T2> value) :value_(value){}
  std::pair<T1, T2> value_;
};

template <typename T1, typename T2>
std::ostream & operator << (std::ostream &os, const WrapperPair<T1, T2> &p)
{
  return os << p.value_.first << p.value_.second;
}

int ioTest(int argc, char **argv)
{
  // std::pair<int, long> p(1, 2);
  // std::cout << p << std::endl;

  std::vector<WrapperPair<int, long>> v;
  v.push_back(WrapperPair<int, long>(std::make_pair(1,2)));
  std::copy(v.begin(), v.end(), std::ostream_iterator<WrapperPair<int, long>>(std::cout, "\n"));

  // cin.tie(&cout);

  // int a;
  // cin >> a;

  return 0;
}

int localeTest(int argc, char **argv)
{
  cin.imbue(locale::classic());

  cout.imbue(locale("en_US.UTF-8"));

  cout << "input floating-point values(classic notation): " << endl;
  double value;
  while (cin >> value)
  {cout << value << endl;}

  return 0;
}



int ContainerFeature::examples(int argc, char **argv)
{
  return localeTest(argc, argv);
}
