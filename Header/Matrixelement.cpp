#include "AllHeaders.h"
using namespace std;

/**
 * enum class for deletion support
 * ----
 * elements are a naming reference to one neighbor in the Matrix
 * ----
 * end indicates the tail item in a Matrix walkthrough
*/
enum class connection {
  up,
  down,
  right,
  left
};

template <typename T> class Matrixelement {

    private:
      map<connection, Matrixelement> connections_elements;

      T* data = NULL;

      int is_row;

    public:
      Matrixelement(int x, int y, Matrixelement<T>& left);
      Matrixelement(int x, int y, Matrixelement<T>& up, bool is_up);
      Matrixelement(int x, int y, Matrixelement<T>& left, int is_row);
      Matrixelement(int x, int y, Matrixelement<T>& up, bool is_up, int is_row);
      T get_iterate(int x, int y);
      bool set_iterate(int x, int y, T& data_new);
      vector<T> get_row(int y);
      vector<T> get_column(int x);
      bool add_dimension_y(int current_size_x);
      bool add_dimension_x(int current_size_y);
      bool delete_dimension_y(int y, int current_size_x, int current_size_y, int rows);
      bool delete_dimension_x(int x, int current_size_x, int current_size_y, int columns);
      void print_data();
};
using namespace std;

template <class T>
Matrixelement<T>::Matrixelement(int x, int y, Matrixelement<T>& left) {
    this->data = new T();
    this->is_row = 0;

    this->connections_elements.insert(connection::left, left);

    if (x-1 > 0) {
        this->connections_elements.insert(connection::right, Matrixelement<T> m(x-1, y, *this));
    }

    if (y-1 > 0) {
        this->connections_elements.insert(connection::down, Matrixelement<T> m(x, y-1, *this, true));
    }
}

template <class T>
Matrixelement<T>::Matrixelement(int x, int y, Matrixelement<T>& up, bool is_up) {
    this->data = new T();
    this->is_row = 0;

    this->connections_elements.insert(connection::up, up);

    if (y-1 > 0) {
        this->connections_elements.insert(connection::down, Matrixelement<T> m(x, y-1, *this, true));
    }
}

template <class T>
Matrixelement<T>::Matrixelement(int x, int y, Matrixelement<T>& left, int is_row) {
    this->data = new T();
    this->is_row = is_row;

    this->connections_elements.insert(connection::left, left);

    if (x-1 > 0) {
        this->connections_elements.insert(connection::right, Matrixelement<T> m(x-1, y, *this, 1));
    }
}

template <class T>
Matrixelement<T>::Matrixelement(int x, int y, Matrixelement<T>& up, bool is_up, int is_row) {
    this->data = new T();
    this->is_row = is_row;

    this->connections_elements.insert(connection::up, up);

    if (y-1 > 0) {
        this->connections_elements.insert(connection::down, Matrixelement<T> m(x, y-1, *this, true, 1));
    }

    if (x-1 > 0) {
        this->connections_elements.insert(connection::right, Matrixelement<T>(x-1, y-1, *this, 1));
    }
}

template <class T>
T Matrixelement<T>::get_iterate(int x, int y) {
    if (this->is_row) {
        if(y > 0) {
            this->connections_elements.find(connections::down).get_iterate(x, y-1);
        } else if (x > 0) {
            this->connections_elements.find(connection::right).get_iterate(x-1, y);
        } else {
            return *this->data;
        }
    } else {
        if(x > 0) {
            this->connections_elements.find(connections::right).get_iterate(x-1, y);
        } else if (y > 0) {
            this->connections_elements.find(connection::down).get_iterate(x, y-1);
        } else {
            return *this->data;
        }
    }
}

template <class T>
bool Matrixelement<T>::set_iterate(int x, int y, T& data_new) {
    if (this->is_row) {
        if(y > 0) {
            this->connections_elements.find(connections::down).set_iterate(x, y-1, data_new);
        } else if (x > 0) {
            this->connections_elements.find(connection::right).set_iterate(x-1, y, data_new);
        } else {
            this->data = data_new;
            return true;
        }
    } else {
        if(x > 0) {
            this->connections_elements.find(connections::right).set_iterate(x-1, y, data_new);
        } else if (y > 0) {
            this->connections_elements.find(connection::down).set_iterate(x, y-1, data_new);
        } else {
            this->data = data_new;
            return true;
        }
    }
}

template <class T>
vector<T> Matrixelement<T>::get_row(int y) {
    if(this->is_row) {
        if(y > 0) {
            return this->connections_elements.find(connection::down).get_row(y-1);
        }

        vector<T> temp({*this->data});

        if(this->connections_elements.contains(connection::right)) {
            vector<T> get_temp = this->connections_elements.find(connection::right).get_row(y);
            temp.insert(temp.end(), get_temp.begin(), get_temp.end());
        }

        return temp;
    }
    vector<T> emptyv;
    return emptyv;
}

