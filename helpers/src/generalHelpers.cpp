#include"../include/generalHelpers.h"
#include<string>
#include<functional>
#include<iostream>
#include<limits>

using namespace std;

const CardTypeData CARD_TYPES[13] = { {"Ace", 11}, {"Two", 2}, {"Three", 3}, {"Four", 4}, {"Five", 5}, {"Six", 6}, {"Seven", 7}, {"Eight", 8}, {"Nine", 9}, {"Ten", 10}, {"Jack", 10}, {"Queen", 10}, {"King", 10} };
const string SUITS[] = {"Spades", "Hearts", "Diamonds", "Clubs"};

// function<bool(int)> isInputValid: accept a lambda function (returns: bool, parameter type: int)
int getValidatedInput(string prompt, string errorPrompt, function<bool(int)> isInputValid) {
  cout << prompt;

  int input;
  while (1) {
    // check for missmatched data type in user input
    if(cin >> input) {
      // check if the input is valid regarding to the function "checker" provided.
      // if not, output the errorPrompt provided and clear the buffer
      if (isInputValid(input)) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return input;
      }
      cout << errorPrompt;
    } else {
      cout << "Bad input. Please enter the integer that you are asked: ";
      // reset the failbit, make the compiler to stop panicking
      cin.clear();
    }    

    // ignore all of the bad input entered until the next line (\n)
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
}

