#ifndef ENUMS_AND_CONSTANTS_H
#define ENUMS_AND_CONSTANTS_H

#include<string>
#include<functional>

// ENUMS
enum SuitEnum { SPADES, HEARTS, DIAMONDS, CLUBS };
enum RankEnum { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
enum TurnEnum { NEXT_PLAYER, SAME_PLAYER, NEXT_PLAYER_LOOSES_TURN };

// CONSTANTS
struct CardTypeData {
  std::string name;
  int points;
};

extern const CardTypeData CARD_TYPES[13];
extern const std::string SUITS[];

// FUNCTIONS
int getValidatedInput(std::string prompt, std::string errorPrompt, std::function<bool(int)> isInputValid);
 
#endif