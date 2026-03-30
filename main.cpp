#include"helpers/include/generalHelpers.h"
#include"helpers/include/mainHelperFunctions.h"
#include"classes/include/Player.h"
#include"classes/include/Card.h"
#include"classes/include/Deck.h"
#include"classes/include/DiscardPile.h"
#include<iostream>
#include<string>
#include<vector>
#include<time.h>
#include <algorithm> // for shuffle function
#include <random> // for default_random_engine

using namespace std;

int main() {
  Deck d;
  // set one card inside the discardPile as start
  Card initialCardForDp = d.drawInitialCardForDP();
  DiscardPile dp(initialCardForDp);

  // create players
  vector<Player> players = createPlayers(&d, &dp);
  int playersVecSize = players.size();
  
  // set points limit in case nobody finishes their hand.
  int pointsLimit = getValidatedInput("Set the point limit. The point limit must be set to declare winner in case nobody finishes their hand (so that the game will finish faster): ", "Invalid point limit. Please make the point limit > 0 points: ", [](int input) { return input > 0; });


  TurnEnum playerAction = NEXT_PLAYER;
  int playersTurn = 0;
  // how many cards must the next person draw after the seven.
  int stackedSevens = 0;

  enum WonByEnum { NO_CARDS_LEFT, POINTS } winnerBy;

  while (1) {
    // the deck is empty, so we take the cards from dp and shuffle
    // them to create a new deck
    dp.regenerateDeckFromDpIfEmpty(&d);
    
    Player& currentPlayer = players[playersTurn];
    
    clearScreen();

    if (playerAction == NEXT_PLAYER_LOOSES_TURN) {
      // if current player (playersTurn) is 0, then that means
      // that the last player of the vector players lost his turn
      int playerThatLostTurn = playersTurn == 0 ? playersVecSize - 1 : playersTurn - 1;
      cout << "\n" << players[playerThatLostTurn].getPlayerName() << ", you lost your turn because the previous player played a 9." << endl;
    } else if (playerAction == SAME_PLAYER) {
      cout << "\nYou played an 8. Replay." << endl;
    }
  
    
    waitForPlayer(currentPlayer.getPlayerName());
  
    playerAction = currentPlayer.playCard(stackedSevens);
    
    // winner decision
    // player won by playing all of cards
    if (currentPlayer.didPlayerPlayAllCards()) {
      winnerBy = NO_CARDS_LEFT;
      break;
    } else if (currentPlayer.getPlayerPoints() >= pointsLimit) {
      winnerBy = POINTS;
      break;
    }

    // update player turn
    switch (playerAction) {
      // player dropped eight, replay.
      case SAME_PLAYER:
        break;
      // player dropped 9, next player looses turn.
      case NEXT_PLAYER_LOOSES_TURN:
        playersTurn += 2;
        break;
      // next player
      default:
        playersTurn++;
        break;
    }

    if (playersTurn >= playersVecSize) playersTurn -= playersVecSize;
  }

  // end of game 
  clearScreen();
  cout << "\nPlayer " << players[playersTurn].getPlayerName() << ", you won by " << (winnerBy == NO_CARDS_LEFT ? "playing all of your cards!" : "having the most points!") << endl;

  // display the leaderboard by points
  sort(players.begin(), players.end(), [](Player a, Player b) {
    return a.getPlayerPoints() > b.getPlayerPoints();
  });
  cout << "\nLeaderboard (by points): " << endl;
  for (int i = 0; i < playersVecSize; i++) {
    cout << i + 1 << ". " << players[i].getPlayerName() << ": " << players[i].getPlayerPoints() << endl;
  }

  cout << "\nGame ended, press enter to exit..." << endl;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}