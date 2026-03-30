#ifndef PLAYER_H
#define PLAYER_H

#include"Card.h"
#include"../../helpers/include/generalHelpers.h"

#include<string>
#include<vector>

class Deck;
class DiscardPile;

class Player {
  std::string playerName;
  int playerPoints;
  Deck* connectedDeck;
  DiscardPile* connectedDiscardPile;
  std::vector<Card> hand;
  
  void drawCard();
  void handleAcePlay ();
  bool handleSevenPlay (int& stackedSevens);
  TurnEnum changeTurn(RankEnum playedRank);

  public: 
    Player(Deck* cd, DiscardPile* dp, std::string n);
    std::string getPlayerName();
    int getPlayerPoints();
    bool didPlayerPlayAllCards();
    TurnEnum playCard(int& stackedSevens);
};

#endif