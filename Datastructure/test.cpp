#include <iostream>
using namespace std;

int main() {
    int *p = NULL;
    delete p;
    if(p) {
        cout<<"Hello";
    }
    cout<<"test";
    delete p;
}