template <class T>
vector<T> Matrixelement<T>::get_column(int x) {
    if(!this->is_row) {
        if(x > 0) {
            return this->connections_elements.find(connection::right).get_row(x-1);
        }

        vector<T> temp({*this->data});

        if(this->connections_elements.contains(connection::down)) {
            vector<T> get_temp = this->connections_elements.find(connection::down).get_row(x);
            temp.insert(temp.end(), get_temp.begin(), get_temp.end());
        }

        return temp;
    }
    vector<T> emptyv;
    return emptyv;
}

template <class T>
bool Matrixelement<T>::add_dimension_y(int current_size_x) {
    if(this->is_row) {
        if(this->connections_elements.contains(connection::down)) {
            return this->connections_elements.find(connection::down).add_dimension_y(int current_size_x);
        }
        this->connections_elements.insert(connection::down, Matrixelement<T> m(current_size_x, 1, *this, false, 1));
        return true;
    } else {
        if(this->connections_elements.contains(connection::right)) {
            this->connections_elements.find(connection::right).add_dimension_y(current_size_x);
        }

        if(this->connections_elements.contains(connection::down)) {
            return this->connections_elements.find(connection::down).add_dimension_y(current_size_x);
        }

        this->connections_elements.insert(connection::down, Matrixelement<T> m(1, 1, *this, true));
        return true;
    }
}

template <class T>
bool Matrixelement<T>::add_dimension_x(int current_size_y) {
    if(!this->row) {
        if(this->contains(connection::right)) {
            return this->find(connection::right).add_dimension_x(current_size_y);
        }
        this->connections_elements.insert(connection::right, Matrixelement<T> m(1, current_size_y, *this, true));
        return true;
    } else {
        if(this->connections_elements.contains(connection::down)) {
            this->connection_elements.find(connection::down).add_dimension_x(current_size_y);
        }

        if(this->connections_elements.contains(connection::right)) {
            return this->connections_elements.find(connection::right).add_dimension_y(current_size_x);
        }

        this->connections_elements.insert(connection::down, Matrixelement<T> m(1, 1, *this, true, 1));
        return true;
    }
}

template <class T>
bool Matrixelement<T>::delete_dimension_y(int y, int current_size_x, int current_size_y, int rows) { // y = current_size_y - rows to delete
if(y > 0) {
        Matrixelement<T>::followup_right::delete_dimension_x(y-1);
    } else {
        Matrixelement<T>* up_temp = this->get_right();
        Matrixelement<T>* down_temp = this-get_down()->get_right();

        while (up_temp != NULL) {
            up_temp->set_down(NULL);
            down_temp->set_up(NULL);
            up_temp = up_temp->get_right();
            down_temp = down_temp->get_right();
        }

        up_temp = NULL;
        down_temp = NULL;
        delete up_temp;
        delete down_temp;
        
        if(current_size_x == 1 && rows == 1) {
            delete Matrixelement<T>::followup_down;
            Matrixelement<T>::followup_down = NULL;
        } else if(current_size_x == 1 && rows != 1) {
            Matrixelement<T>::followup_down->del_method(delete_helper::up, delete_helper::right);
        } else if(current_size_x != 1 && rows == 1) {
            Matrixelement<T>::followup_down->del_method(delete_helper::right, delete_helper::right);
        } else {
            Matrixelement<T>::followup_down->del_method(delete_helper::up, delete_helper::up);
        }
    }
    return true;
}

template <class T>
bool Matrixelement<T>::delete_dimension_x(int x, int current_size_x, int current_size_y, int columns) { // x = current_size_x - columns to delete
    if(x > 0) {
        Matrixelement<T>::followup_right::delete_dimension_x(x-1);
    } else {
        if(columns == 1 && current_size_y == 1) {
            delete Matrixelement<T>::followup_down;
            Matrixelement<T>::followup_down = NULL;
        } else if(columns == 1 && current_size_y != 1) {
            Matrixelement<T>::followup_down->del_method(delete_helper::up, delete_helper::right);
        } else if(columns != 1 && current_size_y == 1) {
            Matrixelement<T>::followup_down->del_method(delete_helper::right, delete_helper::right);
        } else {
            Matrixelement<T>::followup_down->del_method(delete_helper::up, delete_helper::up);
        }
        Matrixelement<T>::followup_right::del_helper(delete_helper::down, delete_helper::down);
        delete Matrixelement<T>::followup_right;
        Matrixelement<T>::followup_right = NULL;
        Matrixelement<T>* temp = Matrixelement<T>::followup_down;
        while(temp != NULL) {
            temp->set_right(NULL);
            temp = temp->get_down();
        }
        temp = NULL;
        delete temp;
    }
    return true;
}

template <class T>
void Matrixelement<T>::print_data() {
    if(this->is_row) {
        cout<< *this->data << "   ";

        if(this->connections_elements.contains(connection::right)) {
            this->connections_elements.find(connection::right).print_data();
        } else {
            cout<<endl;
        }

        if(this->connections_elements.contains(connection::down)) {
            this->connections_elements.find(connection::down).print_data();
        }
    }
}