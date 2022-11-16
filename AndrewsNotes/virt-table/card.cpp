#include "card.hpp"

#include <iostream>

// Virtual tables

any_function card_vtable[] = {
  nullptr,
  nullptr,
  (any_function)Card::is_standard_default,
  (any_function)Card::is_joker_default,
};

any_function standard_card_vtable[] = {
  (any_function)&StandardCard::print_override,
  (any_function)&StandardCard::get_color_override,
  (any_function)&StandardCard::is_standard_override,
  (any_function)&Card::is_joker_default, // NOTE: inherited definition
};

any_function joker_card_vtable[] = {
  (any_function)&JokerCard::print_override,
  (any_function)&JokerCard::get_color_override,
  (any_function)&Card::is_standard_default, // NOTE: inherited definition
  (any_function)&JokerCard::is_joker_override,
};

void
StandardCard::print_override(Card const* c, std::ostream& os)
{
  StandardCard const* this_ = static_cast<StandardCard const*>(c);
  os << *this_;
}

Color
StandardCard::get_color_override(Card const* c) 
{
  StandardCard const* this_ = static_cast<StandardCard const*>(c);
  return static_cast<Color>(this_->suit >= Diamonds);
}

void 
JokerCard::print_override(Card const* c, std::ostream& os)
{
  JokerCard const* this_ = static_cast<JokerCard const*>(c);
  os << *this_;
}

Color
JokerCard::get_color_override(Card const* c) 
{
  JokerCard const* this_ = static_cast<JokerCard const*>(c);
  return this_->color;
}

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
