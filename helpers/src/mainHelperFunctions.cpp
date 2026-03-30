#include"../../classes/include/Deck.h"
#include"../../classes/include/DiscardPile.h"
#include"../../classes/include/Player.h"
#include"../include/generalHelpers.h"
#include"../include/mainHelperFunctions.h"
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<random>
#include<ctime>

using namespace std;

vector<Player> createPlayers(Deck* d, DiscardPile* dp) {
  // 1. Get number of players
  cout << "Welcome to Agony!" << endl;
  int numberOfPlayers = getValidatedInput("Select how many players will play (can only be 2 or 4): ", "Invalid number of players. Please select 2 OR 4 players: ", [](int input) { return input == 2 || input == 4; });

  // 2. Get player names
  vector<string> playerNames;
  for (int i = 0; i < numberOfPlayers; i++) {
    string name;
    cout << "Player number " << i + 1 << ", enter your name: ";
    while(1) {
      getline(cin, name);
      if (find(playerNames.begin(), playerNames.end(), name) != playerNames.end()) {
        cout << "This name has already been picked. Please pick another one: ";
        continue;
      } else if (name.empty()) {
        cout << "Your name must not be empty. Please pick a name: ";
        continue;
      }
      playerNames.push_back(name);
      break;
    }
  }

  // 3. shuffle names to create vector with random turns
  cout << "\nShuffling players, getting turns... " << endl;
  shuffle(playerNames.begin(), playerNames.end(), default_random_engine(time(0)));

  cout << "The order that you are going to play is the following: " << endl;
  for (int i = 0; i < numberOfPlayers; i++) {
    cout << i << ". " << playerNames[i] << endl;
  }

  cout << endl;

  // 4. create players vector
  // do not use array, because we must initialize a constructor first.
  // init a vector so we can fill it with player objects with no crashes.
  vector<Player> playersVec;
  
  for (string name : playerNames) {
    // emplace_back is the best method for here. We use it when we 
    // want to create the object directly inside the vector's memory
    // without creating a copy of the object and push_back
    playersVec.emplace_back(d, dp, name);
  }

  return playersVec;
}

void clearScreen() {
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

void waitForPlayer(string playerName) {
  cout << "PASS THE COMPUTER TO " << playerName << "!" << endl;
  cout << playerName << ", when you are ready press enter to reveal your cards" << endl;
  getchar();
  clearScreen();
}
