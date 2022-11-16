#pragma once

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

class Card {
public:
  Card(Rank r, Suit s)
    : rank(r), suit(s)
  { }

  // Returns the rank. The "const" guarantees
  // that the function does not modify the data
  // members of the class (or call any other
  // member function that does).
  //
  // This is an accessor function, or getter, or
  // observer.
  Rank get_rank() const { return rank; }

  // Same as above.
  Suit get_suit() const { return suit; }

  // Think before you create mutators (setters).
  // void set_rank(Rank r) { rank = r; }
  // void set_suit(Suit s) { suit = s; }

private:
  Rank rank;
  Suit suit;
};

bool operator==(Card a, Card b);
bool operator!=(Card a, Card b);

bool operator<(Card a, Card b);
bool operator>(Card a, Card b);
bool operator<=(Card a, Card b);
bool operator>=(Card a, Card b);


struct Deck : std::deque<Card> {
  using std::deque<Card>::deque;
};

std::ostream& operator<<(std::ostream& os, Suit s);
std::ostream& operator<<(std::ostream& os, Rank r);
std::ostream& operator<<(std::ostream& os, Card c);
std::ostream& operator<<(std::ostream& os, Deck const& d);
