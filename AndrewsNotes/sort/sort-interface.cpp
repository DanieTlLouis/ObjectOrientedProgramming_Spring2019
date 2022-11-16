
#include <iostream>
#include <iomanip>
#include <functional>
#include <random>
#include <string>
#include <vector>

struct book
{
  std::string title;
  std::string author;
  std::string year;
};

bool
operator<(book const& a, book const& b)
{
  if (a.author < b.author)
    return true;
  if (b.author < a.author)
    return false;
  if (a.year < b.year)
    return true;
  if (b.year < a.year)
    return false;
  return a.title < b.title;
}

bool
operator>(book const& a, book const& b)
{
  return b < a;
}

std::ostream&
operator<<(std::ostream& os, book const& b)
{
  os << std::setw(12) << std::left << b.author << "| ";
  os << std::setw(6) << b.year << "| ";
  os << b.title << '\n';
  return os;
}

// Defines comparison (a type) to be any function
// that takes two books and returns bool.
struct comparison
{
  virtual bool less(book const& a, book const& b) const = 0;
};

// This function is an instance of the "template method"
// pattern: you have a function parameterized by one or
// more operations, provided by abstract base class
// arguments.
book*
my_min_element(book* first, book* last, comparison& op)
{
  assert(first != last);
  book* min = first++;
  for (; first != last; ++first) {
    if (op.less(*first, *min))
      min = first;
  }
  return min;
}


// Instead of using a "flag" to control behavior,
// we can parameterize the entire behavior of the
// function by another function.
//
// A language has "first class functions" if you
// can pass a function as an argument to another
// function.
//
// insertion_sort is called a "high order function",
// meaning that it's behavior depends on other 
// functions.
//
// The new postcondition for this functions is:
//
//    is_sorted(first, last, comp) &&
//    is permutation of original.
//
// New preconditions are harder to define.
//
//    axiom is_range(first, last)
//
// What is required of comp? comp must be a strict
// weak order. That is, for any books a and b, one
// of the following must be true:
//
//    comp(a, b) // i.e., a < b
//    comp(b, a) // i.e., b < a
//    !comp(a, b) && !comp(b, a)
//
// Let eq = !comp(a, b) && !comp(b, a), then
// eq must be an equivalence relation.
//
// A strict weak order is a generalized form of
// a strict total order (e.g., operator <).
void
insertion_sort(book* first, book* last, comparison& comp)
{
  while (first != last) {
    book* iter = my_min_element(first, last, comp);
    std::iter_swap(first, iter);
    ++first;
  }
}

void
print(std::vector<book> const& v)
{
  for (book const& b : v)
    std::cout << b;
}

bool
less(book const& a, book const& b)
{
  return a < b;
}

bool
greater(book const& a, book const& b)
{
  return a > b;
}

bool
title_asc(book const& a, book const& b)
{
  return a.title < b.title;
}

bool
author_asc(book const& a, book const& b)
{
  return a.author < b.author;
}

bool
author_year_asc(book const& a, book const& b)
{
  if (a.author < b.author)
    return true;
  if (a.author > b.author)
    return false;
  return a.year < b.year;
}

// A derived class implementing a single kind
// of comparison for books.
struct author_year_comp : comparison
{
  bool less(book const& a, book const& b) const override
  {
    return author_year_asc(a, b);
  }
};


int
main()
{
  std::vector<book> v {
    {"The Lord or the Rings", "Tolkien", "1956"},
    {"The Great Gatsby", "Fitzgerald", "1925"},
    {"Fellowship of the Ring", "Tolkien", "1954"},
    {"Dune", "Herbert", "1965"},
    {"Programming", "Stroustrup", "2008"},
    {"The Two Towers", "Tolkien", "1955"},
    {"1984", "Orwell", "1948"},
  };

  std::random_device rng;
  std::minstd_rand prng(rng());
  std::shuffle(v.begin(), v.end(), prng);

  std::cout << "BEFORE\n";
  print(v);

  // insertion_sort(v.data(), v.data() + v.size(), less);
  // std::cout << "LESS\n";
  // print(v);
  // insertion_sort(v.data(), v.data() + v.size(), greater);
  // std::cout << "GREATER\n";
  // print(v);

  // insertion_sort(v.data(), v.data() + v.size(), title_asc);
  // std::cout << "TITLE ASC\n";
  // print(v);

  // insertion_sort(v.data(), v.data() + v.size(), author_asc);
  // std::cout << "AUTHOR ASC\n";
  // print(v);

  author_year_comp ay_asc;
  insertion_sort(v.data(), v.data() + v.size(), ay_asc);
  std::cout << "AUTHOR YEAR ASC\n";
  print(v);
}



