#include "AllHeaders.h"
#include "Matrixelement.cpp"
using namespace std;

template <typename T> class Matrix {
    private:
        Matrixelement<T>* reference_start = NULL;
        int current_x;
        int current_y;
        bool error_in_construct = false;

    public:
        Matrix(int x, int y, vector<T> values);
        Matrix(int &x, int &y);
        ~Matrix();
        void autofill(T values[]);
        vector<T> get_row(int y);
        vector<T> get_column(int x);
        int get_x();
        int get_y();
        T get_val(int x, int y);
        void print();
        Matrix<T>& operator*(Matrix<T> mul);
        Matrix<T>& operator+(Matrix<T> add);
        Matrix<T>& operator+=(Matrix<T>& add_is);
        Matrix<T>& operator*=(Matrix<T>& mul_is);
        //template <class M = T, enable_if<is_floating_point<M>::value, bool> == true> {
        //    void rand_fill();
        //}
};

template <class T>
Matrix<T>::Matrix(int x, int y, vector<T> values) {
    if(x*y != (values.size())) {
        std::cout<<"false formatted init-list";
        Matrix<T>::error_in_construct = true;
        delete this;
    } else {
        Matrix<T>::reference_start = new Matrixelement<T>(x-1, y-1, NULL, NULL);
        Matrix<T>::reference_start->init_sec();
        std::cout<<"Matrix init "<<values.size()<<std::endl;
        int count = 0;
        for(int i = 0; i < y; i++) {
            for(int j = 0; j < x; j++) {
                cout<<i<<" "<<j<<" "<<count<<std::endl;
                Matrix<T>::reference_start->set_iterate(j, i, values[count]);
                count++;
            }
        }
        Matrix<T>::current_x = x;
        Matrix<T>::current_y = y;
    }
}

template <class T>
Matrix<T>::Matrix(int& x, int& y) {
    Matrix<T>::reference_start = new Matrixelement<T>(x-1, y-1, NULL, NULL);
    Matrix<T>::reference_start->init_sec();
    Matrix<T>::current_x = x;
    Matrix<T>::current_y = y;
}

template <class T>
Matrix<T>::~Matrix() {
    if(!Matrix<T>::error_in_construct) {
        Matrix<T>::reference_start->del_method(delete_helper::down, delete_helper::down);
        delete Matrix<T>::reference_start;
    }
    Matrix<T>::reference_start == NULL;
}

template <class T>
void Matrix<T>::autofill(T values[]) {
    int count = 0;
    for(int i = 0; i < this->get_y(); i++) {
        for(int j = 0; j < this->get_x(); j++) {
            Matrix<T>::reference_start->set_iterate(j, i, values[count]);
            count++;
        }
        count++;
    }
}

template <class T>
vector<T> Matrix<T>::get_row(int y) {
    return Matrix<T>::reference_start->get_row(y);
}

template <class T>
vector<T> Matrix<T>::get_column(int x) {
    return Matrix<T>::reference_start->get_column(x);
}

template <class T>
int Matrix<T>::get_x() {
    return Matrix<T>::current_x;
}

template <class T>
int Matrix<T>::get_y() {
    return Matrix<T>::current_y;
}

template <class T>
T Matrix<T>::get_val(int x, int y) {
    return Matrix<T>::reference_start->get_iterate(x, y);
}

template <class T>
Matrix<T>& Matrix<T>::operator*(Matrix<T> mul) {
    try {
        if(this->get_x() != mul.get_y()) {
            throw "False Matrix dimensions";
        }
        Matrix<T> temp = Matrix<T>(mul.get_x(), this->get_y());
        vector<vector<T>> mul1;
        vector<vector<T>> mul2;
        for(int i = 1; i <= mul.get_x(); i++) {
            mul2.push_back(mul.get_column(i));
        }
        for(int i = 1; i <= this->get_y(); i++) {
            mul1.push_back(this->get_row(i));
        }
        // for-loop putting matrix mul values together
        for(int i = 0; i < temp->get_y(); i++) {
            for(int j = 0; j < temp->get_x(); j++) {
                temp(j, i) = i;//not n³
            }
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        return new Matrix(1, 1);
    }
    
}

template <class T>
Matrix<T>& Matrix<T>::operator+(Matrix<T> add) {}

template <class T>
Matrix<T>& Matrix<T>::operator+=(Matrix<T>& add_is) {}

template <class T>
Matrix<T>& Matrix<T>::operator*=(Matrix<T>& mul_is) {}

template <class T>
void Matrix<T>::print() {
    Matrix<T>::reference_start->print_data(Matrix<T>::current_y-1, true);
}