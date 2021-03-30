#include "commonUtil.h"

#include <iostream>
#include <utility>
#include <tuple>
#include <memory>
#include <vector>

using std::cout;
using std::endl;
using std::string;

void f(std::pair<int, const char *>)
{}

void g()
{}

int pairTest(int argc, char **argv)
{
    std::pair<string , string> pairChar = std::make_pair("aaa", "bbb");
    cout << pairChar.first << ":" << pairChar.second << endl;
    auto t = std::make_tuple(77, "hello", 1.1);
    int a;
    string s;
    float f;
    std::tie(a, s, f) = t;
    cout << a << ":" << s << ":" << f << endl;

    return 0;
}

// int pairTest(int argc, char **argv)
// {
//     return 0;
// }

int smartPointTest(int argc, char **argv)
{
    std::shared_ptr<string> pNico(new string("nico"));
    std::shared_ptr<string> pJutta(new string("jutta"));

    (*pNico)[0] = 'N';
    pJutta->replace(0, 1, "J");

    std::vector<std::shared_ptr<string>> whoMadeCoffee;
    whoMadeCoffee.push_back(pJutta);
    whoMadeCoffee.push_back(pJutta);
    whoMadeCoffee.push_back(pNico);
    whoMadeCoffee.push_back(pJutta);
    whoMadeCoffee.push_back(pNico);

    for (auto ptr : whoMadeCoffee)
    {
        cout << *ptr << "   ";
    }
    cout << endl;

    *pNico = "Nicolai";

    for (auto ptr : whoMadeCoffee)
    {
        cout << *ptr << "   ";
    }

    cout << endl;

    return 0;
}



int CommonUtil::examples(int argc, char **argv)
{
    return smartPointTest(argc, argv);
}
