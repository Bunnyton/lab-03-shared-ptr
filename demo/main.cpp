#include "SharedPtr.hpp"

int main() {
  auto* ptri = new int(1);
  SharedPtr ptr(ptri);
  SharedPtr ptr2(ptr);
  std::cout << *ptr2 << " " << ptr2.get() << " " << ptr2.use_count() << std::endl;
  ptr2.reset();
  std::cout << *ptr << " " << ptr.get() << " " << ptr.use_count();
  return 0;
}