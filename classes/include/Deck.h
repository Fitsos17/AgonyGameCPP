#ifndef DECK_H
#define DECK_H

#include"Card.h"
#include<vector>

class Deck {
  std::vector<Card> deckVec;
  
  void fillInitialEmptyDeck();

  public:
    Deck();
    void generateDeckFromDP(std::vector<Card> &discardPileDeck);
    bool isDeckEmpty();
    Card drawFromDeck();
    Card drawInitialCardForDP();
};

#endif