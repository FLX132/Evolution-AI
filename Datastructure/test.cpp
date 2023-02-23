#include <iostream>
#include <type_traits>
#include <exception>
#include "../Header/Matrix.cpp"
using namespace std;

int main() {
    int x = 5;
    if(x > 4) {
        cout<<"is bigger than 4"<<endl;
    } else if(x > 3) {
        cout<<"is bigger than 3"<<endl;
    }
    // vector<int> n({1, 2, 3, 4 ,5 , 6, 7, 8, 9});
    // Matrix<int> m(3, 3, n);
    // Matrix<int> f(3, 3, n);
    // m.print();
    // cout<<""<<endl;
    // Matrix<int> g = m * f;
    // g.print();
}