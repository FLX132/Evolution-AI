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
      ~Matrixelement();
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
      bool set_iterate(int x, int y, T& data);
      vector<T&> get_row(int y);
      vector<T&> get_column(int x);
      bool add_dimension_y(int y, int &current_size_x, int &current_size_y);
      bool add_dimension_x(int x, int &current_size_x, int &current_size_y);
      bool delete_dimension_y(int y, int current_size_x, int current_size_y, int rows);
      bool delete_dimension_x(int x, int current_size_x, int current_size_y, int columns);
      void print_data(int y, bool first);
};