#ifndef MAIN_HELPER_FUNCTIONS_H
#define MAIN_HELPER_FUNCTIONS_H

#include"../../classes/include/Player.h"
#include"generalHelpers.h"
#include<vector>
#include<string>

class Deck;
class DiscardPile;

std::vector<Player> createPlayers(Deck* d, DiscardPile* dp);
void clearScreen();
void waitForPlayer(std::string playerName);

#endif