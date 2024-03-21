#ifndef CARDS_H
#define CARDS_H

#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <algorithm>

using namespace std;

class Card  // abstract Class
{
    protected:
        int hp  ;
        int atk  ;

    public:
        string name;
        string element;
        string cardType ;
        int cardIndex ;
        string skillString;
        bool hasAttacked ;
        int isStunned;
        int cooldown;
        int cdcounter;

        void setHp(int newHp) ;
        void setAtk(int newAtk) ;
        int getHp() ;
        int getAtk() ;
        void displayCard() ;
        void cardImage() ;
        virtual void attack(vector<Card*> &field1, vector<Card*> &field2) =0;
        virtual void autoattack(vector<Card*> &field)=0  ;
        void (*skill)(vector<Card*> &field1,vector<Card*> &field2, Card* card) ;
        bool isDead() ;

        int compareElements(Card* card) ;

        Card& operator=(const Card& rhs) ;
        Card( Card& card) ;
        Card() ;
        // destructor
        virtual ~Card()  {}
};

class Assasin : public Card
{
    public:

        Assasin() ;
        Assasin(Card& card) ;
        void autoattack(vector<Card*> &field) override;
        void attack(vector<Card*> &field1, vector<Card*> &field2) override;
        Assasin& operator=(const Assasin& rhs) ;
        virtual ~Assasin() {}
};


class Tank : public Card
{
    public:

        Tank() ;
        Tank(Card& card) ;
        void autoattack(vector<Card*> &field) override;
        void attack(vector<Card*> &field1, vector<Card*> &field2) override;
        Tank& operator=(const Tank& rhs) ;
        virtual ~Tank() {}


};


class Mage : public Card
{
    public:

        Mage() ;
        Mage(Card& card) ;
        void autoattack(vector<Card*> &field) override;
        void attack(vector<Card*> &field1, vector<Card*> &field2) override;
        Mage& operator=(const Mage& rhs) ;
        virtual ~Mage() {}

};


class Support : public Card
{
    public:

        Support() ;
        Support(Card& card) ;
        void autoattack(vector<Card*> &field) override;

        void attack(vector<Card*> &field1, vector<Card*> &field2) override;
        Support& operator=(const Support& rhs) ;
        virtual ~Support() {}


};


class Marksman : public Card
{
    public:

        Marksman() ;
        Marksman(Card& card) ;
        void autoattack(vector<Card*> &field) override ;
        void attack(vector<Card*> &field1, vector<Card*> &field2) override;
        Marksman& operator=(const Marksman& rhs) ;
        virtual ~Marksman() {}

};



#endif // CARDS_H
