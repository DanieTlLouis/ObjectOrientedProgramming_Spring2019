#include "card.hpp"

#include <iostream>


std::ostream&
operator<<(std::ostream& os, Suit s)
{
  switch (s) {
  case Clubs: return os << "C";
  case Spades: return os << "S";
  case Hearts: return os << "H";
  case Diamonds: return os << "D";
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
operator<<(std::ostream& os, StandardCard const& c)
{
  return os << c.rank << c.suit;
}

std::ostream&
operator<<(std::ostream& os, JokerCard const& c)
{
  return os << c.color;
}

void
StandardCard::print(std::ostream& os) const
{
  os << *this;
}

void 
JokerCard::print(std::ostream& os) const
{
  os << *this;
}

std::ostream&
operator<<(std::ostream& os, Card const& c)
{
  c.print(os);
  return os;
}

std::ostream& 
operator<<(std::ostream& os, Deck const& d)
{
  int n = 0;

  // Range-based for loop.
  // This is equivalent (more or less) to the
  // loop below.
  for (Card const* c : d) {
    os << *c << ' ';
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
