
#include <cassert>
#include <cstdlib>

struct Suit
{
  // Static means that the variable (or function)
  // is not bound to (or part of) the object.
  static int Hearts = 0;
  static int Diamonds = 1;
  static int Clubs = 2;
  static int Spades = 3;

  Suit(int s)
    : suit(s) // Directly initialize suit from s.
  {
    assert(s < 0 || s > 3);

    // DONT DO THIS (almost ever).
    // if (s < 0 || s > 3)
    //   std::cout << "error\n";

    // DONT DO THIS (for the most part).
    // if (s < 0 || s > 3)
    //   s = Hearts;

    // if (s < 0 || s > 3)
    //   throw std::logic_error("invalid suit");

    // if (s < 0 || s > 3)
    //   std::abort();
  }

  int suit; // Stores one of the values above.
};

Suit s1 = Suit::Hearts;

Suit s2 = -1; // NOTE: Runtime error

