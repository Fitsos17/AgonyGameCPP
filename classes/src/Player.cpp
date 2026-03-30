#include"../../helpers/include/generalHelpers.h"
#include"../include/Card.h"
#include"../include/Player.h"
#include"../include/Deck.h"
#include"../include/DiscardPile.h"
#include<string>
#include<iostream>
#include<limits>

using namespace std;

const int DRAW_PER_SEVEN = 2;
  
void Player::drawCard() {
  hand.push_back(connectedDeck->drawFromDeck());
}

// handle plays of special cards
// ACE
void Player::handleAcePlay () {
  cout << "\nYou played an ACE. Choose the card you want to place down to the pile: " << endl;
  // choose rank
  cout << "- Available ranks: " << endl;
  for (int i = TWO; i <= KING; i++) {
    cout << i << ". " <<  CARD_TYPES[i].name << endl;
  }
  int pickedRankInt = getValidatedInput("Choose card rank: ", "Rank does not exist. Please enter a valid rank: ", [](int input) { return input >= TWO && input <= KING; });
  RankEnum acePickedRank = (RankEnum)pickedRankInt;
  
  // choose suit
  cout << "- Available suits: " << endl;
  for (int i = SPADES; i <= CLUBS; i++) {
    cout << i + 1 << ". " << SUITS[i] << endl;
  }
  int pickedSuitInt = getValidatedInput("Choose card suit: ", "Suit does not exist. Please enter a valid suit: ", [](int input) { return (input - 1) >= SPADES && (input - 1) <= CLUBS; });
  SuitEnum acePickedSuit = (SuitEnum)pickedSuitInt;

  Card acePickedCard(acePickedSuit, acePickedRank);
  connectedDiscardPile->updateMaskedAcePlay(acePickedCard);
}

// SEVEN
// returns true if user dropped a seven to counter, else returns false.
bool Player::handleSevenPlay (int& stackedSevens) {

  // A stack of sevens is already there. We need
  // to check if current player has another seven
  // to counter, or then he must take 2 cards. 
  int handSize = hand.size();
  cout << "\nOh no! Other players dropped a seven. Checking cards to see if you have another seven to counter..." << endl;
  for (int i = 0; i < handSize; i++) {
    if (hand[i].rank == SEVEN) {
      // seven found. Play it for counter and erase it from the hand
      cout << "You are lucky, I found a seven in your hands. I am going to play it for you, so you won't draw the 2 cards needed!" << endl;
      stackedSevens++;
      hand.erase(hand.begin() + i);
      return true;
    }
  }

  int numberOfCardsToDraw = stackedSevens * DRAW_PER_SEVEN;
  cout << "Unlucky, you did not have a seven to counter. Because " << stackedSevens << " seven(s) has been dropped, you will draw the following " << numberOfCardsToDraw << " cards" << endl;

  for (int i = 0; i < numberOfCardsToDraw; i++) {
    drawCard();
    cout << hand[hand.size() - 1].getFullCardName() << endl;
  }
  stackedSevens = 0;
  cout << endl;
  return false;
}

// return action enum to handle player turns
TurnEnum Player::changeTurn(RankEnum playedRank) {
  switch(playedRank) {
    case EIGHT:
      return SAME_PLAYER;
    case NINE:
      return NEXT_PLAYER_LOOSES_TURN;
    default:
      return NEXT_PLAYER;
  }
}


// bind the reference cd instantly, because the alias object can not be left
// hanging. When we create the alias, we need to bind it at the same time
// to the connectedDeck (playerName(n) binds n to playerName, good for performance)
Player::Player(Deck* cd, DiscardPile* dp, string n): connectedDeck(cd), connectedDiscardPile(dp), playerName(n) { 
  playerPoints = 0;
  // get initial hand
  for (int i = 0; i < 7; i++) {
    drawCard();
  }
}

string Player::getPlayerName() {
  return playerName;
}

int Player::getPlayerPoints() {
  return playerPoints;
}

bool Player::didPlayerPlayAllCards() {
  return hand.empty();
}

TurnEnum Player::playCard(int& stackedSevens) {
  if (stackedSevens) {
    if (handleSevenPlay(stackedSevens)) {
      // function returned true, so player did have a 
      // seven to counter. We continue to the next player.
      playerPoints += 7;
      return NEXT_PLAYER;
    };
  }
  int handSize = hand.size();
  cout << "\nPlayer " << playerName << ", you have currently " << handSize << " cards and " << playerPoints << " points.\nYour available cards are: \n";
  for (int i = 0; i < handSize; i++) {
    cout << i << ". " << hand[i].getFullCardName() << endl;
  }
  cout << handSize << ". Pass" << endl;
  cout << "Last card played was: " << connectedDiscardPile->getLastCardName() << endl;
  
  TurnEnum nextPlayerAction;
  while (1) {
    int playersChoice = getValidatedInput("Select the number of the card you want to play: ", "Invalid number picked. Please pick again.", [handSize](int input) { return input >= 0 && input <= handSize; });

    if (playersChoice == handSize) {
      drawCard();
      cout << "You passed. You drew the card: " << hand[hand.size() - 1].getFullCardName() << endl;
      cout << "Press enter to continue to the next player..." << endl;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      nextPlayerAction = NEXT_PLAYER;
    } else if (playersChoice >= 0 && playersChoice < handSize) {
      Card pickedCard = hand[playersChoice];
      // we must first check if the pile updated successfully or 
      // the user picked different rank/suit (and not an ace).   
      if (!connectedDiscardPile->didUpdatePile(pickedCard)) continue;

      if (pickedCard.rank == ACE) {
        handleAcePlay();
      } else if (pickedCard.rank == SEVEN) {
        stackedSevens++;
      }
      nextPlayerAction = changeTurn(pickedCard.rank);
      
      playerPoints += CARD_TYPES[pickedCard.rank].points;

      // delete card from hand of player.
      hand.erase(hand.begin() + playersChoice);
    }
    break;
  }
  return nextPlayerAction;
}
