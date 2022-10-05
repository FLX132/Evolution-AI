#include <iostream>
#include "../Header/Matrixelement.h"
using namespace std;

template <class T>
Matrixelement<T>::Matrixelement(int x, int y, Matrixelement<T>* up, Matrixelement<T>* left) {
    Matrixelement<T>::before_up = up;
    Matrixelement<T>::before_left = left;
    if(x > 0) {
        if(y > 0) {
            Matrixelement<T>::followup_down* = new Matrixelement<T>(x, y-1, this, NULL);
        } else if(y == 0) {
            Matrixelement<T>::followup_down* = NULL;
            Matrixelement<T>::followup_rigth* = NULL;
        }
        Matrixelement<T>::followup_rigth* = new Matrixelement<T>(x-1, y, NULL, this);
    } else if(x == 0) { // case for x = 0 but y ax needs instantation
        Matrixelement<T>::followup_rigth* = NULL;
    }   
}

template <class T>
Matrixelement<T>::~Matrixelement() {
    // how to delete everything
}

template <class T>
bool Matrixelement<T>::init_sec() {
    if(Matrixelement<T>::followup_rigth* != NULL && Matrixelement<T>::before_up == NULL) { 
        bool right_init = Matrixelement<T>::followup_rigth->init_sec();
        Matrixelement<T>* left_temp = Matrixelement<T>::before_left;
        Matrixelement<T>* right_temp = this;
        while(left_temp->followup_down != NULL && right_temp->followup_down != NULL) {
            left_temp->followup_rigth = right_temp;
            right_temp->before_left = left_temp;
            left_temp = left_temp->followup_down;
            right_temp = right_temp->followup_down;
        };
        left_temp = NULL;
        right_temp = NULL;
        delete left_temp;
        delete right_temp;

    } else if(Matrixelement<T>::followup_rigth* == NULL && Matrixelement<T>::followup_down == NULL) { 
        Matrixelement<T>* left_temp = Matrixelement<T>::before_left;
        Matrixelement<T>* right_temp = this;
        while(left_temp->followup_down != NULL && right_temp->followup_down != NULL) {
            left_temp->followup_rigth = right_temp;
            right_temp->before_left = left_temp;
            left_temp = left_temp->followup_down;
            right_temp = right_temp->followup_down;
        };
        left_temp = NULL;
        right_temp = NULL;
        delete left_temp;
        delete right_temp;
    }
}