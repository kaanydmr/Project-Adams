#ifndef  PLAYER_H
#define  PLAYER_H
#include "card.h"
#include <string>
#include <vector>

class Player
{
public:

    Player(std::string name) ;

    std::string name;
    Card** deck;

    virtual void playCard(vector<Card*> &hand, vector<Card*> &field) ;
    virtual void selectDeck(vector<vector<Card*>> preDecks , Card** cards, int cardsSize) ;
    ~Player() ;

};


class Computer : public Player
{
public:

    void playCard(vector<Card*> &hand, vector<Card*> &field) ;
    void selectDeck(vector<vector<Card*>> preDecks , Card** cards, int cardsSize) ;
    Computer() ;
    ~Computer();
};

class Boss : public Player
{
public:

    void playCard(vector<Card*> &hand, vector<Card*> &field) ;
    Boss() ;
    ~Boss();
};

#endif //PLAYER_H
