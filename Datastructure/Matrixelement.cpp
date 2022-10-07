#include <iostream>
#include "../Header/Matrixelement.h"
using namespace std;

template <class T>
Matrixelement<T>::Matrixelement(int x, int y, Matrixelement<T> *up, Matrixelement<T> *left) {
    Matrixelement<T>::before_up = up;
    Matrixelement<T>::before_left = left;
    if(x > 0) {
        if(y > 0) {
            Matrixelement<T>::followup_down = new Matrixelement<T>(x, y-1, this, NULL);
        } else if(y == 0) {
            Matrixelement<T>::followup_down = NULL;
            Matrixelement<T>::followup_rigth = NULL;
        }
        if(Matrixelement<T>::before_up == NULL) {
            Matrixelement<T>::followup_rigth = new Matrixelement<T>(x-1, y, NULL, this); // if before_up is NULL
        }
    } else if(x == 0) { // case for x = 0 but y ax needs instantation
        Matrixelement<T>::followup_rigth = NULL;
        if(y > 0) {
            Matrixelement<T>::followup_down = new Matrixelement<T>(x, y-1, this, NULL);
        } else if(y == 0) {
            Matrixelement<T>::followup_down = NULL;
        }
    }   
}

template <class T>
Matrixelement<T>::~Matrixelement() {
    if(Matrixelement<T>::followup_rigth != NULL) {
        Matrixelement<T>::followup_rigth->~Matrixelement(); // cant be called when last row has been deleted
        // maybe bool variable for before_up == NULL
        if(Matrixelement<T>::followup_down != NULL) {
            Matrixelement<T>::followup_down->~Matrixelement();
        } else { // watch out for 0x000000 memory
            Matrixelement<T>::before_left = NULL;
            Matrixelement<T>::before_up = NULL;

            delete Matrixelement<T>::followup_down;
            delete Matrixelement<T>::before_left;
            delete Matrixelement<T>::before_up;

            Matrixelement<T>::before_left = NULL;
            Matrixelement<T>::before_up = NULL;
            Matrixelement<T>::followup_down = NULL;
            Matrixelement<T>::followup_rigth = NULL;
        }
    } else {
        if(Matrixelement<T>::followup_down != NULL) {
            Matrixelement<T>::followup_down->~Matrixelement();
            Matrixelement<T>::before_left = NULL;
            Matrixelement<T>::before_up = NULL;

            delete Matrixelement<T>::followup_down;
            delete Matrixelement<T>::followup_rigth;
            delete Matrixelement<T>::before_left;
            delete Matrixelement<T>::before_up;

            Matrixelement<T>::before_left = NULL;
            Matrixelement<T>::before_up = NULL;
            Matrixelement<T>::followup_down = NULL;
            Matrixelement<T>::followup_rigth = NULL;
        } else {
            Matrixelement<T>::before_left = NULL;
            Matrixelement<T>::before_up = NULL;

            delete Matrixelement<T>::followup_down;
            delete Matrixelement<T>::followup_rigth;
            delete Matrixelement<T>::before_left;
            delete Matrixelement<T>::before_up;

            Matrixelement<T>::before_left = NULL;
            Matrixelement<T>::before_up = NULL;
            Matrixelement<T>::followup_down = NULL;
            Matrixelement<T>::followup_rigth = NULL;
        }
    }
}

template <class T>
bool Matrixelement<T>::init_sec() {
    if(Matrixelement<T>::followup_rigth != NULL) { 
        bool right_init = Matrixelement<T>::followup_rigth->init_sec();
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

    } else if(Matrixelement<T>::followup_rigth == NULL) { 
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