#include "AllHeaders.h"
#include "Matrixelement.cpp"
using namespace std;

template <typename T, typename = typename enable_if<is_arithmetic<T>::value, T>::type> class Matrix {
    private:
        Matrixelement<T> columns_matrix;
        Matrixelement<T> rows_matrix;
        int current_x;
        int current_y;

    public:
        Matrix(int x, int y, initializer_list<T> values);
        Matrix(int x, int y);
        ~Matrix();
        void autofill(T values[]);
        bool autofill(initializer_list<T> values);
        void randomfill();
        vector<T> get_row(int y) const;
        vector<T> get_column(int x) const;
        int get_x() const;
        int get_y() const;
        T get_val(int x, int y) const;
        void set_val(int x, int y, T data);
        void print();
        void operator=(const Matrix<T> &new_val);
        Matrix<T>& operator*(const Matrix<T> &mul) const;
        Matrix<T>& operator+(Matrix<T> add);
        void rand_fill();
};

template <typename T, typename M>
Matrix<T, M>::Matrix(int x, int y, initializer_list<T> values) : current_x{x}, current_y{y} {
    bool error_in_construct = false;
    if(x*y < (values.size())) {
        std::cout<<"initializer list is smaller than expected"<<endl<<"  - left out fields will be filled randomly"<<endl;
        error_in_construct = true;
    } else {
        std::cout<<"initializer list is bigger than expected"<<endl<<"   - overflow list elements will be left out"<<endl;
    }
    
    if (!this->error_in_construct) {
        this->columns_matrix = Matrixelement<T>(x, y);
        this->rows_matrix = Matrixelement<T>(x, y, 1);

        this->autofill(values);
    } else {
        this->rand_fill();
        this->autofill(values);
    }
}

template <typename T, typename M>
Matrix<T, M>::Matrix(int x, int y) {
    std::cout<<"no initializer list provided"<<endl<<"  - matrix is filled with random values"<<endl;
    this->columns_matrix = Matrixelement<T>(x, y);
    this->rows_matrix = Matrixelement<T>(x, y, 1);
    this->rand_fill();
}

template <typename T, typename M>
Matrix<T, M>::~Matrix() {
    this->columns_matrix.clear();
    this->rows_matrix.clear();
}

template <typename T, typename M>
void Matrix<T, M>::autofill(T values[]) {
    int count = 0;
    for(int i = 0; i < this->current_y; i++) {
        for(int j = 0; j < this->current_x; j++) {
            this->rows_matrix.set_iterate(j, i, values[count]);
            this->columns_matrix.set_iterate(j, i, values[count]);
            count++;
        }
        count++;
    }
}

template <typename T, typename M>
bool Matrix<T, M>::autofill(initializer_list<T> values) {
    auto count = values.begin();
    for(int i = 0; i < this->current_y; i++) {
        for(int j = 0; j < this->current_x; j++) {
            if(count == values.end()) {
                return true;
            }
            this->rows_matrix.set_iterate(j, i, *count);
            this->columns_matrix.set_iterate(j, i, *count);
            count++;
        }
        count++;
    }
    return true;
}

template <typename T, typename M>
void Matrix<T, M>::void randomfill() {
    for(int i = 0; i < this->current_y; i++) {
        for(int j = 0; j < this->current_x; j++) {
            this->rows_matrix.set_iterate(j, i, rand());
            this->columns_matrix.set_iterate(j, i, rand());
        }
    }
}

template <typename T, typename M>
vector<T> Matrix<T, M>::get_row(int y) const {
    return this->rows_matrix.get_row(y);
}

template <typename T, typename M>
vector<T> Matrix<T, M>::get_column(int x) const {
    return this->rows_matrix.get_column(x);
}

template <typename T, typename M>
int Matrix<T, M>::get_x() const {
    return this->current_x;
}

template <typename T, typename M>
int Matrix<T, M>::get_y() const {
    return this->current_y;
}

template <typename T, typename M>
T Matrix<T, M>::get_val(int x, int y) const {
    return this->rows_matrix.get_iterate(x, y);
}

template <typename T, typename M>
void Matrix<T, M>::set_val(int x, int y, T data) {
    this->rows_matrix.set_iterate(x, y, data);
    this->columns_matrix.set_iterate(x, y, data);
}

template <typename T, typename M>
Matrix<T>& Matrix<T, M>::operator*(const Matrix<T> &mul) const{
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

template <typename T, typename M>
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
}

template <typename T, typename M>
void Matrix<T, M>::print() {
    this->rows_matrix.print_data();
}