#include <iostream>
#include <functional>

//
// Using this namespace helps a lot with making std::bind readable
//
using namespace std::placeholders;

//
// A normal function
//
int square10()
{
  return 10*10;
}

//
// A normal function
//
int square(int n)
{
  return n*n;
}

//
// A normal function
//
int times(int n, int m)
{
  return n*m;
}

//
// A Function object (operator() is overloaded)
//
struct MySquare {
  int operator() (int n) {return n*n;};
} mySquare;

//
// A function object
//
struct MySquare10 {
  int operator() () {return 10*10;};
} mySquare10;

//
// A class with members and methods
//
struct MyNumber {
  int number;
  int times(int m) {return m*number;};
};

MyNumber operator*(MyNumber n1, MyNumber n2)
{
  MyNumber ret;
  ret.number = n1.number * n2.number;
  return ret;
}




int main() {
    std::function<int(void)> f;       // should be called with f()
    std::function<int(int)> g;        // should be caled with g(int)
    std::function<int(MyNumber&)> h;  // should be called with h(object)

    //
    // Assigning usual functions
    //
    g = square;
    std::cout << g(10) << std::endl;

    f = square10;
    std::cout << f() << std::endl;

    //
    // Assigning usual functions by binding parameter values
    //
    f = std::bind(square,10);
    std::cout << f() << std::endl;

    g = std::bind(times,_1,_1);
    std::cout << g(10) << std::endl;

    //
    // Assigning function objects (with or without binding)
    //
    g = mySquare;
    std::cout << g(10) << std::endl;

    f = mySquare10;
    std::cout << f() << std::endl;

    f = std::bind(mySquare,10);
    std::cout << f() << std::endl;


    //
    // Assigning an object member or method
    //
    MyNumber n1;
    h = &MyNumber::number;
    n1.number = 10*10;
    std::cout << h(n1) << std::endl;

    n1.number = 10;
    f = std::bind(&MyNumber::times,n1,10);
    std::cout << f() << std::endl;

    g = std::bind(&MyNumber::times,n1,_1);
    std::cout << g(10) << std::endl;

    //
    // Now lets do lambdas (= unnamed function objects, sort of)
    //

    //
    // Inline evaluation of lambdas
    //
    std::cout << [] () {return 10*10;}() << std::endl;
    std::cout << [] (int number) {return number * number;}(10) << std::endl;



    //
    // Variable declaration
    //
    int m =  [] (int number) {return number * number;}(10);
    std::cout << m << std::endl;

    m = 10;
    // m is 10 here
    std::cout << [&p = m, q = m + 1] ()-> int {p += 1; return (p-1)*(q-1);}() << std::endl;
    // m is 11 here

    //
    // Assigning a lambda to a std::function
    //
    g = [] (int number) {return number * number;};
    std::cout << g(10) << std::endl;

    f = [] () {return 10*10;};
    std::cout << f() << std::endl;

    //
    // Generic lambdas
    //

    //
    // the function mul can be used on any class with operator* defined.
    //
    auto mul = [] (auto x, auto y) {return x*y;};
    std::cout << mul(10,10) << std::endl;
    std::cout << mul(10.0f, 10.0f) << std::endl;
    n1.number = 10;
    MyNumber n2; n2.number = 10;
    std::cout << (n1*n2).number << std::endl;
    std::cout << mul(n1,n2).number << std::endl;

    //
    // std::bind is not needed, and can always be replaced with lambdas(?)
    //

    //
    // binding using lambdas
    //
    f = [] () {return square(10);};
    std:: cout << f() << std::endl;

    g = [] (auto x) {return times(x,x);};
    std::cout << g(10) << std::endl;

    n1.number = 10*10;
    h = [] (auto x) {return x.number;};
    std::cout << h(n1) << std::endl;

    n1.number = 10;
    f = [&ln1=n1] () {return ln1.times(10);};
    std::cout << f() << std::endl;

    g = [&ln1=n1] (auto x) {return ln1.times(x);};
    std::cout << g(10) << std::endl;
}
