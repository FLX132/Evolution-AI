#include <iostream>
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
                left_temp->get_down()->set_right(right_temp);
                right_temp->get_down()->set_left(left_temp);
                left_temp = left_temp->get_down();
                right_temp = right_temp->get_down();
            };
            left_temp = NULL;
            right_temp = NULL;
            delete left_temp;
            delete right_temp;
        }

    } else if(Matrixelement<T>::followup_right == NULL) { 
        Matrixelement<T> *left_temp = Matrixelement<T>::before_left;
        Matrixelement<T> *right_temp = this;
        while(left_temp->get_down() != NULL && right_temp->get_down() != NULL) {
            left_temp->get_down()->set_right(right_temp);
            right_temp->get_down()->set_left(left_temp);
            left_temp = left_temp->get_down();
            right_temp = right_temp->get_down();
        };
        left_temp = NULL;
        right_temp = NULL;
        delete left_temp;
        delete right_temp;
    }
}