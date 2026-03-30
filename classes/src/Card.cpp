#include"../include/Card.h"
#include"../../helpers/include/generalHelpers.h"
#include<string>

Card::Card(SuitEnum s, RankEnum r) : suit(s), rank(r) {}

std::string Card::getFullCardName() {
  return CARD_TYPES[rank].name + " of " + SUITS[suit];
}

