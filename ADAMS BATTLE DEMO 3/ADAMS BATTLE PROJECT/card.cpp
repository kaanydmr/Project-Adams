#include <iostream>
#include "card.h"
#include "game.h"
#include "player.h"
#include "skills.h"
#include <string>
#include <cstdlib>
#include <algorithm>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <vector>


using namespace std;


void Card::setHp(int newHp)
{
    this->hp = newHp ;
}

void Card::setAtk(int newAtk)
{
    this->atk = newAtk ;
}
int Card::getHp()
{
    return this->hp;
}

int Card::getAtk()
{
    return this->atk;
}

Card::Card()
{
    this->name = "None" ;
    this->element = "None" ;
    this->setAtk(0)  ;
    this->setHp(0);
    this->cardType = "None" ;
    this->cardIndex = 99;
    this->skill = nullptr ;
    this->hasAttacked = false;
    this->cdcounter = 1;
    this->isStunned = 1;

}



void Card::displayCard()
{
    cout << "Name: " << this->name;
    cout << "\nType: " << this->cardType;
    cout << "\nAttack Damage: " << this->atk << " dmg";
    cout << "\nHealth:" << this->hp << " hp";
    cout << "\nSkill: " << this->skillString;
    cout << "\nElement: " << this->element;

}

void Card::cardImage()
{
    /*
        -Bromen atk:7  hp:3 Tank earth-
    */
    cout << "-" << name << " atk:" << getAtk() << "  hp:" << getHp() << " " << cardType << " " << element << "-";
}

Card::Card( Card& card) {
    this->name = card.name;
    this->element = card.element;
    this->setAtk(card.getAtk());
    this->setHp(card.getHp());
    this->cardType = card.cardType;
    this->cardIndex = card.cardIndex;
    this->skill = card.skill;
    this->hasAttacked = card.hasAttacked;
    this->cdcounter = 1;
    this->isStunned = card.isStunned;
    this->cooldown = card.cooldown;


}
Assasin::Assasin() : Card()
{

}


Mage::Mage() : Card()
{

}


Tank::Tank() : Card()
{

}


Support::Support() : Card()
{

}


Marksman::Marksman() : Card()
{

}

Marksman::Marksman(Card& card) : Card(card)
{

}

Mage::Mage(Card& card) : Card(card)
{

}

Tank::Tank(Card& card) : Card(card)
{

}

Support::Support(Card& card) : Card(card)
{

}

Assasin::Assasin(Card& card) : Card(card)
{

}





void Tank::attack(vector<Card*> &field1, vector<Card*> &field2) // normal saldiri. Tanklarin özelligi diger kartlarýn saldirisini üzerine cekmektir
{

    // skill aticak cd geldiyse
    if(cdcounter >= cooldown)
    {
        this->skill(field1,field2, this) ;
    }
    else
    {
        this->autoattack(field1) ;
    }

    this->hasAttacked = true ;

}
void Marksman::attack(vector<Card*> &field1, vector<Card*> &field2) // marksman kritik vurma ihtimali vardir
{

    // skill aticak cd geldiyse
    if(this->cdcounter >= this->cooldown)
    {
        this->skill(field1,field2, this) ;
    }
    else
    {
        this->autoattack(field1) ;
    }
    this->hasAttacked = true ;

}
void Assasin::attack(vector<Card*> &field1, vector<Card*> &field2) // assasin cani en az olana vurur
{

    // skill aticak cd geldiyse
    if(this->cdcounter >= this->cooldown)
    {
        this->skill(field1,field2, this) ;
    }
    else
    {
        this->autoattack(field1) ;
    }

    this->hasAttacked = true ;

}

void Mage::attack(vector<Card*> &field1, vector<Card*> &field2) // Mage oyun ilerledikce güclenir her attack yaptiginda atk 5 artar
{

    // skill aticak cd geldiyse
    if(this->cdcounter >= this->cooldown)
    {
        this->skill(field1,field2, this) ;
    }
    else
    {
        this->autoattack(field1) ;
    }
    this->hasAttacked = true ;

    int newAtk ;
    newAtk = this->getAtk() + 5 ;
    this->setAtk(newAtk) ;
}

