#include <string>
#include <fstream>
#include <sstream>
#include "day7.h"

int day7::totalWinnings(std::string fp){
    std::fstream data(fp);

    std::string line;

    std::vector<std::string*> allHands;
    std::unordered_map<std::string, int> wagers;
    do{
        getline(data, line);

        std::istringstream linestream(line);
        std::string *hand = new std::string();
        int wager;
        linestream >> *hand;
        linestream >> wager;

        wagers[*hand] = wager;
        allHands.push_back(hand);
    }while(!data.eof());

    std::vector<std::string*> fivekinds;
    std::vector<std::string*> fourkinds;
    std::vector<std::string*> fullhouse;
    std::vector<std::string*> threekinds;
    std::vector<std::string*> twopair;
    std::vector<std::string*> onepair;
    std::vector<std::string*> highcards;

    //fill hand lists
    for(auto hand : allHands){
        if(is5OfKind(*hand)){
            fivekinds.push_back(hand);
        }
        else if(is4OfKind(*hand)){
            fourkinds.push_back(hand);
        }
        else if(isFullHouse(*hand)){
            fullhouse.push_back(hand);
        }
        else if(is3ofKind(*hand)){
            threekinds.push_back(hand);
        }
        else if(is2Pair(*hand)){
            twopair.push_back(hand);
        }
        else if(is1Pair(*hand)){
            onepair.push_back(hand);
        }
        else{
            highcards.push_back(hand);
        }
    }
    //merge all the hand types into a single list
    std::vector<std::vector<std::string*>> ALL;
    ALL.push_back(highcards);
    ALL.push_back(onepair);
    ALL.push_back(twopair);
    ALL.push_back(threekinds);
    ALL.push_back(fullhouse);
    ALL.push_back(fourkinds);
    ALL.push_back(fivekinds);

    //map for letters->numbervals
    std::unordered_map<char, int> letterCards;
    letterCards['T'] = 10;
    letterCards['J'] = 11;
    letterCards['Q'] = 12;
    letterCards['K'] = 13;
    letterCards['A'] = 14;

    //sorts all the cards from each deck
    // after each deck is sorted, wager * rank is calculated and added to the total
    int winnings = 0;
    int ranks = 1;
    for(auto &list : ALL){
        std::sort(list.begin(), list.end(), [&letterCards](std::string * a, std::string *b){
            for (auto handA = a->begin(), handB = b->begin(); handA != a->end(); handA++, handB++) {
                int cardA = std::isdigit(*handA) ? *handA - '0' : letterCards[*handA];
                int cardB = std::isdigit(*handB) ? *handB - '0' : letterCards[*handB];

                if (cardA != cardB) {
                    return cardA < cardB;
                }
            }
            return false;
        });

        for(int i = 0; i < list.size(); i++){
            winnings += wagers[*list[i]] * ranks;
            ranks++;
        }
    }

    return winnings;
}

