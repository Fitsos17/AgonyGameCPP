#include"../include/Deck.h"
#include"../include/Card.h"
#include<string>
#include<vector>
#include<algorithm>
#include<random>
#include<ctime>

using namespace std;

void Deck::fillInitialEmptyDeck() {
  if (deckVec.size() == 0) {
    for (int i = ACE; i <= KING; i++) {
      for (int j = SPADES; j <= CLUBS; j++) {
        deckVec.emplace_back((SuitEnum)j, (RankEnum)i);
      }
    }

    // shuffle the deck
    shuffle(deckVec.begin(), deckVec.end(), default_random_engine(time(0)));
  }
}

// deck is empty, because players took all the cards. We must take
// the dp and shuffle it to create a new deck.
void Deck::generateDeckFromDP(vector<Card> &discardPileDeck) {
  // creates a deep copy of the discardPileDeck
  deckVec = discardPileDeck;
  shuffle(deckVec.begin(), deckVec.end(), default_random_engine(time(0)));
}

bool Deck::isDeckEmpty() {
  return deckVec.empty();
}

Deck::Deck() {
  // fill the deck with all possible combinations
  fillInitialEmptyDeck();
}

Card Deck::drawFromDeck() {
  Card temp = deckVec.back();
  deckVec.pop_back();
  return temp;
}

Card Deck::drawInitialCardForDP() {
  // The initial card for the DP must not be a special card, so
  // we check the card that we get and we accept it only if it 
  // is not a special card
  int deckVecSize = deckVec.size();
  for (int i = deckVecSize - 1; i >= 0; i--) {
    Card currentCard = deckVec[i];
    RankEnum currentCardRank = currentCard.rank;
    if (currentCardRank != ACE && currentCardRank != SEVEN && currentCardRank != EIGHT && currentCardRank != NINE) {
      deckVec.erase(deckVec.begin() + i);
      return currentCard;
    }
  }
}
