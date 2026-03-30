#ifndef DISCARD_PILE_H
#define DISCARD_PILE_H

#include"../include/Card.h"

#include<vector>
#include<string>

class Deck;

class DiscardPile {
  std::vector<Card> cardsPlayed;
  Card maskedAceCard;
  Card getLastCard();
  bool wasLastCardAnAce();
  
  public: 
    DiscardPile(Card initialCard);
    std::string getLastCardName();
    bool didUpdatePile(Card play);
    void regenerateDeckFromDpIfEmpty(Deck* d);
    void updateMaskedAcePlay(Card mask);
};

#endif