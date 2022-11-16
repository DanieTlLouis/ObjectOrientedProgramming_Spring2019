
#include <iostream>
#include <vector>

// What if I want to control whether we are sorting
// ascending or descending.
//
// We COULD add a flag to determine whether we
// are sorting ascending or descending. This
// is a bit limited. It also complicates the
// logic of the postconditions of this function,
// and by extension, the logical "flow" of any
// code that calls this function.
void
insertion_sort(int* first, int* last, bool asending)
{
  while (first != last) {
    int* iter;
    if (asending)
      iter = std::min_element(first, last);
    else
      iter = std::max_element(first, last);
    std::iter_swap(first, iter);
    ++first;
  }
}

void
print(std::vector<int> const& v)
{
  for (int n : v)
    std::cout << n << ' ';
  std::cout << '\n';
}

int
main()
{
  std::vector<int> v {
    5, 10, 3, 16, -5, 11, 0, 10000, -42
  };

  print(v);
  insertion_sort(v.data(), v.data() + v.size(), true);
  print(v);
  insertion_sort(v.data(), v.data() + v.size(), false);
  print(v);
}