void Support::attack(vector<Card*> &field1, vector<Card*> &field2) // support hasar atmaz, can basar
{

    // skill aticak cd geldiyse
    if(this->cdcounter >= this->cooldown)
    {
        this->skill(field1,field2, this) ;
    }
    else // skilli yoksa can bas
    {
        int enazindex = 0;
        for(int i=0; i<field2.size(); i++)
        {
            if(field2[i]->getHp() < field2[enazindex]->getHp())
            {
                enazindex = i;
            }
        }
        field2[enazindex]->setHp(field2[enazindex]->getHp() + 10) ;
        cout << this->name << " healed " << field2[enazindex]->name << " 10 hp. " << field2[enazindex]->name << "'s new hp:" << field2[enazindex]->getHp() << endl;


    }


    this->hasAttacked = true ;
}



void Tank::autoattack(vector<Card*> &field) // normal sekilde ilk siradakine vurur
{

    bool tankvarmi = false ;
    int tankindex;

    for( int i=0; i<field.size(); i++)
    {
        if(field[i]->cardType == "Tank")
        {
            tankvarmi = true;
            tankindex = i ;
            break;
        }
    }

    int newHp;



    if(tankvarmi == true)
    {
         newHp = field[tankindex]->getHp() - this->getAtk()*compareElements(field[tankindex]) ;
         field[tankindex]->setHp(newHp) ;
         cout << this->name << " attacked " << field[tankindex]->name << " for " << this->getAtk() << "x" << compareElements(field[tankindex]) << "=" << this->getAtk()*compareElements(field[tankindex]) << " damage. " << field[tankindex]->name << "'s remaining hp: " << field[tankindex]->getHp() << "\n" ;
    }


    else
    {
       newHp = field[0]->getHp() - this->getAtk()*compareElements(field[0]) ;
       field[0]->setHp(newHp) ;
       cout << this->name << " attacked " << field[0]->name << " for " << this->getAtk() << "x" << compareElements(field[0])  << "=" << this->getAtk()*compareElements(field[0]) << " damage. " << field[0]->name << "'s remaining hp: " << field[0]->getHp() << "\n" ;
    }
}

void Assasin::autoattack(vector<Card*> &field) // cani az olana vurur
{
    int enazcanindex = 0;

    for(size_t i=0; i<field.size(); i++)
    {
        if(field[i]->getHp() < field[enazcanindex]->getHp())
        {
            enazcanindex = i ;
        }
    }

    int newHp;

    newHp = field[enazcanindex]->getHp() - this->getAtk()*compareElements(field[enazcanindex]) ;
    field[enazcanindex]->setHp(newHp) ;
    cout << this->name << " attacked " << field[enazcanindex]->name << " for " << this->getAtk() << "x" << compareElements(field[enazcanindex]) << "=" << this->getAtk()*compareElements(field[enazcanindex]) << " damage. " << field[enazcanindex]->name << "'s remaining hp: " << field[enazcanindex]->getHp() << "\n" ;

}

void Marksman::autoattack(vector<Card*> &field) // kritik vurma ihtimali vardir
{
    srand(time(0)) ;
    bool tankvarmi = false ;
    int tankindex;

    for( size_t i=0; i<field.size(); i++)
    {
        if(field[i]->cardType == "Tank")
        {
            tankvarmi = true;
            tankindex = i ;
            break;
        }
    }

    int newHp;
    int critRate = 50;
    int x = rand() % 100 ;
    int extraDmg = 1;
    if(x < critRate)
    {
        extraDmg = 2;
    }
    if(tankvarmi == true)
    {
         newHp = field[tankindex]->getHp() - this->getAtk()*compareElements(field[tankindex])*extraDmg ;
         field[tankindex]->setHp(newHp) ;
         cout << this->name << " attacked " << field[tankindex]->name << " for " << this->getAtk() << "x" << compareElements(field[tankindex]) << "x" << extraDmg << "=" << this->getAtk()*compareElements(field[tankindex])*extraDmg << " damage. " << field[tankindex]->name << "'s remaining hp: " << field[tankindex]->getHp() << "\n" ;
    }

    else
    {
       newHp = field[0]->getHp() - this->getAtk()*compareElements(field[0])*extraDmg ;
       field[0]->setHp(newHp) ;
       cout << this->name << " attacked " << field[0]->name << " for " << this->getAtk() << "x" << compareElements(field[0]) << "x" << extraDmg << "=" << this->getAtk()*compareElements(field[0])*extraDmg << " damage. " << field[0]->name << "'s remaining hp: " << field[0]->getHp() << "\n" ;
    }

}

