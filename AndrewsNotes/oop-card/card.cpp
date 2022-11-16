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

std::ostream&
operator<<(std::ostream& os, Card const& c)
{
  #if 0
  // If the dynamic type of c is a standard
  // card, print its rank and suit.
  if (c.kind == Card::Standard)
    return os << static_cast<StandardCard const&>(c);

  // If the dynamic type of c is a joker,
  // print its color.
  if (c.kind == Card::Joker)
    return os << static_cast<JokerCard const&>(c);
  #endif

  // Use switch cause it's fast.
  switch (c.kind) {
  case Card::Standard:
    return os << static_cast<StandardCard const&>(c);
  case Card::Joker:
    return os << static_cast<JokerCard const&>(c);
  }

  label:

  goto label;

  // This was the variant/tagged union version.
  // if (c.is_standard())
  //   return os << c.get_standard();
  // if (c.is_joker())
  //   return os << c.get_joker();
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
