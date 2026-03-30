#ifndef CARD_H
#define CARD_H

#include"../../helpers/include/generalHelpers.h"
#include<string>


class Card {
  public:
    SuitEnum suit;
    RankEnum rank;
    
    Card(SuitEnum s, RankEnum r);
    std::string getFullCardName();
};


#endif