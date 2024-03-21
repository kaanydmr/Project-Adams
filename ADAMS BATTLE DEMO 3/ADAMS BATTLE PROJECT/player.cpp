#include "card.h"
#include "player.h"
#include "game.h"
#include "skills.h"
#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>

Player::Player(std::string name = "None") : name(name),deck(nullptr)
{

    deck = new Card*[7] ;

    for (int i = 0; i < 7; i++)
    {
        deck[i] = nullptr;
    }

}

Player::~Player()
{
    delete[] deck;
}

void Player::selectDeck(vector<vector<Card*>> preDecks , Card** cards, int cardsSize )  // user selecting deck
{


    cout << "\n\n" << name << " Select one." ;
    cout << "\n\n1.Use existing deck" ;
    cout << "\n2.Create your deck\n" ;

    string s;
    int select;
    bool validInput = false;
    while(validInput == false)
    {
        try
            {
                cin >> s;
                if(s == "x")
                    break;

                select = stoi(s);
                if(select<1)
                {
                    throw invalid_argument("\nNegative input not allowed!\n") ;
                }
                if(select>2)
                {
                    throw out_of_range("\nInput out of range!\n") ;
                }
                validInput = true;
            }
            catch(const exception& e)
            {
                cout << "\nInvalid input please try again.\n" ;
            }
        if(s =="x")
            break;
    }
    if(s == "x")
        return;



    if(select == 1)
    {

        cout << "\n1. Balanced deck" ;
        cout << "\n2. Early game Assasins deck" ;
        cout << "\n3. Late game scaling Mages deck" ;
        cout << "\n4. Protect the Marksmans deck" ;
        cout << "\n\n\nSelect your deck\n" ;
    string s;
    int select;
    bool validInput = false;
    while(validInput == false)
    {
        try
            {
                cin >> s;
                select = stoi(s);

                if(select<1)
                {
                    throw invalid_argument("\ninvalid input!\n") ;
                }
                if(select>4)
                {
                    throw out_of_range("\nInput out of range!\n") ;
                }
                validInput = true;
            }
            catch(const exception& e)
            {
                cout << "\nInvalid input please try again.\n" ;
            }

    }

        for(int i = 0; i<7; i++)
        {
            deck[i] = preDecks[select-1][i] ;
        }

    }

    else if(select == 2)
    {
        infoCard(cards,cardsSize) ;

        vector <int> selected;
        for(int i = 0; i<7; i++) // 7 card secimi
        {

            string s;
            int select;
            bool validInput = false;
            while(validInput == false)
            {

                try
                {
                    cout << "\nSelect " << i+1 << ". card (you cant select same card twice!): " ;
                    cin >> s;
                    select = stoi(s);
                    bool flag = false;
                    for(int i=0; i<selected.size(); i++)
                    {
                        if(select == selected[i])
                        {
                            flag = true;
                        }
                    }

                    if (flag == true)
                    {
                        throw invalid_argument("\nYou cant select same card twice!\n") ;
                    }
                    if(select<0)
                    {
                        throw invalid_argument("\nNegative input not allowed!\n") ;
                    }
                    if(select>=cardsSize)
                    {
                        throw out_of_range("\nInput out of range!\n") ;
                    }
                    validInput = true;
                }
                catch(const exception& e)
                {
                    cout << "\nInvalid input please try again.\n" ;
                }

            }
            deck[i] = cards[select] ;
            selected.push_back(select) ;
        }
    }

    system("cls") ;
    cout << name << " Deck:\n\n";
    for(int i = 0; i<7; i++)
    {
         cout << i+1 << ". " << setw(10) << left << deck[i]->name << setw(10) << deck[i]->cardType << setw(10) << deck[i]->element << "\n" ;
    }

    cout << "\n\n Press anything to continue." ;
    cin.ignore(1000,'\n') ;
    getchar() ;

}

