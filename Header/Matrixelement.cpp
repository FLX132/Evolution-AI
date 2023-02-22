#include "AllHeaders.h"
using namespace std;

/**
 * enum class for deletion support
 * ----
 * elements are a naming reference to one neighbor in the Matrix
 * ----
 * end indicates the tail item in a Matrix walkthrough
*/
enum class delete_helper {
  up,
  down,
  right,
  end
};

template <typename T> class Matrixelement {

    private:
      Matrixelement<T> *followup_right = NULL;
      Matrixelement<T> *followup_down = NULL;
      Matrixelement<T> *before_left = NULL;
      Matrixelement<T> *before_up = NULL;
      delete_helper way_del;

      T* data = NULL;

    public:
      Matrixelement(int x, int y, Matrixelement<T> *up, Matrixelement<T> *left);
      bool init_sec();
      void delete_next();
      bool del_method(delete_helper way1, delete_helper way2);
      Matrixelement<T>* get_up();
      Matrixelement<T>* get_right();
      Matrixelement<T>* get_left();
      Matrixelement<T>* get_down();
      void set_right(Matrixelement<T>* new_right);
      void set_left(Matrixelement<T>* new_left);
      void set_up(Matrixelement<T>* new_up);
      void set_down(Matrixelement<T>* new_down);
      T& get_iterate(int x, int y);
      bool set_iterate(int x, int y, T& data_new);
      vector<T> get_row(int y);
      vector<T> get_column(int x);
      bool add_dimension_y(int y, int &current_size_x, int &current_size_y);
      bool add_dimension_x(int x, int &current_size_x, int &current_size_y);
      bool delete_dimension_y(int y, int current_size_x, int current_size_y, int rows);
      bool delete_dimension_x(int x, int current_size_x, int current_size_y, int columns);
      void print_data(int y, bool first);
};
using namespace std;

template <class T>
Matrixelement<T>::Matrixelement(int x, int y, Matrixelement<T> *up, Matrixelement<T> *left) {
    std::cout<<"Called Matrixelement constructor"<<std::endl;
    Matrixelement<T>::data = new T();
    Matrixelement<T>::way_del = delete_helper::end;
    Matrixelement<T>::before_up = up;
    Matrixelement<T>::before_left = left;
    if(x > 0) {
        if(y > 0) {
            Matrixelement<T>::followup_down = new Matrixelement<T>(x, y-1, this, NULL);
        } else if(y == 0) {
            Matrixelement<T>::followup_down = NULL;
            Matrixelement<T>::followup_right = NULL;
        }
        if(Matrixelement<T>::before_up == NULL) {
            Matrixelement<T>::followup_right = new Matrixelement<T>(x-1, y, NULL, this); // if before_up is NULL
        }
    } else if(x == 0) { // case for x = 0 but y ax needs instantation
        Matrixelement<T>::followup_right = NULL;
        if(y > 0) {
            Matrixelement<T>::followup_down = new Matrixelement<T>(x, y-1, this, NULL);
        } else if(y == 0) {
            Matrixelement<T>::followup_down = NULL;
        }
    }   
}

template <class T>
void Matrixelement<T>::delete_next() { // next step, destructor travels through Matrix and starts deletion chain
    std::cout<<"Called Matrixelement destructor"<<std::endl;
    switch (Matrixelement<T>::way_del) {
        case delete_helper::up:
            Matrixelement<T>::before_left = NULL;
            Matrixelement<T>::followup_right = NULL;
            Matrixelement<T>::followup_down = NULL;
            delete Matrixelement<T>::before_up;
            Matrixelement<T>::before_up = NULL;
            break;
        case delete_helper::down:
            Matrixelement<T>::before_left = NULL;
            Matrixelement<T>::before_up = NULL;
            Matrixelement<T>::followup_right = NULL;
            delete Matrixelement<T>::followup_down;
            Matrixelement<T>::followup_down = NULL;
            break;
        case delete_helper::right:
            Matrixelement<T>::before_left = NULL;
            Matrixelement<T>::before_up = NULL;
            Matrixelement<T>::followup_down = NULL;
            delete Matrixelement<T>::followup_right;
            Matrixelement<T>::followup_right = NULL;
            break;
        default:
            Matrixelement<T>::before_left = NULL;
            Matrixelement<T>::before_up = NULL;
            Matrixelement<T>::followup_down = NULL;
            Matrixelement<T>::followup_right = NULL;
            break;
    }
    delete Matrixelement<T>::data;
}

