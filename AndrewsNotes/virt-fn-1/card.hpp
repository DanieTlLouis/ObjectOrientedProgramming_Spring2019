#pragma once

#include <cassert>
#include <deque>
#include <iosfwd>
#include <stdexcept>


enum Suit {
  Spades,
  Clubs,
  Diamonds,
  Hearts,
};

enum Rank { 
  Ace,
  Two,
  Three,
  Four,
  Five,
  Six,
  Seven,
  Eight,
  Nine,
  Ten,
  Jack,
  Queen,
  King,
};

enum Color {
  Black,
  Red,
};

struct Card {
  Card() {
    print_fn = nullptr;
    color_fn = nullptr;
  }

  // Invokes a virtual function indirectly.
  void print(std::ostream& os) const {
    print_fn(this, os);
  }

  Color get_color() const {
    return color_fn(this);
  }

  // Stores the "current" override of a virtual
  // function.
  void (*print_fn)(Card const*, std::ostream&);
  Color (*color_fn)(Card const*);
};

struct StandardCard : Card {
  StandardCard(Rank r, Suit s)
    : rank(r), suit(s)
  {
    // Actually OVERRIDE the inherited behaviors
    // of these functions.
    print_fn = do_print;
    color_fn = do_get_color;
  }

  // Print override.
  static void do_print(Card const* self, std::ostream& os);

  static Color do_get_color(Card const* self) {
    StandardCard const* ptr = static_cast<StandardCard const*>(self);
    return static_cast<Color>(ptr->suit > Diamonds);
  }

  Rank rank;
  Suit suit;
};

struct JokerCard : Card {
  JokerCard(Color c)
    : color(c)
  { 
    print_fn = do_print;
    color_fn = do_get_color;
  }
  
  static void do_print(Card const* self, std::ostream& os);

  static Color do_get_color(Card const* self) {
    JokerCard const* ptr = static_cast<JokerCard const*>(self);
    return ptr->color;
  }

  Color color;
};


struct Deck : std::deque<Card*> {
  using std::deque<Card*>::deque;
};

std::ostream& operator<<(std::ostream& os, Suit s);
std::ostream& operator<<(std::ostream& os, Rank r);
std::ostream& operator<<(std::ostream& os, Color c);
std::ostream& operator<<(std::ostream& os, StandardCard const& c);
std::ostream& operator<<(std::ostream& os, JokerCard const& c);
std::ostream& operator<<(std::ostream& os, Card const& c);
std::ostream& operator<<(std::ostream& os, Deck const& d);