void Player::playCard(vector<Card*> &hand, vector<Card*> &field)
{
    cout << "Select a card to play from your deck:  " ;


    string s;
    int select;
    bool validInput = false;
    while(validInput == false)
    {
        try
            {
                cin >> s;

                select = stoi(s);
                if(select<1)
                {
                    throw invalid_argument("\nNegative input not allowed!\n") ;
                }
                if(select>hand.size())
                {
                    throw out_of_range("\nInput out of range!\n") ;
                }
                validInput = true;
            }
            catch(const exception& e)
            {
                cout << "\nInvalid input please try again.\n" ;
            }

    }


    if (hand[select-1]->cardType == "Marksman")
    {
        field.push_back(new Marksman(*hand[select-1])) ;
    }
    else if (hand[select-1]->cardType == "Tank")
    {
        field.push_back(new Tank(*hand[select-1])) ;
    }
    else if (hand[select-1]->cardType == "Mage")
    {
        field.push_back(new Mage(*hand[select-1])) ;
    }
    else if (hand[select-1]->cardType == "Assasin")
    {
        field.push_back(new Assasin(*hand[select-1])) ;
    }
    else if (hand[select-1]->cardType == "Support")
    {
        field.push_back(new Support(*hand[select-1])) ;
    }


    delete hand[select-1] ;
    hand.erase(hand.begin()+select-1) ;

}



Computer::Computer()
{
    this->name = "Computer" ;
    deck = new Card*[7] ;

    for (int i = 0; i < 7; i++)
    {
        deck[i] = nullptr;
    }

}

Computer::~Computer()
{
    for(int i=0; i<7; i++)
    {
        delete deck[i] ;
    }
    delete[] deck;
}

void Computer::playCard(vector<Card*> &hand, vector<Card*> &field)
{
    srand(time(0)) ;
    int select ;

    select = rand() % hand.size() ;

    cout << "\nComputer is selecting card...\n" ;
    Sleep(3000) ;

    if (hand[select]->cardType == "Marksman")
    {
        field.push_back(new Marksman(*hand[select])) ;
    }
    else if (hand[select]->cardType == "Tank")
    {
        field.push_back(new Tank(*hand[select])) ;
    }
    else if (hand[select]->cardType == "Mage")
    {
        field.push_back(new Mage(*hand[select])) ;
    }
    else if (hand[select]->cardType == "Assasin")
    {
        field.push_back(new Assasin(*hand[select])) ;
    }
    else if (hand[select]->cardType == "Support")
    {
        field.push_back(new Support(*hand[select])) ;
    }


    delete hand[select] ;
    hand.erase(hand.begin()+select) ;
}

void Computer::selectDeck(vector<vector<Card*>> preDecks, Card** cards, int cardsSize)
{
    srand(time(0)) ;
    int s;
    s = rand() % preDecks.size() ;
    cout << "\nComputer is selecting card...\n" ;
    Sleep(3000) ;
    for(int i = 0; i<7; i++)
        {
            this->deck[i] = preDecks[s][i] ;
        }
}


Boss::Boss()
{
    this->name = "BOSS" ;
    this->deck[0] = new Tank() ;
    deck[0]->name = "BOSS" ;
    deck[0]->element = "fire" ;
    deck[0]->setAtk(15)  ;
    deck[0]->setHp(500);
    deck[0]->cardType = "Tank" ;
    deck[0]->cardIndex = 99;
    deck[0]->hasAttacked = false;
    deck[0]->cdcounter = 1;
    deck[0]->isStunned = -99; // cant be stunned
    deck[0]->skill = skillBOSS ;
    deck[0]->cooldown = 1 ;

}

Boss::~Boss()
{
    delete deck[0] ;
    delete[] deck;
}

void Boss::playCard(vector<Card*> &hand, vector<Card*> &field)
{

    if(field.size() == 0)
    {
         field.push_back(new Tank(*hand[0])) ;
         delete hand[0] ;
         hand.erase(hand.begin()) ;
    }

}
