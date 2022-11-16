#include "card.hpp"

#include <iostream>

#if 0
bool
operator==(Card a, Card b)
{
  return a.get_rank() == b.get_rank() &&
         a.get_suit() == b.get_suit();
}

bool
operator!=(Card a, Card b)
{
  return !(a == b);
}


bool
operator<(Card a, Card b)
{
  // Product order (does not give a
  // total order).
  // return a.get_rank() < b.get_rank() &&
  //        a.get_suit() < b.get_suit();

  // Lexicographical order
  if (a.get_suit() < b.get_suit())
    return true;
  if (b.get_suit() < a.get_suit())
    return false;
  return a.get_rank() < b.get_rank();
}

bool
operator>(Card a, Card b)
{
  return false;
}

bool
operator<=(Card a, Card b)
{
  return false;
}

bool
operator>=(Card a, Card b)
{
  return false;
}
#endif


std::ostream&
operator<<(std::ostream& os, Suit s)
{
  switch (s) {
  case Spades: return os << "S";
  case Clubs: return os << "C";
  case Diamonds: return os << "D";
  case Hearts: return os << "H";
  }
}

std::ostream&
operator<<(std::ostream& os, Rank r)
{
  switch (r) {
  case Ace: return os << "A";
  case Two: return os << "2";
  case Three: return os << "3";
  case Four: return os << "4";
  case Five: return os << "5";
  case Six: return os << "6";
  case Seven: return os << "7";
  case Eight: return os << "8";
  case Nine: return os << "9";
  case Ten: return os << "T";
  case Jack: return os << "J";
  case Queen: return os << "Q";
  case King: return os << "K";
  }
}

std::ostream&
operator<<(std::ostream& os, Color c)
{
  return os << (c == Black ? "B" : "R");
}

std::ostream&
operator<<(std::ostream& os, StandardCard c)
{
  return os << c.get_suit() << c.get_rank();
}

std::ostream&
operator<<(std::ostream& os, JokerCard c)
{
  return os << c.get_color();
}

std::ostream&
operator<<(std::ostream& os, PlayingCard c)
{
  if (c.is_standard())
    return os << c.get_as_standard();
  else
    return os << c.get_as_joker();
}

std::ostream& 
operator<<(std::ostream& os, Deck const& d)
{
  int n = 0;
  for (PlayingCard c : d) {
    os << c << ' ';
    if (n == 12) {
      os << '\n';
      n = 0;
    }
    else {
      ++n;
    }
  }
  return os;
}