template <class T>
bool Matrixelement<T>::del_method(delete_helper way1, delete_helper way2) {
    bool all_ok = true;
    if(!((Matrixelement<T>::followup_right == NULL) && ((Matrixelement<T>::followup_down == NULL) || (Matrixelement<T>::before_up == NULL))) || way2 == delete_helper::right) {
        bool all_ok = true;
        switch(way1) {
            case delete_helper::down:
                switch (way2) {
                    case delete_helper::down:
                        if(Matrixelement<T>::followup_down == NULL) {
                            Matrixelement<T>::way_del = delete_helper::right;
                            all_ok = Matrixelement<T>::followup_right->del_method(way2, delete_helper::right);
                        } else {
                            Matrixelement<T>::way_del = delete_helper::down;
                            all_ok = Matrixelement<T>::followup_down->del_method(way2, delete_helper::down);
                        }
                        break;
                    case delete_helper::right:
                        Matrixelement<T>::way_del = delete_helper::up;
                        all_ok = Matrixelement<T>::before_up->del_method(way2, delete_helper::up);
                        break;
                    default:
                        return false;
                }
                break;
            case delete_helper::up:
                switch (way2) {
                    case delete_helper::up:
                        if(Matrixelement<T>::before_up == NULL) {
                            Matrixelement<T>::way_del = delete_helper::right;
                            all_ok = Matrixelement<T>::followup_right->del_method(way2, delete_helper::right);
                        } else {
                            Matrixelement<T>::way_del = delete_helper::up;
                            all_ok = Matrixelement<T>::before_up->del_method(way2, delete_helper::up);
                        }
                        break;
                    case delete_helper::right:
                        Matrixelement<T>::way_del = delete_helper::down;
                        all_ok = Matrixelement<T>::followup_down->del_method(way2, delete_helper::down);
                        break;
                    default:
                        return false;
                }
                break;
            case delete_helper::right:
                switch (way2) {
                    case delete_helper::down:
                        if(Matrixelement<T>::followup_down == NULL) {
                            Matrixelement<T>::way_del = delete_helper::right;
                            all_ok = Matrixelement<T>::followup_right->del_method(way2, delete_helper::right);
                        } else {
                            Matrixelement<T>::way_del = delete_helper::down;
                            all_ok = Matrixelement<T>::followup_down->del_method(way2, delete_helper::down);
                        }
                        break;
                    case delete_helper::up:
                        if(Matrixelement<T>::before_up == NULL) {
                            Matrixelement<T>::way_del = delete_helper::right;
                            all_ok = Matrixelement<T>::followup_right->del_method(way2, delete_helper::right);
                        } else {
                            Matrixelement<T>::way_del = delete_helper::up;
                            all_ok = Matrixelement<T>::before_up->del_method(way2, delete_helper::up);
                        }
                        break;
                    default:
                        return false;
                }
                break;
        }
    } else if (way1 == delete_helper::right && way2 == delete_helper::right && Matrixelement<T>::followup_right != NULL) {
        Matrixelement<T>::way_del = delete_helper::right;
        Matrixelement<T>::followup_right->del_method(way1, way2);
    }
    this->delete_next();
    return all_ok;
}

template <class T>
bool Matrixelement<T>::init_sec() {
    if(Matrixelement<T>::followup_right != NULL) { 
        bool right_init = Matrixelement<T>::followup_right->init_sec();
        if(Matrixelement<T>::before_left != NULL) {
            Matrixelement<T> *left_temp = Matrixelement<T>::before_left;
            Matrixelement<T> *right_temp = this;
            while(left_temp->get_down() != NULL && right_temp->get_down() != NULL) {
                left_temp->get_down()->set_right(right_temp->get_down());
                right_temp->get_down()->set_left(left_temp->get_down());
                left_temp = left_temp->get_down();
                right_temp = right_temp->get_down();
            };
            left_temp = NULL;
            right_temp = NULL;
            delete left_temp;
            delete right_temp;
        }
        return right_init;
    } else if(Matrixelement<T>::followup_right == NULL) { 
        Matrixelement<T> *left_temp = Matrixelement<T>::before_left;
        Matrixelement<T> *right_temp = this;
        while(left_temp->get_down() != NULL && right_temp->get_down() != NULL) {
            std::cout<<left_temp->get_down()<<" and "<<right_temp->get_down()<<std::endl;
            left_temp->get_down()->set_right(right_temp->get_down());
            right_temp->get_down()->set_left(left_temp->get_down());
            left_temp = left_temp->get_down();
            right_temp = right_temp->get_down();
        };
        left_temp = NULL;
        right_temp = NULL;
        delete left_temp;
        delete right_temp;
        return true;
    }
    return true;
}

template <class T>
Matrixelement<T>* Matrixelement<T>::get_up() {
    return Matrixelement<T>::before_up;
}

template <class T>
Matrixelement<T>* Matrixelement<T>::get_right() {
    return Matrixelement<T>::followup_right;
}

template <class T>
Matrixelement<T>* Matrixelement<T>::get_left() {
    return Matrixelement<T>::before_left;
}

template <class T>
Matrixelement<T>* Matrixelement<T>::get_down() {
    return Matrixelement<T>::followup_down;
}

template <class T>
T& Matrixelement<T>::get_iterate(int x, int y) {
    switch (x) {
        case 0:
            if(y != 0) {
                return Matrixelement<T>::followup_down->get_iterate(x, y-1);
            }    
            return *Matrixelement<T>::data;
        default:
            return Matrixelement<T>::followup_right->get_iterate(x-1, y); 
    }
}

