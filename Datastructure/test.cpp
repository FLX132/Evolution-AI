#include <iostream>
#include <type_traits>
#include <exception>
#include "../Header/Matrix.cpp"
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
    int x = 2;
    int y = 3;
    int i = 0;
    int *p = new int(8);
    cout<<p;
    delete p;
    vector<int> t({1, 2, 3, 4, 5, 6});
    cout<<t.size();
    Matrix<int> *test = new Matrix<int>(x, y, t);
    cout<<test->get_val(0, 1)<<endl;
    test->print();
    vector<int> m = test->get_column(1);
    for(int i = 0; i < m.size(); i++) {
        cout<<m[i]<<" ";
    }
    cout<<"\n";
    delete test;
}