int day7::totalWinningsWildcards(std::string fp){
    std::fstream data(fp);

    std::string line;

    std::vector<std::string*> allHands;
    std::unordered_map<std::string, int> wagers;
    do{
        getline(data, line);

        std::istringstream linestream(line);
        std::string *hand = new std::string();
        int wager;
        linestream >> *hand;
        linestream >> wager;

        wagers[*hand] = wager;

        allHands.push_back(hand);

    }while(!data.eof());

    std::vector<std::string*> fivekinds;
    std::vector<std::string*> fourkinds;
    std::vector<std::string*> fullhouse;
    std::vector<std::string*> threekinds;
    std::vector<std::string*> twopair;
    std::vector<std::string*> onepair;
    std::vector<std::string*> highcards;
//fill hand lists
    for(auto hand : allHands){
        if(is5OfKind(*hand)){
            fivekinds.push_back(hand);
        }
        else if(is4OfKind(*hand)){
            //if there are any wildcards in a 4 of kind it always becomes a 5 of kind. consider: KKKKJ or JJJJK
            if(getWildcards(*hand) != 0){
                fivekinds.push_back(hand);
            }
            else{
                fourkinds.push_back(hand);
            }
        }
        else if(isFullHouse(*hand)){
            //if there are wildcards present these will always become a 5 kind: KKJJJ or JJKKK
            if(getWildcards(*hand) != 0){
                fivekinds.push_back(hand);
            }
            else {
                fullhouse.push_back(hand);
            }
        }
        else if(is3ofKind(*hand)){
            //if there are any wildcards present these will always become 4 kind: 7KKKJ or JJJK7
            if(getWildcards(*hand) != 0){
                fourkinds.push_back(hand);
            }
            else {
                threekinds.push_back(hand);
            }
        }
        else if(is2Pair(*hand)){
            //this ones a bit more interesting... if there are 2 wildcards that means one of the pairs
            //is a wild card pair, making the hand 4 of a kind: JJKK5
            if(getWildcards(*hand) == 2){
                fourkinds.push_back(hand);
            }
            //however if there is 1 wildcard, a full house is presented: 55KKJ
            else if(getWildcards(*hand) == 1){
                fullhouse.push_back(hand);
            }
            else {
                twopair.push_back(hand);
            }
        }
        else if(is1Pair(*hand)){
            //if there are any wildcards these turn into 3 kind: JJK57 or JKK57
            if(getWildcards(*hand) != 0){
                threekinds.push_back(hand);
            }
            else{
                onepair.push_back(hand);
            }
        }
        else{
            //if a high card hand has a wildcard, since all the cards are distinct,
            //the hand will always turn to a one pair: J5678
           if(getWildcards(*hand) != 0){
               onepair.push_back(hand);
           }
           else{
               highcards.push_back(hand);
           }
        }
    }
    //merge all the hand types into a single list
    std::vector<std::vector<std::string*>> ALL;
    ALL.push_back(highcards);
    ALL.push_back(onepair);
    ALL.push_back(twopair);
    ALL.push_back(threekinds);
    ALL.push_back(fullhouse);
    ALL.push_back(fourkinds);
    ALL.push_back(fivekinds);

    //map for letters->numbervals
    std::unordered_map<char, int> letterCards;
    letterCards['T'] = 10;
    letterCards['J'] = 1;
    letterCards['Q'] = 12;
    letterCards['K'] = 13;
    letterCards['A'] = 14;

    //sorts all the cards from each deck
    // after each deck is sorted, wager * rank is calculated and added to the total
    int winnings = 0;
    int ranks = 1;
    for(auto &list : ALL){
        std::sort(list.begin(), list.end(), [&letterCards](std::string * a, std::string *b){
            for (auto handA = a->begin(), handB = b->begin(); handA != a->end(); handA++, handB++) {
                int cardA = std::isdigit(*handA) ? *handA - '0' : letterCards[*handA];
                int cardB = std::isdigit(*handB) ? *handB - '0' : letterCards[*handB];

                if (cardA != cardB) {
                    return cardA < cardB;
                }
            }
            return false;
        });

        for(int i = 0; i < list.size(); i++){
            winnings += wagers[*list[i]] * ranks;
            ranks++;
        }
    }
    return winnings;
}

int day7::getWildcards(std::string cards) {
    return std::count(cards.begin(), cards.end(), 'J');
}

//if theres more than 1 distinct card, no 5 of kind
bool day7::is5OfKind(std::string cards){
    return std::count(cards.begin(), cards.end(), cards.at(0)) == 5;
}
//if theres more than 2 distinct cards no 4 of a kind
bool day7::is4OfKind(std::string cards){
    if(cards.at(0) == cards.at(1)){
        return std::count(cards.begin(), cards.end(), cards.at(0)) == 4;
    }
    else if(cards.at(0) == cards.at(2)){
        return std::count(cards.begin(), cards.end(), cards.at(0)) == 4;
    }
    else if(cards.at(1) == cards.at(2)){
        return std::count(cards.begin(), cards.end(), cards.at(1)) == 4;
    }
    return false;
}
//if there is more than 2 distinct cards, you dont have a full house
bool day7::isFullHouse(std::string cards){
    char card1 = ' ', card2 = ' ';
    for(auto i : cards){
        if(card1 == ' '){
            card1 = i;
        }
        else if(card1 != i && card2 == ' '){
            card2 = i;
        }
        else if(i != card1 && i != card2){
            return false;
        }
    }
    return true;
}
//check each card and see if one of them occurs 3 times
bool day7::is3ofKind(std::string cards){
   for(auto i : cards){
      if(std::count(cards.begin(), cards.end(), i) == 3){
          return true;
      }
   }
   return false;
}
//if you have more than 3 unique cards, then you dont have 2 pairs
bool day7::is2Pair(std::string cards){
    char card1 = ' ', card2 = ' ', card3 = ' ';
    for(auto i : cards){
        if(card1 == ' '){
            card1 = i;
        }
        else if(card1 != i && card2 == ' '){
            card2 = i;
        }
        else if((card1 != i && card2 != i) && card3 == ' '){
            card3 = i;
        }
        else if(card1 != i && card2 != i && card3 != i){
            return false;
        }
    }
    return true;
}
//check each card and see if any occur twice
bool day7::is1Pair(std::string cards){
    for(auto i : cards){
        if(std::count(cards.begin(), cards.end(), i) == 2){
            return true;
        }
    }
    return false;
}