template <class T>
bool Matrixelement<T>::set_iterate(int x, int y, T& data_new) {
    switch (x) {
        case 0:
            if(y != 0) {
                return Matrixelement<T>::followup_down->set_iterate(x, y-1, data_new);
            }
            *Matrixelement<T>::data = data_new;    
            return true;
        default:
            return Matrixelement<T>::followup_right->set_iterate(x-1, y, data_new); 
    }
}

template <class T>
vector<T> Matrixelement<T>::get_row(int y) {
    switch (y) {
        case 0: {
            if(Matrixelement<T>::followup_right == NULL) {
                vector<T> temp_end({*Matrixelement<T>::data});
                std::cout<<temp_end.size()<<" size array "<<std::endl;
                return temp_end;
            }
            vector<T> temp({*Matrixelement<T>::data});
            vector<T> get_temp = Matrixelement<T>::followup_right->get_row(y);
            temp.insert(temp.end(), get_temp.begin(), get_temp.end());
            std::cout<<temp.size()<<" size array "<<get_temp.size()<<std::endl;
            return temp;
        }
        default: {
            return Matrixelement<T>::followup_down->get_row(y-1);
        }
    }
}

template <class T>
vector<T> Matrixelement<T>::get_column(int x) {
    switch (x) {
        case 0: {
            if(Matrixelement<T>::followup_down == NULL) {
                vector<T> temp_end({*Matrixelement<T>::data});
                std::cout<<temp_end.size()<<" size array "<<std::endl;
                return temp_end;
            }
            vector<T> temp({*Matrixelement<T>::data});
            vector<T> get_temp = Matrixelement<T>::followup_down->get_column(x);
            temp.insert(temp.end(), get_temp.begin(), get_temp.end());
            std::cout<<temp.size()<<" size array "<<get_temp.size()<<std::endl;
            return temp; 
        } 
        default: {
            return Matrixelement<T>::followup_right->get_column(x-1);
        }
    }
}

template <class T>
bool Matrixelement<T>::add_dimension_y(int y, int &current_size_x, int &current_size_y) {
    if(Matrixelement<T>::before_left == NULL && Matrixelement<T>::followup_down == NULL && y > 0) {
        Matrixelement<T>::followup_down = new Matrixelement(current_size_x, 0, this, NULL);

        Matrixelement<T> *up_temp = Matrixelement<T>::before_up;
        Matrixelement<T> *down_temp = this;

        while(up_temp->get_right() != NULL && down_temp->get_right() != NULL) {
            up_temp->get_right()->set_down(down_temp->get_right());
            down_temp->get_right()->set_up(up_temp->get_right());
            up_temp = up_temp->get_right();
            down_temp = down_temp->get_right();
        };
        up_temp = NULL;
        down_temp = NULL;
        delete up_temp;
        delete down_temp;
        current_size_y++;
        Matrixelement<T>::followup_down->add_dimension(y-1, current_size_x, current_size_y);
    }
    return true;
}

template <class T>
bool Matrixelement<T>::add_dimension_x(int x, int &current_size_x, int &current_size_y) {
    if(Matrixelement<T>::before_up == NULL && Matrixelement<T>::followup_right == NULL && x > 0) {
        Matrixelement<T>::followup_right = new Matrixelement(0, current_size_y, this, NULL);

        Matrixelement<T> *left_temp = this;
        Matrixelement<T> *right_temp = Matrixelement<T>::followup_right;

        while(left_temp->get_down() != NULL && right_temp->get_down() != NULL) { // change rest of loop
            left_temp->get_down()->set_right(right_temp->get_down());
            right_temp->get_down()->set_left(left_temp->get_down());
            left_temp = left_temp->get_down();
            right_temp = right_temp->get_down();
        };
        left_temp = NULL;
        right_temp = NULL;
        delete left_temp;
        delete right_temp;
        current_size_x++;
        Matrixelement<T>::followup_down->add_dimension(x-1, current_size_x, current_size_y);
    } else {
        Matrixelement<T>::followup_right->add_dimension_x(x, current_size_x, current_size_y);
    }
    return true;
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
void Matrixelement<T>::set_right(Matrixelement<T>* new_right) {
    Matrixelement<T>::followup_right = new_right;
}

template <class T>
void Matrixelement<T>::set_left(Matrixelement<T>* new_left) {
    Matrixelement<T>::before_left = new_left;
}

template <class T>
void Matrixelement<T>::set_up(Matrixelement<T>* new_up) {
    Matrixelement<T>::before_up = new_up;
}

template <class T>
void Matrixelement<T>::set_down(Matrixelement<T>* new_down) {
    Matrixelement<T>::followup_down = new_down;
}

template <class T>
void Matrixelement<T>::print_data(int y, bool first) {
    if (y > -1 && Matrixelement<T>::followup_right != NULL) {
        cout << *Matrixelement<T>::data << "   ";
        Matrixelement<T>::followup_right->print_data(y, false);
        if(first && Matrixelement<T>::followup_down != NULL) {
            Matrixelement<T>::followup_down->print_data(y-1, true);
        }
    } else if(y > -1 && Matrixelement<T>::followup_right == NULL) {
        cout << *Matrixelement<T>::data << endl;
    }
}