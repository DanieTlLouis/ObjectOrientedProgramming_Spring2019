
#include "card.hpp"

#include <iostream>
#include <random>

int main(int argc, char* argv[]) 
{
  Deck d {
    {Ace, Spades},
    {Two, Spades},
    {Three, Spades},
    {Four, Spades},
    {Five, Spades},
    {Six, Spades},
    {Seven, Spades},
    {Eight, Spades},
    {Nine, Spades},
    {Ten, Spades},
    {Jack, Spades},
    {Queen, Spades},
    {King, Spades},

    {Ace, Clubs},
    {Two, Clubs},
    {Three, Clubs},
    {Four, Clubs},
    {Five, Clubs},
    {Six, Clubs},
    {Seven, Clubs},
    {Eight, Clubs},
    {Nine, Clubs},
    {Ten, Clubs},
    {Jack, Clubs},
    {Queen, Clubs},
    {King, Clubs},

    {Ace, Diamonds},
    {Two, Diamonds},
    {Three, Diamonds},
    {Four, Diamonds},
    {Five, Diamonds},
    {Six, Diamonds},
    {Seven, Diamonds},
    {Eight, Diamonds},
    {Nine, Diamonds},
    {Ten, Diamonds},
    {Jack, Diamonds},
    {Queen, Diamonds},
    {King, Diamonds},

    {Ace, Hearts},
    {Two, Hearts},
    {Three, Hearts},
    {Four, Hearts},
    {Five, Hearts},
    {Six, Hearts},
    {Seven, Hearts},
    {Eight, Hearts},
    {Nine, Hearts},
    {Ten, Hearts},
    {Jack, Hearts},
    {Queen, Hearts},
    {King, Hearts},

    // ...
  };

  std::cout << d << '\n';

  std::random_device rng;
  std::minstd_rand prng(rng());

  std::shuffle(d.begin(), d.end(), prng);

  std::cout << d << '\n';

  std::sort(d.begin(), d.end());

  std::cout << d << '\n';

  return 0;
}
