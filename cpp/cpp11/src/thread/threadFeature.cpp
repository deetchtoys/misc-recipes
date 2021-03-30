#include "threadFeature.h"

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <map>
#include <cassert>
#include <future>
#include <random>
#include <chrono>
#include <string>

using namespace std;

struct B;

struct A{
  A()
  {
    cout << "A()" << endl;
  }

  ~A()
  {
    cout << "~A" << endl;
  }
  shared_ptr<B> b;
};

struct B{
  B()
  {
    cout << "B()" << endl;
  }

  ~B()
  {
    cout << "~B" << endl;
  }

  weak_ptr<A> a;
};

int sharedPtrTest(int argc, char **argv)
{
  shared_ptr<A> a(new A());
  cout << "a:" << a.use_count() << endl;
  shared_ptr<B> b(new B());
  cout << "b:" << b.use_count() << endl;
  a->b = b;
  cout << "a:" << a.use_count() << endl;
  cout << "b:" <<b.use_count() << endl;
  b->a = a;
  cout << "a:" << a.use_count() << endl;
  cout << "b:" << b.use_count() << endl;

  return 0;
}

class CustomerData
{
 public:
  typedef vector<pair<string, int>> EntryList;
  typedef map<string, EntryList> Map;
  typedef shared_ptr<Map> MapPtr;

  CustomerData():data_(new Map)
  {}

  CustomerData(MapPtr mapPtr):data_(mapPtr)
  {
  }

  int query(const string &customer, const string &stock) const
  {
    MapPtr data = getData();
    const EntryList &entries = (*data)[customer];
    return findEntry(entries, stock);
  }

  void update(const string &customer, const EntryList &entries)
  {
    lock_guard<mutex> lockGuard(dataMutex_);
    if (!data_.unique())
    {
      MapPtr newData(new Map(*data_));
      data_.swap(newData);
      cout << "swap the data" << endl;
    }

    assert(data_.unique());
    (*data_)[customer] = entries;
    cout << "needn't use swap" << endl;
  }

 private:
  int findEntry(const EntryList &entries, const string &key) const
  {
    for(auto info : entries)
    {
      if (info.first == key)
      {
        return info.second;
      }
    }

    return 0;
  }

  MapPtr getData() const
  {
    lock_guard<mutex> lockGuard(dataMutex_);
    return data_;
  }

  MapPtr data_;
  mutable mutex dataMutex_;
};

void initData(CustomerData &customerData)
{
  while (1)
  {
    int length = 10;
    default_random_engine drg(clock());
    uniform_int_distribution<int> uid(0,length);
    CustomerData::EntryList entryList;
    entryList.reserve(length);
    int bucketIndex = 0;
    for (int i = 0; i < length; ++i)
    {
      int value = uid(drg);
      bucketIndex = value % 10;
      string valuekey = "key-" + to_string(value % length);
      entryList.push_back(pair<string, int>(valuekey, value));
    }

    string bucketName[] = {"bucket-0",
                           "bucket-1",
                           "bucket-2",
                           "bucket-3",
                           "bucket-4",
                           "bucket-5",
                           "bucket-6",
                           "bucket-7",
                           "bucket-8",
                           "bucket-9"};
    customerData.update(bucketName[bucketIndex], entryList);
    cout << "===================" << endl;
    cout << "update bucket name:" << bucketName[bucketIndex] << ", size:" << entryList.size() << endl;
    cout << "===================" << endl;
    this_thread::sleep_for(chrono::duration<long double>(5));
  }
}

void readData(CustomerData &customerData, string &bucketName, string &keyName)
{
  int result = customerData.query(bucketName, keyName);
  cout << "in bucketname: " << bucketName << " found result:" << result << endl;
}

int copyOnWriteTest(int argc, char **argv)
{
  CustomerData customerData;
  future<void> fUpdate = async(launch::async, initData, std::ref(customerData));
  default_random_engine drg(clock());
  uniform_int_distribution<int> uid(0,10);
  string bucketName[] = {"bucket-0",
                         "bucket-1",
                         "bucket-2",
                         "bucket-3",
                         "bucket-4",
                         "bucket-5",
                         "bucket-6",
                         "bucket-7",
                         "bucket-8",
                         "bucket-9"};
  while (1)
  {
    for (int i = 0; i < 5; ++i)
    {
      int value = uid(drg);
      string s = "key-" + to_string(value);
      future<void> fRead = async(launch::async, readData, ref(customerData), ref(bucketName[value]), ref(s));
    }

    // this_thread::sleep_for(chrono::duration<long double>(2));
  }

  return 0;
}

int threadTest(int argc, char **argv)
{
  future<int> f = async(std::launch::async,
                        []()
                        {
                          this_thread::sleep_for(chrono::duration<int>(2));
                          cout << this_thread::get_id() << endl;
                          return 1;
                        });

  cout << this_thread::get_id() << endl;
  f.get();

  return 0;
}



int ThreadFeature::examples(int argc, char **argv)
{
  return threadTest(argc, argv);
}
