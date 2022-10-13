#include <iostream>
#include <vector>
#include "../Header/Matrixelement.h"
using namespace std;

template <class T>
Matrixelement<T>::Matrixelement(int x, int y, Matrixelement<T> *up, Matrixelement<T> *left) {
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
Matrixelement<T>::~Matrixelement() {
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
}

template <class T>
bool del_method(delete_helper way1, delete_helper way2) {
    bool all_ok = true;
    if(!((Matrixelement<T>::followup_right == NULL) && ((Matrixelement<T>::followup_down == NULL) || (Matrixelement<T>::before_up == NULL))) || way2 == delete_helper::right) {
        switch(way1) {
            case delete_helper::down:
                switch (way2) {
                    case delete_helper::down:
                        if(Matrixelement<T>::followup_down == NULL) {
                            Matrixelement<T>::way_del = delete_helper::right;
                            all_ok = Matrixelement<T>::folloup_right->del_method(way2, delete_helper::right);
                        } else {
                            Matrixelement<T>::way_del = delete_helper::down;
                            all_ok = Matrixelement<T>::folloup_down->del_method(way2, delete_helper::down);
                        }
                        break;
                    case delete_helper::right:
                        Matrixelement<T>::way_del = delete_helper::up;
                        all_ok = Matrixelement<T>::before_up->del_method(way2, delete_helper::up);
                        break;
                    default:
                        return false;
                }
            case delete_helper::up:
                switch (way2) {
                    case delete_helper::up:
                        if(Matrixelement<T>::before_up == NULL) {
                            Matrixelement<T>::way_del = delete_helper::right;
                            all_ok = Matrixelement<T>::folloup_right->del_method(way2, delete_helper::right);
                        } else {
                            Matrixelement<T>::way_del = delete_helper::up;
                            all_ok = Matrixelement<T>::before_up->del_method(way2, delete_helper::up);
                        }
                        break;
                    case delete_helper::right:
                        Matrixelement<T>::way_del = delete_helper::down;
                        all_ok = Matrixelement<T>::folloup_down->del_method(way2, delete_helper::down);
                        break;
                    default:
                        return false;
                }
            case delete_helper::right:
                switch (way2) {
                    case delete_helper::down:
                        if(Matrixelement<T>::followup_down == NULL) {
                            Matrixelement<T>::way_del = delete_helper::right;
                            all_ok = Matrixelement<T>::folloup_right->del_method(way2, delete_helper::right);
                        } else {
                            Matrixelement<T>::way_del = delete_helper::down;
                            all_ok = Matrixelement<T>::folloup_down->del_method(way2, delete_helper::down);
                        }
                        break;
                    case delete_helper::up:
                        if(Matrixelement<T>::before_up == NULL) {
                            Matrixelement<T>::way_del = delete_helper::right;
                            all_ok = Matrixelement<T>::folloup_right->del_method(way2, delete_helper::right);
                        } else {
                            Matrixelement<T>::way_del = delete_helper::up;
                            all_ok = Matrixelement<T>::before_up->del_method(way2, delete_helper::up);
                        }
                        break;
                    default:
                        return false;
                }
        }
    }
    this->~Matrixelement();
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
T Matrixelement<T>::get_iterate(int x, int y) {
    switch (x) {
        case 0:
            return Matrixelement<T>::followup_down->get_iterate(x, y-1);     
        default:
            if(y != 0) {
                return Matrixelement<T>::followup_right->get_iterate(x-1, y);
            }
            return Matrixelement<T>::data;
    }
}

template <class T>
bool Matrixelement<T>::set_iterate(int x, int y, T& data) {
    switch (x) {
        case 0:
            if(y != 0) {
                return Matrixelement<T>::followup_right->get_iterate(x-1, y);
            }
            return Matrixelement<T>::data = data;    
        default:
            return Matrixelement<T>::followup_down->get_iterate(x, y-1); 
    }
}

template <class T>
vector<T> Matrixelement<T>::get_row(int y) {
    switch (y) {
        case 0:
            vector<T> temp(Matrixelement<T> data);
            vector<T> get_temp = Matrixelement<T>::followup_right->get_row(y);
            return temp.insert(temp.end(), get_temp.begin(), get_temp.end());
        default:
            return Matrixelement<T>::followup_down->get_row(y-1);
    }
}

template <class T>
vector<T> Matrixelement<T>::get_column(int x) {
    switch (x) {
        case 0:
            vector<T> temp(Matrixelement<T> data);
            vector<T> get_temp = Matrixelement<T>::followup_down->get_column(x);
            return temp.insert(temp.end(), get_temp.begin(), get_temp.end());   
        default:
            return Matrixelement<T>::followup_right->get_column(x-1);
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
            down_temp->get_right()->set_upleft(up_temp->get_right());
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
}

template <class T>
bool Matrixelement<T>::add_dimension_x(int x, int &current_size_x, int &current_size_y) {
    if(Matrixelement<T>::before_up == NULL && Matrixelement<T>::followup_right == NULL && x > 0) {
        Matrixelement<T>::followup_right = new Matrixelement(0, current_size_y, this, NULL);

        Matrixelement<T> *left_temp = this;
        Matrixelement<T> *right_temp = Matrixelement<T>::followup_right;

        while(left_temp->get_down() != NULL && right_temp->get_down() != NULL) { // change rest of loop
            up_temp->get_right()->set_down(down_temp->get_right());
            down_temp->get_right()->set_upleft(up_temp->get_right());
            up_temp = up_temp->get_right();
            down_temp = down_temp->get_right();
        };
        up_temp = NULL;
        down_temp = NULL;
        delete up_temp;
        delete down_temp;
        current_size_y++;
        Matrixelement<T>::followup_down->add_dimension(x-1, current_size_x, current_size_y);
    } else {
        Matrixelement<T>::followup_right->add_dimension_x(x, current_size_x, current_size_y);
    }
}

template <class T>
bool Matrixelement<T>::delete_dimension_y(int y) {}

template <class T>
bool Matrixelement<T>::delete_dimension_x(int x) {}

template <class T>
void Matrixelement<T>::print_data(int y, bool first) {
    if (y > -1 && Matrixelement<T>::followup_right != NULL) {
        cout << Matrixelement<T>::data << "   ";
        Matrixelement<T>::followup_right->print_data(y, false);
        if(first && Matrixelement<T>::followup_down != NULL) {
            Matrixelement<T>::followup_down->print_data(y-1, true)
        }
    } else if(y > -1 && Matrixelement<T>::followup_right == NULL) {
        cout << Matrixelement<T>::data << endl;
    }
}