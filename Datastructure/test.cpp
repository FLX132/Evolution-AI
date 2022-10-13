#include <iostream>
#include <type_traits>
#include <exception>
#include "../Header/Matrixelement.h"
using namespace std;

struct No {}; 
  template<typename T, typename Arg> No operator== (const T&, const Arg&);

class test {
    public:
    bool operator== (const test&) {
        return true;
    }
};

template <typename M, typename Arg = M>
struct EqualExists
  {
    enum { value = !std::is_same<decltype(std::declval<M>() == std::declval<Arg>()), No>::value };
  };

int main() {
    try {
        cout<<EqualExists<test>::value;
    } catch(exception& e) {
        cout<<e.what();
    }
    cin.get();
    
}