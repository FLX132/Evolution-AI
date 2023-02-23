#include "AllHeaders.h"
#include "Matrixelement.h"
using namespace std;

template <typename T> class Matrix {
    private:
        Matrixelement<T>* reference_start = NULL;
        int& current_x;
        int& current_y;

    public:
        Matrix(int x, int y, T values[]);
        Matrix(int x, int y);
        ~Matrix();
        void autofill(T values[]);
        vector<T&> get_row(int y);
        vector<T&> get_column(int x);
        int get_x();
        int get_y();
        T get_val(int x, int y);
        Matrix<T>& operator*(Matrix<T> mul);
        Matrix<T>& operator+(Matrix<T> add);
        Matrix<T>& operator+=(Matrix<T>& add_is);
        Matrix<T>& operator*=(Matrix<T>& mul_is);
        //template <class M = T, enable_if<is_floating_point<M>::value, bool> == true> {
        //    void rand_fill();
        //}
};