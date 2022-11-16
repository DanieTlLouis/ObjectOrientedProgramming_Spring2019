#pragma once

#include <cassert>
#include <deque>
#include <iostream>
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

class Card;

// The virtual table (or vtable) for the
// Card class.
struct CardVirtualTable {
  void (*print_fn)(Card const*, std::ostream&) = nullptr;
  Color (*color_fn)(Card const*) = nullptr;
};

extern CardVirtualTable card_vtbl;

struct Card {
  Card() {
    vptr = &card_vtbl;

    print(std::cout); // WHAT HAPPENS???
  }

  ~Card() {
    vptr = &card_vtbl;
  }

  // Invokes a virtual function indirectly.
  void print(std::ostream& os) const {
    vptr->print_fn(this, os);
  }

  Color get_color() const {
    return vptr->color_fn(this);
  }

  // The virtual table pointer.
  CardVirtualTable* vptr;
};

struct StandardCardVirtualTable : CardVirtualTable {
  StandardCardVirtualTable();
};

extern StandardCardVirtualTable standard_card_vtbl;

struct StandardCard : Card {
  StandardCard(Rank r, Suit s)
    : rank(r), suit(s)
  {
    vptr = &standard_card_vtbl;
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

struct JokerCardVirtualTable : CardVirtualTable {
  JokerCardVirtualTable();
};

extern JokerCardVirtualTable joker_card_vtbl;

struct JokerCard : Card {
  JokerCard(Color c)
    : color(c)
  {
    vptr = &joker_card_vtbl;
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
