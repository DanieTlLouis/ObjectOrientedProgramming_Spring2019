
#pragma once

// Suits...
char clubs = 'C';
char spades = 'S';
char hearts = 'H';
char diamonds = 'D';

// Constructs a type that defines
// an enumerated set of values.
enum class Suit {
  Clubs,
  Spades,
  Hearts,
  Diamonds,
};

// Ranks
enum Rank {
  Ace,
};

// char ace = 'A';
// ... 


// char suit = clubs;
// suit = 'Z';
Suit suit = Hearts;
// suit = 'z'; // error
// suit = Zombie; // error


struct Card
{
  Suit suit;
  Rank rank;
};
