#include <functional>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cmath>
#include <list>
#include <string>
#include <array>

using namespace std::placeholders;

// I use this for debugging
void Exit(const char* st)
{
    std::cout << st;
    exit(0);
}

class MyList {
public:
    MyList take(int n) const  {
        MyList res;
        res.f = f;
        res.b = b;
        int j = -1; int i;
        for(i=0; j < n && (size == -1 || i < size); i++) {
            if(b(i)) j++;
            }
        if(n>j) Exit("take n out of bounds");
        res.size = i;
        return res;
        };

    int operator[](int n) const {
        int j = -1; int i;
        for(i=0; j < n && (size == -1 || i < size); i++) {
            if(b(i)) j++;
            }
        if(n>j) Exit("[] out of bounds");
        return f(i-1);
        ;};

    int length() const {
        if(size == -1) Exit("length of (possibly) infinite list");
        int j = 0;
        for(int i = 0; i < size; i++) {
            if(b(i)) j++;
            }
        return j-1;
        }


    MyList map(std::function<int(int)> nf) const {
        MyList ret;
        ret.f = [of=f, lnf=nf] (int x) {
          return lnf(of(x));
        };
        ret.b = b;
        return ret;
        };

    MyList filter(std::function<bool(int)> nb) const {
        MyList ret;
        ret.f = f;
        ret.b = [ob=b,of=f,lnb=nb] (int x) {return ob(x) && !lnb(of(x));};
        return ret;
        };

    int head() const {return this->operator[](0);};

    MyList tail() const {
        return drop(1);
        }

    MyList drop(int n) const {
        MyList ret;
        int j = -1; int i = 0;
        for(; j < n && (size == -1 || i < size); i++) {
            if(b(i)) j++;
            }
        if(j < n) Exit("drop out of bonds");
        ret.b = [ob=b,i](int x) {return ob(x+i-1);};
        ret.f = [of=f,i](int x) {return of(x+i-1);};
        if(size != -1) ret.size = size-n;
        return ret;
        }

    MyList zipWith(std::function<int(int,int)> p, MyList v) {
        MyList ret;
        ret.b = [] (int x) {return true;};
        ret.f = [lv=v,lo=*this,lp=p] (int x) {return lp(lo[x],lv[x]);};
        int slength = -1;
        if(!infinite()) slength = length();
        if(!v.infinite() && v.length() < slength) slength = v.length();
        return ret;
        }

    MyList concat(MyList v) {
        if(infinite()) Exit("trying to concat with infinite list");
        MyList ret;
        ret.b = [lsize=size, lv=v, lb=b] (int x) {
            if(x < lsize-1) return lb(x);
            else return lv.b(x-lsize+1);
            };
        ret.f = [lsize=size, lv=v, lf=f] (int x) {
            if(x < lsize-1) return lf(x);
            else return lv.f(x-lsize+1);
            };
        if(v.size == -1) ret.size = -1;
        else ret.size = size + v.size - 1;
        std::cout << ret.size;
        return ret;
        }

    bool infinite() const {return size == -1;}
    bool empty() const {return length() == 0;}

private:
    std::function<int(int)> f = [] (int x) {return x;};
    std::function<bool(int)> b = [] (int x) {return true;};
    int size = -1;
};

auto take = [] (int n, auto m) {return m.take(n);};
auto filter = [] (auto p, auto m) {return m.filter(p);};
auto map = [=] (auto p, auto m) {return  m.map(p);};
auto head = [] (auto m) {return m.head();};
auto tail = [] (auto m) {return m.tail();};
auto drop = [] (int n, auto m) {return m.drop(n);};
auto length = [] (auto m) {return m.length();};
auto infinite = [] (auto m) {return m.infinite();};
auto empty = [] (auto m) {return m.empty();};
auto zipWith = [] (auto p, auto m1, auto m2) {return m1.zipWith(p,m2);};
auto concat = [] (auto m1, auto m2) {return m1.concat(m2);};

std::ostream& operator<<(std::ostream& o, MyList w)
{
    if(infinite(w)) Exit("ostream of (possibly) infinite list");
    o << "[";
    int len = length(w);
    for(int i = 0; i < len; i++) {
        o << w[i] << " ";
    }
    o << "]";
    return o;
}



int main(void)
{
    //
    // Numbers which are relative prime with 100
    //
    MyList num1;
    std::function<int(int,int)> gcd = [&gcd] (int m, int n)->int {
        if(n==0) return m;
        else return gcd(n,m%n);
        };
    num1 = filter([&gcd] (int x) {return gcd(100,x) != 1;},num1);
    std::cout << take(20,num1) << std::endl;

    //
    // Squares with remainder one when we divide by 8
    //
    MyList num2;
    std::function<int(int)> mymap = std::bind([] (int x)->int {return x*x;},_1);
    num2 = map(std::function<int(int)>(std::bind([] (int x)->int {return x*x;},_1)),num2);
    std::cout << take(20,num2) << std::endl;
    num2 = filter([] (int x) {return x % 8 != 1;},num2);
    std::cout << take(20,num2) << std::endl;


    //
    // Generate first 100000 primes - with a sieve
    //
    MyList primes;
    primes = drop(2,primes);
    auto pf = [] (int n, int x) {return (n != x) && (x % n == 0);};
    for(int i = 0; i < 785; i++) {
        int n = primes[i];
        primes = filter([=] (int x) {return pf(n,x);},primes);
    }
    std::cout << "filtering done" << std::endl;
    std::cout << primes[49999] << std::endl;


}
