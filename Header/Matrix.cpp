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
        vector<T> get_row(int y) const;
        vector<T> get_column(int x) const;
        int get_x() const;
        int get_y() const;
        T get_val(int x, int y) const;
        void set_val(int &x, int &y, T data);
        void print();
        void operator=(const Matrix<T>& new_val);
        Matrix<T> operator*(const Matrix<T> &mul) const;
        Matrix<T>& operator+(Matrix<T> add);
        void rand_fill();
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
vector<T> Matrix<T, M>::get_row(int y) const {
    return Matrix<T, M>::reference_start->get_row(y);
}

template <typename T, typename M>
vector<T> Matrix<T, M>::get_column(int x) const {
    return Matrix<T, M>::reference_start->get_column(x);
}

template <typename T, typename M>
int Matrix<T, M>::get_x() const {
    return Matrix<T, M>::current_x;
}

template <typename T, typename M>
int Matrix<T, M>::get_y() const {
    return Matrix<T, M>::current_y;
}

template <typename T, typename M>
T Matrix<T, M>::get_val(int x, int y) const {
    return Matrix<T, M>::reference_start->get_iterate(x, y);
}

template <typename T, typename M>
void Matrix<T, M>::set_val(int &x, int &y, T data) {
    Matrix<T, M>::reference_start->set_iterate(x, y, data);
}

template <typename T, typename M>
Matrix<T> Matrix<T, M>::operator*(const Matrix<T> &mul) const{
    try {
        if(this->get_x() != mul.get_y()) {
            throw "False Matrix dimensions";
        }
        int y = this->get_y();
        int x = mul.get_x();
        Matrix<T> temp(y, x);
        vector<vector<T>> mul2;
        for(int i = 0; i < mul.get_x(); i++) {
            mul2.push_back(mul.get_column(i));
        }
        for(int i = 0; i < this->get_y(); i++) {
            vector<T> first_matrix = this->get_row(i);
            for(int j = 0; j < mul2.size(); j++) {
                vector<T> temp_rows(0);
                transform(first_matrix.begin(), first_matrix.end(), mul2[j].begin(), back_inserter(temp_rows), multiplies<T>());
                T new_data = accumulate(temp_rows.begin(), temp_rows.end(), 0);
                temp.set_val(j, i, new_data);
            }
        }
        Matrix<T>& temp2 = temp;
        temp2.print();
        return temp2;
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        int x = 1;
        Matrix<T> err = Matrix(x,x);
        return err;
    }
    
}

template <typename T, typename M>
Matrix<T>& Matrix<T, M>::operator+(Matrix<T> add) {}

/*template <typename T, typename M>
void Matrix<T, M>::operator=(const Matrix<T>& new_val) {
    try {
        cout<<"in = "<<new_val.get_val(1, 1);
        if((this->get_x() != new_val.get_y()) || (this->get_y() != new_val.get_y())) {
            throw "false x or y for =";
        }
        for(int i = 0; i < new_val.get_y(); i++) {
            for(int j = 0; j <new_val.get_x(); j++) {
                this->set_val(j, i, new_val.get_val(j, i));
            }
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }    
}*/

template <typename T, typename M>
void Matrix<T, M>::print() {
    Matrix<T, M>::reference_start->print_data(Matrix<T, M>::current_y-1, true);
}