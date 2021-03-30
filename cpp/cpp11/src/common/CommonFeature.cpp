#include "CommonFeature.h"

#include <iostream>

using std::cout;
using std::endl;
using std::string;

int useAuto(int argc, char **argv)
{
    int a = 10;
    auto aa = a;
    // const int *aP = &a;
    cout << aa << endl;
    aa += 1;
    cout << aa << endl;

    const int aC = 10;
    auto aaC = aC;
    cout << aaC << endl;

    aaC += 1;
    cout << aaC << endl;

    // auto aaP = aP;
    //*aaP = 123; // const int *, read-only

    return 0;
}

class CommonInfo
{
  public:
    CommonInfo(std::initializer_list<CommonInfo> vals)
    {
        // for (auto info = vals.begin(); info!=vals.end(); ++info)
        // {
        //     _num = info->_num;
        // }

        cout << "CommonInfo(std::initializer_list<CommonInfo> vals)" << endl;
    }

    CommonInfo(std::initializer_list<int> vals)
    {
        // for (auto info = vals.begin(); info!=vals.end(); ++info)
        // {
        //     _num = info->_num;
        // }

        cout << "CommonInfo(std::initializer_list<int> vals)" << endl;
    }

    CommonInfo()
    {
        cout << "call CommonInfo()" << endl;
    }

    explicit CommonInfo(int, int, int)
    {
        cout << "call CommonInfo(int, int, int)" << endl;
    }

    CommonInfo(const CommonInfo &commonInfo)
    {
        cout << "CommonInfo(const CommonInfo &commonInfo)" << endl;
    }

    CommonInfo(CommonInfo &commonInfo)
    {
        cout << "(CommonInfo &commonInfo)" << endl;
    }

    CommonInfo(CommonInfo &&commonInfo)
    {
        cout << "CommonInfo(CommonInfo &&commonInfo)" << endl;
    }


  private:
    int _num;
};

int useUniformInit(int argc, char **argv)
{
    CommonInfo commonInfo = CommonInfo();
    CommonInfo commonInfo1 = {1,2};
    CommonInfo commonInfo2 = CommonInfo{1,2,3};
    CommonInfo commonInfo3 {1,2,3};
    CommonInfo commonInfo4 = {1,2,3};

    return 0;
}

int moveTest(int argc, char **argv)
{
    CommonInfo commonInfo;
    CommonInfo c = std::move(commonInfo);

    return 0;
}

int newStringTest(int argc, char **argv)
{
    std::string s = "\\\\a";
    cout << s << endl;
    s = R"(\\\\a)";
    cout << s << endl;
    s = R"nc(a\
b\nc()
)nc";
    cout << s << endl;
    return 0;
}

int testLambda(int argc, char **argv)
{
    int val = 12;
    auto f = [val] {return val;};
    val = 13;

    cout << f() << endl;
    return 0;
}

template <typename T> void templateFunc(T &a)
{
    *a = 2;
}

int testTemplate(int argc, char **argv)
{
    int *const a = 0;
    templateFunc(a);
    cout << a << endl;
    return 0;
}

class A {
  public:
    void test();
  private:
    char a;
};

class B : virtual public A {
  private:
    char b;
};

class C : virtual public A {
  private:
    char c;
};

class D : virtual public B, virtual public C {
  private:

};

class E : virtual public A
{

};

int sizeofClass(int argc, char **argv)
{
    cout << sizeof(A) << endl;
    cout << sizeof(B) << endl;
    cout << sizeof(C) << endl;
    cout << sizeof(D) << endl;
    cout << sizeof(E) << endl;

    return 0;
}

int CommonFeature::examples(int argc, char **argv)
{
    return sizeofClass(argc, argv);
}
