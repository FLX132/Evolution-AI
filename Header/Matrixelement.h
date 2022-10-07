#include <iostream>
using namespace std;

template <typename T> class Matrixelement {

    private:
      Matrixelement<T>* followup_rigth = NULL;
      Matrixelement<T>* followup_down = NULL;
      Matrixelement<T>* before_left = NULL;
      Matrixelement<T>* before_up = NULL;

      T data;

    public:
      Matrixelement(int x, int y, Matrixelement<T>* up, Matrixelement<T>* left);
      ~Matrixelement();
      bool init_sec();
      bool get_iterate(int x, int y);
      bool add_dimension(int x, int y);
      bool delete_dimension(int x, int y);
      bool print_data();
      long add_value();
      bool safe_to_file();
};