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

// Denotes an abstract set values whose
// concrete values are represented by
// derived classes.
struct Card {
  // This is a virtual function. It declares
  // that print is dispatched based on the
  // dynamic type of this object (I mean the 
  // pointer). Called dynamic dispatch.
  //
  // We will eventually call one of the
  // overrides defined below.

  // virtual void print(std::ostream& os) const {
  //   // assert(false);
  //   throw std::logic_error("you done messed up");
  // }

  // This is a pure virtual function. Also 
  // called an abstract method.
  virtual void print(std::ostream& os) const = 0;

  // Returns the color of a card.
  // virtual Color get_color() const {
  //   throw std::logic_error("you done messed up");
  // }

  virtual Color get_color() const = 0;
};

// StandardCard *derives from Card.
// Card is the *base class* (superclass/supertype)
// StandardCard is the *derived class* (subclass/subtype).
struct StandardCard : Card {
  StandardCard(Rank r, Suit s)
    : rank(r), suit(s)
  { }

  // This is an override (not an overwrite) of
  // the virtual function in Card.
  //
  // Defined in the .cpp file.
  void print(std::ostream& os) const override;

  // Override.
  Color get_color() const override {
    return static_cast<Color>(suit > Diamonds);
  }

  Rank rank;
  Suit suit;
};

struct JokerCard : Card {
  JokerCard(Color c)
    : color(c)
  { }
  
  // An override for jokers.
  void print(std::ostream& os) const override;

  // Override
  Color get_color() const override {
    return color;
  }
  
  Color color;
};


// DOES NOT WORK.
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
