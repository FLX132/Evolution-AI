#include <iostream>
using namespace std;

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

      T data;

    public:
      Matrixelement(int x, int y, Matrixelement<T> *up, Matrixelement<T> *left);
      ~Matrixelement();
      bool del_method(delete_helper way1, delete_helper way2);
      Matrixelement<T>* get_up();
      Matrixelement<T>* get_right();
      Matrixelement<T>* get_left();
      Matrixelement<T>* get_down();
      bool init_sec();
      bool get_iterate(int x, int y);
      bool add_dimension(int x, int y);
      bool delete_dimension(int x, int y);
      bool print_data();
      long add_value();
      bool safe_to_file();
};