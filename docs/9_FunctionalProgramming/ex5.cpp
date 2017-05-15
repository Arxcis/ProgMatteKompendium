#include <functional>
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std::placeholders;

template<typename T, typename U> std::ostream& operator<<(std::ostream& o, std::pair<T,U> x)
{
    o << "(" << x.first << "," << x.second << ")";
    return o;
}

template<typename T> std::ostream& operator<<(std::ostream& o, std::vector<T> w)
{
    std::for_each(w.begin(), w.end(), [&] (auto x) { o << x << " ";});
    return o;
}

typedef std::function<float(float)> func;
typedef std::pair<float,float> valpair;
typedef std::function<valpair(valpair)> funcpair;

int main(void)
{
    auto f = [] (float x) {return x*x;};
    auto g = [] (float x) {return x+2;};
    auto fg = std::bind(g,std::bind(f,_1));

    auto add = [] (func f, func g) {
        return [=] (float x) {
            return f(x)+g(x);
            };
        };

    auto mul = [] (func f, func g) {
        return [=] (float x) {
            return f(x)*g(x);
            };
        };

    auto com = [] (func f, func g) {
        return [=] (float x) {
            return f(g(x));
            };
        };

    auto addpair = [] (funcpair f, funcpair g)->funcpair{
        return [=] (valpair x) {
            return std::make_pair(f(x).first+g(x).first,f(x).second+g(x).second);
            };
        };

    auto mulpair = [] (funcpair f, funcpair g) {
        return [=] (valpair x) {
            return std::make_pair(f(x).first*g(x).first,f(x).first*g(x).second+f(x).second*g(x).first);
            };
        };

    auto compair = [] (funcpair f, funcpair g) {
        return [=] (valpair x) {
            return std::make_pair(f(g(x)).first, f(g(x)).second*g(x).second);
            };
        };

  /*  std::function<func(func,func)> add = [] (func f, func g) {
        return std::bind([] (func f, func g, float x) {
            return f(x)+g(x);
            },f,g,_1);
        };

    auto mul = [] (func f, func g) {
        return std::bind([] (func f, func g, float x) {
            return f(x)*g(x);
            },f,g,_1);
        };

    auto com = [] (func f, func g) {
        return std::bind(f,std::bind(g,_1));
        };


    auto addpair = [] (funcpair f, funcpair g)->funcpair{
        return std::bind([] (funcpair a, funcpair b, valpair x) {
            return std::make_pair(a(x).first+b(x).first,a(x).second+b(x).second);
            },f,g,_1);
        };

    auto mulpair = [] (funcpair f, funcpair g) {
        return std::bind([] (funcpair a, funcpair b, valpair x) {
            return std::make_pair(a(x).first*b(x).first,a(x).first*b(x).second+a(x).second*b(x).first);
            },f,g,_1);
        };

    auto compair = [] (funcpair f, funcpair g) {
        return std::bind([] (funcpair a, funcpair b, valpair x) {
            return std::make_pair(a(b(x)).first, a(b(x)).second*b(x).second);
            },f,g,_1);
        };
*/
    funcpair f1 = [](valpair x){return std::make_pair(x.first*x.first*x.first,3*x.first*x.first);};
    funcpair f2 = [](valpair x){return std::make_pair(std::sin(x.first),-std::cos(x.first));};
    funcpair f3 = compair(f2,compair(f1,f2));

    std::cout << f3(std::make_pair(2,0)) << " " << sin(pow(sin(2),3)) << " " << cos(pow(sin(2),3))*3*(sin(2)*sin(2))*cos(2)
        << std::endl;  // works

    std::cout << sizeof(f3) << std::endl;

return 0;

}
