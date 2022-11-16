#pragma once

#include <cassert>
#include <deque>
#include <iosfwd>


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
  enum Kind {
    Standard,
    Joker,
  };

  Card(Kind k) : kind(k) { }
  
  Kind kind;
};

// StandardCard *derives from Card.
// Card is the *base class* (superclass/supertype)
// StandardCard is the *derived class* (subclass/subtype).
struct StandardCard : Card {
  StandardCard(Rank r, Suit s)
    : Card(Standard), rank(r), suit(s)
  { }

  Rank rank;
  Suit suit;
};

struct JokerCard : Card {
  JokerCard(Color c)
    : Card(Joker), color(c)
  { }
  
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
