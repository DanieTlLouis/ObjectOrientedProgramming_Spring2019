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


// Points to a function of any type.
using any_function = void (*)();

// Points to an object of any type.
using any_object = void*;


// Virtual tables. One for each polymorphic class.
extern any_function card_vtable[];
extern any_function standard_card_vtable[];
extern any_function joker_card_vtable[];

// Holds a pointer to a virtual table. 
struct PolymorphicBase
{
  // Returns a pointer to a virtual table. This simply casts the
  // vptr to a pointer to sequence of any functions.
  any_function* vtable() const { return (any_function*)vptr; }

  // Points to the (current) vtable for any derived class object.
  any_object vptr;
};

struct Card : PolymorphicBase {

  Card() {
    vptr = (any_object)card_vtable; // Happens before any initialization.
  }

  ~Card() {
    vptr = (any_object)card_vtable; // Happens before any finalization.
  }

  // virtual void print(std::ostream& os) const = 0;
  void print(std::ostream& os) const {
    auto fn = (void (*)(Card const*, std::ostream&))vtable()[0];
    return fn(this, os);
  }

  // virtual Color get_color() const = 0;
  Color get_color() const {
    auto fn = (Color (*)(Card const*))vtable()[1];
    return fn(this);
  }

  // virtual bool is_standard() const { return false; }
  bool is_standard() const { 
    auto fn = (bool (*)(Card const*))vtable()[2];
    return fn(this);
  }

  static bool is_standard_default(Card const* c) { return false; }

  // virtual bool is_joker() const { return false; }
  bool is_joker() const {
    auto fn = (bool (*)(Card const*))vtable()[3];
    return fn(this);    
  }
  
  static bool is_joker_default(Card const* c) { return false; }
};

struct StandardCard : Card {
  StandardCard(Rank r, Suit s) {
    vptr = (any_object)standard_card_vtable; // Happens before any initialization.
    rank = r;
    suit = s;
  }

  ~StandardCard() {
    vptr = (any_object)standard_card_vtable; // Happens before any finalization.
  }

  // void print(std::ostream& os) const override;
  static void print_override(Card const* c, std::ostream& os);

  // Color get_color() const override;
  static Color get_color_override(Card const* c);

  // bool is_standard() const override;
  static bool is_standard_override(Card const* c) { return true; }

  Rank rank;
  Suit suit;
};

struct JokerCard : Card {
  JokerCard(Color c) {
    vptr = (any_object)joker_card_vtable; // Happens before any initialization.
    color = c;
  }

  ~JokerCard() {
    vptr = (any_object)joker_card_vtable; // Happens before any finalization.
  }

  // void print(std::ostream& os) const override;
  static void print_override(Card const* c, std::ostream& os);

  // Color get_color() const override;
  static Color get_color_override(Card const* c);

  // bool is_joker() const override;
  static bool is_joker_override(Card const* c) { return true; }
  
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
