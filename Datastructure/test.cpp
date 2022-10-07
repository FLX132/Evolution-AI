#include <iostream>
using namespace std;

int main() {
    int *p = new int(20);
    delete p;
    bool m = (p == NULL);
    cout<<m;
}