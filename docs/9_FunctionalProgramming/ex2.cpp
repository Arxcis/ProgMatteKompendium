//
// Example 2: Brief introductioon to STL containers
//
#include <iostream>
#include <functional>
#include <algorithm>

//
// Dynamically sized arrays, good at direct access, bad at insertion
//
#include <vector>

//
// Dynamically sized lists, no access, good at insertion
//
#include <list>

//
// I want to use std::ostream with my containers.
//

template <typename T>
std::ostream& myout(std::ostream& os, const T& container)
{
    os << "[";
    for(auto x : container) os << x << " ";
    os << "]";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) { return myout(os, v); }

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::list<T>& v) { return myout(os, v); }

// insert other containers here.



int main() {
  std::vector<int> v(30,0);
  std::vector<int> w(30,0);
  std::list<int> l(30,0);

  //
  // Initialise with values 1..30
  //

  // old style C++
  {
    int c = 0;
    for(std::vector<int>::iterator it = w.begin(); it != w.end(); ++it, ++c) *it=c;
  }
  std::cout << w << std::endl;

  {
    int c = 0;
    for(auto& o : l) {
      o = c;
      ++c;
    }
  }
  std::cout << l << std::endl;


  std::for_each(v.begin(), v.end(), [] (auto& x) {static int c = -1; c++; x = c;} );
  std::cout << v << std::endl;


  //
  // Multiply every element in the container with 10
  //
  // old style c++
  for(std::vector<int>::iterator it = w.begin(); it != w.end(); ++it) *it = *it*10;
  std::cout << w << std::endl;

  for(auto& ob : v) ob = ob*10;
  std::cout << v << std::endl;

  std::for_each(l.begin(), l.end(), [] (auto& x) {x = x * 10;});
  std::cout << l << std::endl;

  //
  // Count number of elements greater than 100
  //
  // old style C++
  int c = 0;
  for(std::vector<int>::iterator it = w.begin(); it != w.end(); ++it) {
    if(*it > 100) c ++;
  }
  std::cout << c << std::endl;

  c = 0;
  for(auto ob : v) if(ob>100) c++;
  std::cout << c << std::endl;

  c = 0;
  std::for_each(l.begin(), l.end(), [&c] (auto& x) {if(x>100) c++;});
  std::cout << c << std::endl;

  c = std::count_if(l.begin(), l.end(), [] (auto x) {return x > 100;});
  std::cout << c << std::endl;

  //
  // remove if less than 100
  //
  auto newlast2 = std::remove_if(w.begin(), w.end(), [] (auto x) {return x < 100;});
  w.erase(newlast2,w.end());

  std::cout << w << std::endl;

  auto swap = [] (auto& x, auto& y) {
    auto temp = x;
    x = y;
    y = temp;
  };

  // old style c++ (but with a lambda)
  std::vector<int>::iterator itf = v.begin();
  std::vector<int>::reverse_iterator itb = ++v.rbegin();
  while(itf != itb.base()) {
    if(*itf < 100) {
      swap(*itf,*itb.base());
      ++itb;
    } else ++itf;
  }
  if(*itf >= 100) ++itf;
  v.erase(itf,v.end());
  std::cout << v << std::endl;

  //
  // Lets move towards a more functional syntax
  //
  std::vector<int> u(30,0);

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

  map([](auto x){static int c = -1; c++; return c;}, u);
  std::cout << u << std::endl;

  map([](auto x){return 10*x;}, u);
  std::cout << u << std::endl;

  c = count([](auto x){return x > 100;},u);
  std::cout << c << std::endl;

  filter([](auto x){return x < 100;},u);
  std::cout << v << std::endl;


}
