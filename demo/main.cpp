#include "SharedPtr.hpp"

int main() {
  int buff_int = 5067;
  auto *ptr_int = new int(buff_int);

  auto shared_ptr_int = SharedPtr<int>(ptr_int);
  auto shared_ptr_null = SharedPtr<int>();

  shared_ptr_null.reset(ptr_int);
  shared_ptr_int.reset();

  return 0;
}