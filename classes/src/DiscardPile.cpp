#include"../include/Card.h"
#include"../include/DiscardPile.h"
#include"../include/Deck.h"
#include<iostream>

using namespace std;

Card DiscardPile::getLastCard() {
  Card lastCard = cardsPlayed[cardsPlayed.size() - 1];
  return lastCard;
}

bool DiscardPile::wasLastCardAnAce() {
  return getLastCard().rank == ACE;
}
  
DiscardPile::DiscardPile(Card initialCard) : maskedAceCard(SPADES, TWO) {
  cardsPlayed.push_back(initialCard);
}

string DiscardPile::getLastCardName() {
  // if last card was an ace, inform player about the card that was picked (in the place of ace) 
  return getLastCard().getFullCardName() + (wasLastCardAnAce() ? " and the player changed it into " + maskedAceCard.getFullCardName() : "");
}

bool DiscardPile::didUpdatePile(Card play) {
  // Allow the card to be played if it matches suit/rank with last card
  // or if it is an ace.
  if (wasLastCardAnAce()) {
    if (play.rank == ACE || (play.rank != maskedAceCard.rank && play.suit != maskedAceCard.suit)) {
      cout << "Can not play the card " + play.getFullCardName() << ". You must NOT pick an ace AND the card that you pick must match the card that the last player chose, which is: " + maskedAceCard.getFullCardName() << endl;
      return false;
    }

    cardsPlayed.push_back(play);
    return true;
  }

  Card lastCard = getLastCard();
  if (play.rank != ACE && play.rank != lastCard.rank && play.suit != lastCard.suit) {
    cout << "Can not play card. You must pick a card that matches suit OR rank with the last card played (" << getLastCardName() << "). Otherwise you must play an ace or loose your turn and draw a card." << endl;
    return false;
  }
  cardsPlayed.push_back(play);
  return true;
}

void DiscardPile::regenerateDeckFromDpIfEmpty(Deck* d) {
  if (!d->isDeckEmpty()) return;
  // leave the last card down on the pile
  Card lastCard = getLastCard();
  cardsPlayed.pop_back();
  d->generateDeckFromDP(cardsPlayed);
  cardsPlayed.clear();
  cardsPlayed.push_back(lastCard);
}

void DiscardPile::updateMaskedAcePlay(Card mask) {
  maskedAceCard = mask;
}