void Mage::autoattack(vector<Card*> &field)
{
    bool tankvarmi = false ;
    int tankindex;

    for( int i=0; i<field.size(); i++)
    {
        if(field[i]->cardType == "Tank")
        {
            tankvarmi = true;
            tankindex = i ;
            break;
        }
    }

    int newHp;
    if(tankvarmi == true)
    {
         newHp = field[tankindex]->getHp() - this->getAtk()*compareElements(field[tankindex]) ;
         field[tankindex]->setHp(newHp) ;
         cout << this->name << " attacked " << field[tankindex]->name << " for " << this->getAtk() << "x" << compareElements(field[tankindex]) << "=" << this->getAtk()*compareElements(field[tankindex]) << " damage. " << field[tankindex]->name << "'s remaining hp: " << field[tankindex]->getHp() << "\n" ;
    }

    else
    {
       newHp = field[0]->getHp() - this->getAtk()*compareElements(field[0]) ;
       field[0]->setHp(newHp) ;
       cout << this->name << " attacked " << field[0]->name << " for " << this->getAtk() << "x" << compareElements(field[0])  << "=" << this->getAtk()*compareElements(field[0]) << " damage. " << field[0]->name << "'s remaining hp: " << field[0]->getHp() << "\n" ;
    }


}

void Support::autoattack(vector<Card*> &field) // attack yaptiktan sonra can basar
{
    bool tankvarmi = false ;
    int tankindex;

    for( size_t i=0; i<field.size(); i++)
    {
        if(field[i]->cardType == "Tank")
        {
            tankvarmi = true;
            tankindex = i ;
            break;
        }
    }

    int newHp;
    if(tankvarmi == true)
    {
         newHp = field[tankindex]->getHp() - this->getAtk()*compareElements(field[tankindex]) ;
         field[tankindex]->setHp(newHp) ;
         cout << this->name << " attacked " << field[tankindex]->name << " for " << this->getAtk() << "x" << compareElements(field[tankindex]) << "=" << this->getAtk()*compareElements(field[tankindex]) << " damage. " << field[tankindex]->name << "'s remaining hp: " << field[tankindex]->getHp() << "\n" ;
    }

    else
    {
       newHp = field[0]->getHp() - this->getAtk()*compareElements(field[0]) ;
       field[0]->setHp(newHp) ;
       cout << this->name << " attacked " << field[0]->name << " for " << this->getAtk() << "x" << compareElements(field[0])  << "=" << this->getAtk()*compareElements(field[0]) << " damage. " << field[0]->name << "'s remaining hp: " << field[0]->getHp() << "\n" ;
    }


}



bool Card::isDead()
{
    if(getHp() <= 0)
    {
        return true;
    }
    return false;
}

int Card::compareElements(Card* card)
{
    if(this->element == "fire" && card->element == "earth")
    {
        return 2;
    }
    else if(this->element == "water" && card->element == "fire")
    {
        return 2;
    }
    else if(this->element == "earth" && card->element == "water")
    {
        return 2;
    }
    else
    {
        return 1;
    }

}

// Define copy assignment operator for each class
Card& Card::operator=(const Card& rhs) {
    if (this != &rhs) {

        this->hp = rhs.hp;
        this->atk = rhs.atk;
        this->name = rhs.name;
        this->element = rhs.element;
        this->cardType = rhs.cardType;
        this->cardIndex = rhs.cardIndex;
        this->skillString = rhs.skillString;
        this->hasAttacked = rhs.hasAttacked;
        this->cooldown = rhs.cooldown;



        this->skill = rhs.skill;
    }
    return *this;
}

// Define copy assignment operator for Assasin class
Assasin& Assasin::operator=(const Assasin& rhs) {
    if (this != &rhs) {
        // Call base class assignment operator
        Card::operator=(rhs);

    }
    return *this;
}

// Repeat the same pattern for Tank, Mage, Support, and Marksman classes
Tank& Tank::operator=(const Tank& rhs) {
    if (this != &rhs) {
        Card::operator=(rhs);

    }
    return *this;
}

Mage& Mage::operator=(const Mage& rhs) {
    if (this != &rhs) {
        Card::operator=(rhs);

    }
    return *this;
}

Support& Support::operator=(const Support& rhs) {
    if (this != &rhs) {
        Card::operator=(rhs);

    }
    return *this;
}

Marksman& Marksman::operator=(const Marksman& rhs) {
    if (this != &rhs) {
        Card::operator=(rhs);

    }
    return *this;
}
