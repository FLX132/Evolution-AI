#include "AllHeaders.h"
#include "Matrixelement.cpp"
using namespace std;

template <typename T, typename = typename enable_if<is_arithmetic<T>::value, T>::type> class Matrix {
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

template <typename T, typename M>
Matrix<T, M>::Matrix(int x, int y, vector<T> values) {
    if(x*y != (values.size())) {
        std::cout<<"false formatted init-list";
        Matrix<T, M>::error_in_construct = true;
        delete this;
    } else {
        Matrix<T, M>::reference_start = new Matrixelement<T>(x-1, y-1, NULL, NULL);
        Matrix<T, M>::reference_start->init_sec();
        std::cout<<"Matrix init "<<values.size()<<std::endl;
        int count = 0;
        for(int i = 0; i < y; i++) {
            for(int j = 0; j < x; j++) {
                cout<<i<<" "<<j<<" "<<count<<std::endl;
                Matrix<T, M>::reference_start->set_iterate(j, i, values[count]);
                count++;
            }
        }
        Matrix<T, M>::current_x = x;
        Matrix<T, M>::current_y = y;
    }
}

template <typename T, typename M>
Matrix<T, M>::Matrix(int& x, int& y) {
    Matrix<T, M>::reference_start = new Matrixelement<T>(x-1, y-1, NULL, NULL);
    Matrix<T, M>::reference_start->init_sec();
    Matrix<T, M>::current_x = x;
    Matrix<T, M>::current_y = y;
}

template <typename T, typename M>
Matrix<T, M>::~Matrix() {
    if(!Matrix<T, M>::error_in_construct) {
        Matrix<T, M>::reference_start->del_method(delete_helper::down, delete_helper::down);
        delete Matrix<T, M>::reference_start;
    }
    Matrix<T, M>::reference_start == NULL;
}

template <typename T, typename M>
void Matrix<T, M>::autofill(T values[]) {
    int count = 0;
    for(int i = 0; i < this->get_y(); i++) {
        for(int j = 0; j < this->get_x(); j++) {
            Matrix<T, M>::reference_start->set_iterate(j, i, values[count]);
            count++;
        }
        count++;
    }
}

template <typename T, typename M>
vector<T> Matrix<T, M>::get_row(int y) {
    return Matrix<T, M>::reference_start->get_row(y);
}

template <typename T, typename M>
vector<T> Matrix<T, M>::get_column(int x) {
    return Matrix<T, M>::reference_start->get_column(x);
}

template <typename T, typename M>
int Matrix<T, M>::get_x() {
    return Matrix<T, M>::current_x;
}

template <typename T, typename M>
int Matrix<T, M>::get_y() {
    return Matrix<T, M>::current_y;
}

template <typename T, typename M>
T Matrix<T, M>::get_val(int x, int y) {
    return Matrix<T, M>::reference_start->get_iterate(x, y);
}

template <typename T, typename M>
Matrix<T>& Matrix<T, M>::operator*(Matrix<T> mul) {
    try {
        if(this->get_x() != mul.get_y()) {
            throw "False Matrix dimensions";
        }
        Matrix<T> temp = Matrix<T>(this->get_y(), mul.get_x());
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

template <typename T, typename M>
Matrix<T>& Matrix<T, M>::operator+(Matrix<T> add) {}

template <typename T, typename M>
Matrix<T>& Matrix<T, M>::operator+=(Matrix<T>& add_is) {}

template <typename T, typename M>
Matrix<T>& Matrix<T, M>::operator*=(Matrix<T>& mul_is) {}

template <typename T, typename M>
void Matrix<T, M>::print() {
    Matrix<T, M>::reference_start->print_data(Matrix<T, M>::current_y-1, true);
}