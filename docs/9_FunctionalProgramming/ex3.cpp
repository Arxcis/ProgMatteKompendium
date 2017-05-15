#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <string>
#include <iomanip>

#include <functional>

using namespace std::placeholders;

template <typename T>
std::ostream& myout(std::ostream& os, const T& container)
{
    for(auto x : container) os << x << " ";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) { return myout(os, v); }

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::list<T>& v) { return myout(os, v); }


auto map = [] (auto p, auto& x) {
  for(auto& ob : x) ob = p(ob);
};

auto count = [] (auto p, auto& x) {
  int c = 0;
  for(const auto& ob : x) if(p(ob)) c++;
  return c;
};

auto filter = [] (auto p, auto& x) {
  x.erase(std::remove_if(x.begin(), x.end(), p),x.end());
};

template <typename T>
bool vectorbinsearch(const std::vector<T>& v, const T& val, int start, int end)
{
  if(start > end) return false;
  int i = (start + end) / 2;
  if(v[i] < val) return  vectorbinsearch(v,val,i+1,end);
  else if(v[i] > val) return  vectorbinsearch(v,val,start,i-1);
  else return true;
}

struct MyArray {
    int size() const {return 10000;};
    int operator[](int i) const {return i*i+2;};
} myArray;

int main() {
    std::vector<int> v(100,0);
    std::list<int> l(100,0);
    map([](auto x){static int c = -1; c++; return c;},v);
    map([](auto x){return x*x+2;},v);
    map([](auto x){static int c = -1; c++; return c;},l);
    map([](auto x){return x*x+2;},l);

    std::cout << v << std::endl << l << std::endl;

    auto linsearch = [] (auto& v, auto val){
      for(auto& x: v) if(x == val) return true;
      return false;
    };

    std::cout << "That 54 belongs to the list is " << std::boolalpha << linsearch(v,54) << std::endl;
    std::cout << "That 18 belongs to the list is " << std::boolalpha << linsearch(l,18) << std::endl;

    auto binsearch2 = [] (const auto& v, const auto& val)->bool{
       return vectorbinsearch(v,val,0,v.size()-1);};

    std::cout << "That 54 belongs to the list is " << std::boolalpha << binsearch2(v,54) << std::endl;
    std::cout << "That 18 belongs to the list is " << std::boolalpha << binsearch2(v,18) << std::endl;

    auto binsearch = [] (const auto& v, const auto& val)->bool {
      auto helper = [] (const auto& v, const auto& val, int start, int end, const auto& f) {
        if(start > end) return false;
        int i = (start + end) / 2;
        if(v[i] < val) return f(v,val,i+1,end,f);
        else if(v[i] > val) return f(v,val,start,i-1,f);
        else return true;
      };
      return helper(v,val,0,v.size()-1,helper);
    };

    std::cout << "That 54 belongs to the list is " << std::boolalpha << binsearch(v,54) << std::endl;
    std::cout << "That 18 belongs to the list is " << std::boolalpha << binsearch(v,18) << std::endl;
    std::cout << "That 18 belongs to the list is " << std::boolalpha << binsearch(myArray,18) << std::endl;
}
