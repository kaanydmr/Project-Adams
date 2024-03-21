#include "game.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <Windows.h>
#include <iomanip>
#include "card.h"
#include <vector>
#include "player.h"
#include "skills.h"

using namespace std;



Game::Game()
{

}

Game::~Game()
{

}

void Game::play(Player &p1, Player &p2)
{

    srand(time(0)) ;
    int round = 1;

    vector<Card*> cardVector1;
    for (int i = 0; i < 7; i++)
    {
        cardVector1.push_back(p1.deck[i]);
    }
    vector<Card*> cardVector2;

    for (int i = 0; i < 7; i++)
    {
        cardVector2.push_back(p2.deck[i]);
    }

    vector<Card*> hand1 ;
    vector<Card*> hand2 ;

    vector<Card*> field1 ;
    vector<Card*> field2 ;



for (Card* card : cardVector1) {
    if (card->cardType == "Marksman")
    {
        hand1.push_back(new Marksman(*card)) ;
    }
    else if (card->cardType == "Tank")
    {
        hand1.push_back(new Tank(*card)) ;
    }
    else if (card->cardType == "Mage")
    {
       hand1.push_back(new Mage(*card)) ;
    }
    else if (card->cardType == "Assasin")
    {
        hand1.push_back(new Assasin(*card)) ;
    }
    else if (card->cardType == "Support")
    {
        hand1.push_back(new Support(*card)) ;
    }
}

for (Card* card : cardVector2) {
    if (card->cardType == "Marksman")
    {
        hand2.push_back(new Marksman(*card)) ;
    }
    else if (card->cardType == "Tank")
    {
        hand2.push_back(new Tank(*card)) ;
    }
    else if (card->cardType == "Mage")
    {
        hand2.push_back(new Mage(*card)) ;
    }
    else if (card->cardType == "Assasin")
    {
        hand2.push_back(new Assasin(*card)) ;
    }
    else if (card->cardType == "Support")
    {
        hand2.push_back(new Support(*card)) ;
    }

}

    system("cls") ;

    for(int i=5; i>0; i--)
    {
        cout << "Game will start in " << i << " seconds. Get ready.\n" ;
        Sleep(1000) ;
    }

    // start game
    bool ending = false;
    int turn;

    while(ending == false)
    {
        if(round % 2 == 1)
        {
            turn = 1;
        }
        else if(round % 2 == 0)
        {
            turn = 2;
        }


        if(turn == 1)
        {
            displayScreen(p1,p2,hand1,hand2,field1,field2,round) ;

            if(!hand1.empty())
            {
                cout << p1.name << "'s turn. ";
                p1.playCard(hand1,field1) ;
            }
            displayScreen(p1,p2,hand1,hand2,field1,field2,round) ;

            if(!hand2.empty())
            {
                cout << p2.name << "'s turn. ";
                p2.playCard(hand2,field2) ;
            }
            displayScreen(p1,p2,hand1,hand2,field1,field2,round) ;


        }

        else if(turn == 2)
        {
            displayScreen(p1,p2,hand1,hand2,field1,field2,round) ;

            if(!hand2.empty())
            {
                cout << p2.name << "'s turn. ";
                p2.playCard(hand2,field2) ;
            }

            displayScreen(p1,p2,hand1,hand2,field1,field2,round) ;

            if(!hand1.empty())
            {
                cout << p1.name << "'s turn. ";
                p1.playCard(hand1,field1) ;
            }

            displayScreen(p1,p2,hand1,hand2,field1,field2,round) ;
        }

        cout << "\n\n" ;
        for(int i=3; i>0; i--)
        {
            cout << "Battle starting in " << i << " seconds\n" ;
            Sleep(1000) ;
        }
        battleScreen(field1,field2,round,p1,p2) ;
        round++ ;

        if(hand1.empty() == true && field1.empty() == true)
        {
            system("cls") ;
            cout << "\n\n" << p2.name << " WON THE GAME!\n\n" ;
            ending = true;
        }

        if(hand2.empty() == true && field2.empty() == true)
        {
            system("cls") ;
            cout << "\n\n" << p1.name << " WON THE GAME!\n\n" ;
            ending = true;
        }
        // bi taraf kaybederse ending = true
    } // while bitisi

    cout << "\nPress anything to return main menu" ;
    cin.ignore(1000,'\n') ;
    getchar() ;


    for (Card* card : hand1)
    {
        delete card;
    }

    for (Card* card : hand2)
    {
        delete card;
    }
    for (Card* card : field1)
    {
        delete card;
    }
    for (Card* card : field2)
    {
        delete card;
    }
    for(int i=0; i<7; i++)
    {
        p1.deck[i] = nullptr;
        p2.deck[i] = nullptr;
    }
    hand1.clear();
    hand2.clear();
    field1.clear();
    field2.clear();
    cardVector1.clear();
    cardVector2.clear();
}

void printBattle(vector<Card*> field1,vector<Card*> field2,int round)
{
    system("cls") ;
    cout << "                                       ROUND: " << round;
    cout << "\n\n\nFIELD 1:    " ;
    for(int i=0; i<field1.size(); i++)
    {
        field1[i]->cardImage() ;
        cout << "    " ;
    }
    cout << "\n\n\n____________________________________________________________________________________________________  damage advantages(x2):    water>fire; fire>earth; earth>water\n\n\n" ;

    cout << "FIELD 2:    " ;
    for(int i=0; i<field2.size(); i++)
    {
        field2[i]->cardImage() ;
        cout << "    " ;
    }
    cout << "\n\n\n\n" ;
    cout << "Battle Info:\n\n";
}

void battleScreen(vector<Card*> &field1,vector<Card*> &field2,int round,Player &p1, Player &p2)
{

    printBattle(field1,field2,round) ;
    Sleep(2000) ;

    for(int i=0; i<field1.size(); i++)
    {
        field1[i]->hasAttacked = false;
        if(field1[i]->isStunned > 0)
            field1[i]->isStunned -= 1;
    }
    for(int i=0; i<field2.size(); i++)
    {
        field2[i]->hasAttacked = false;
        if(field2[i]->isStunned > 0)
            field2[i]->isStunned -= 1;

    }

    int a,b;
    bool endRound = false;

    while(endRound == false)
    {
        if(round % 2 == 1)
        {
                for(a=0; a<field1.size(); a++)       // 1 field karti atak yapiyor
                {
                    if(field1[a]->hasAttacked == false && field1[a]->isStunned <= 0 && field2.size() > 0)
                    {
                        cout << p1.name << " : " ;
                        field1[a]->attack(field2,field1) ;
                        Sleep(4300) ;
                        break ;
                    }
                }

                for (int i=0; i<field2.size(); i++)   // 2.field ölenleri cikar
                    {
                        if (field2[i]->isDead())
                        {
                            cout << "\n" << field2[i]->name << " is dead!\n";
                            Sleep(3000);
                            delete field2[i];
                            field2.erase(field2.begin() + i);
                            i--;
                        }
                    }

                for(b=0; b<field2.size(); b++)    // 2. field attack yapiyor
                {
                    if(field2[b]->hasAttacked == false && field2[b]->isStunned <= 0 && field1.size() > 0)
                    {
                        cout << p2.name << " : " ;
                        field2[b]->attack(field1,field2) ;
                        Sleep(4300) ;
                        break ;
                    }
                }

                 for (int i=0; i<field1.size(); i++)  // 1. field ölenleri cikar
                    {
                        if (field1[i]->isDead())
                        {
                            cout << "\n" << field1[i]->name << " is dead!\n";
                            Sleep(3000);
                            delete field1[i];
                            field1.erase(field1.begin() + i);
                            i--;
                        }
                    }

                endRound = true;
                for(int i=0; i<field1.size(); i++) // butun cardlar saldirmis mi diye kontrol et, eger bir tane bile varsa roundu bitirme 1.field
                {
                    if(field1[i]->hasAttacked == false && field1[i]->isStunned <= 0 && field2.size() >0)
                    {
                        endRound = false ;
                        break ;
                    }
                    else{continue;}
                }
                for(int i=0; i<field2.size(); i++) // butun cardlar saldirmis mi diye kontrol et, eger bir tane bile varsa roundu bitirme 2.field
                {
                    if(field2[i]->hasAttacked == false && field2[i]->isStunned <= 0 && field1.size() >0)
                    {
                        endRound = false ;
                        break ;
                    }
                    else{continue;}
                }


        }


        else if(round % 2 == 0)
        {
            for(b=0; b<field2.size(); b++)       // 2. field karti atak yapiyor
                {
                    if(field2[b]->hasAttacked == false && field2[b]->isStunned <= 0 && field1.size() > 0)
                    {
                        cout << p2.name << " : " ;
                        field2[b]->attack(field1,field2) ;
                        Sleep(4300) ;
                        break ;
                    }
                }

                 for (int i=0; i<field1.size(); i++) // 1. field ölenleri cikar
                    {
                        if (field1[i]->isDead())
                        {
                            cout << "\n" << field1[i]->name << " is dead!\n";
                            Sleep(3000);
                            delete field1[i];
                            field1.erase(field1.begin() + i);
                            i--;
                        }
                    }

                for(a=0; a<field1.size(); a++)    // 1. field attack yapiyor
                {
                    if(field1[a]->hasAttacked == false && field1[a]->isStunned <= 0 && field2.size() > 0)
                    {
                        cout << p1.name << " : " ;
                        field1[a]->attack(field2,field1) ;
                        Sleep(4300) ;
                        break ;
                    }
                }

                 for (int i=0; i<field2.size(); i++) // 2.field ölenleri cikar
                    {
                        if (field2[i]->isDead())
                        {
                            cout << "\n" << field2[i]->name << " is dead!\n";
                            Sleep(3000);
                            delete field2[i];
                            field2.erase(field2.begin() + i);
                            i--;
                        }
                    }

                endRound = true;
                for(int i=0; i<field1.size(); i++) // butun cardlar saldirmis mi diye kontrol et, eger bir tane bile varsa roundu bitirme 1.field
                {
                    if(field1[i]->hasAttacked == false && field1[i]->isStunned == 0 && field2.size() >0)
                    {
                        endRound = false ;
                        break ;
                    }
                    else{continue;}
                }
                for(int i=0; i<field2.size(); i++) // butun cardlar saldirmis mi diye kontrol et, eger bir tane bile varsa roundu bitirme 2.field
                {
                    if(field2[i]->hasAttacked == false && field2[i]->isStunned == 0 && field1.size() >0)
                    {
                        endRound = false ;
                        break ;
                    }
                    else{continue;}
                }
        }
    } // end of round


    cout << "\nEnd of Round " << round  ;
    for(int i=0; i<field1.size(); i++)
    {
        field1[i]->cdcounter += 1 ;

    }

    for(int i=0; i<field2.size(); i++)
    {
        field2[i]->cdcounter += 1 ;

    }
    Sleep(4000) ;


}

void displayScreen(Player &p1, Player &p2,vector<Card*> &hand1,vector<Card*> &hand2,vector<Card*> &field1,vector<Card*> &field2,int round)
{

    /*

*/
    system("cls") ;


    cout << p1.name << "\n\n";
    cout << "Deck 1:     name    atk   hp    type     element\n\n" ;

    for (int i = 0; i < hand1.size(); i++)
    {
        cout << "     " << i+1 << ")    " << hand1[i]->name ;
        for(int x=10-hand1[i]->name.length(); x>=0; x--)
            {
                cout << " ";
            }
            cout << hand1[i]->getAtk() << "  " << hand1[i]->getHp() << "  " << hand1[i]->cardType ;
            for(int x=10-hand1[i]->cardType.length(); x>=0; x--)
            {
                cout << " ";
            }
            cout << hand1[i]->element;


        cout << "\n";
    }

    cout << "\n\n\n                                    BATTLE FIELD\n\n\n" ;
    cout << p1.name << " area:       " ;
    for(int i = 0; i<field1.size(); i++)
    {
        field1[i]->cardImage() ;
        cout << "    " ;
    }

    cout << "\n\n\nROUND: " << round << "__________________________________________________________________________________________________________   damage advantages(x2):    water>fire; fire>earth; earth>water\n\n\n" ;

    cout << p2.name << " area:       " ;
    for(int i = 0; i<field2.size(); i++)
    {
        field2[i]->cardImage() ;
        cout << "    " ;
    }

    cout << "\n\n\n\n" << p2.name << "\n\n";
   cout << "Deck 2:     name    atk   hp    type     element\n\n" ;

    for (int i = 0; i < hand2.size(); i++)
    {
        cout << "     " << i+1 << ")    " << hand2[i]->name ;
        for(int x=10-hand2[i]->name.length(); x>=0; x--)
            {
                cout << " ";
            }
            cout << hand2[i]->getAtk() << "  " << hand2[i]->getHp() << "  " << hand2[i]->cardType;
            for(int x=10-hand2[i]->cardType.length(); x>=0; x--)
            {
                cout << " ";
            }
            cout << hand2[i]->element ;

        cout << "\n";
    }
    cout << "\n\n" ;





}

bool checkError(Card** cards, Player &p,int choose ,int cardsSize)  // check if user selecting same card
{
    for(int x = 0; x<7; x++)
    {
        if(p.deck[x] == cards[choose])
        {
            cout << "\nYou cant select same card\n\n" ;
            return false;
        }
    }
    return true;
}




void infoCard(Card** cards, int cardsSize)
{
    cout << "Cards: \n\n";

    for(int i=0; i<cardsSize; i++)
    {
        cout << cards[i]->cardIndex << ". " << setw(10) << left << cards[i]->name << setw(10) << cards[i]->cardType << setw(10) << cards[i]->element << "\n" ;
    }
}


void viewCards(Card** cards, int cardsSize)
{

    infoCard(cards,cardsSize) ;

    string select;
    int s ;
    bool validInput = false;

    while(validInput == false)
    {

        cout << "\nSelect the card you want to view(x for returning main menu): " ;
        try
        {   cin >> select;
            if(select == "x")
                break;
            s = stoi(select);
            if(s<0)
            {
                throw invalid_argument("\nNegative input not allowed!\n") ;
            }
            if(s>=cardsSize)
            {
                throw out_of_range("\nInput out of range!\n") ;
            }
            validInput = true;
        }
        catch(const exception& e)
        {
            cout << "\nInvalid input please try again.\n" ;
        }
        if(select == "x")
            break;
    }

    if(select == "x")
        return;

    for(int i=0; i<cardsSize; i++)
    {
        if(cards[i]->cardIndex == s)
        {
            cards[i]->displayCard();
            cout << "\n\n" ;
            cards[i]->cardImage() ;
            break;
        }
    }

    cout << "\n\n\nPress anything to return:\n";
    cin.ignore(1000,'\n');
    getchar() ;

    system("cls") ;


    viewCards(cards,cardsSize);

}


void Game::playBOSS(Player &p1, Player &p2)
{

    srand(time(0)) ;
    int round = 1;

    vector<Card*> cardVector1;

    cardVector1.push_back(p1.deck[0]);

    vector<Card*> cardVector2;

    for (int i = 0; i < 7; i++)
    {
        cardVector2.push_back(p2.deck[i]);
    }

    vector<Card*> hand1 ;
    vector<Card*> hand2 ;

    vector<Card*> field1 ;
    vector<Card*> field2 ;



for (Card* card : cardVector1) {
    if (card->cardType == "Marksman")
    {
        hand1.push_back(new Marksman(*card)) ;
    }
    else if (card->cardType == "Tank")
    {
        hand1.push_back(new Tank(*card)) ;
    }
    else if (card->cardType == "Mage")
    {
       hand1.push_back(new Mage(*card)) ;
    }
    else if (card->cardType == "Assasin")
    {
        hand1.push_back(new Assasin(*card)) ;
    }
    else if (card->cardType == "Support")
    {
        hand1.push_back(new Support(*card)) ;
    }
}

for (Card* card : cardVector2) {
    if (card->cardType == "Marksman")
    {
        hand2.push_back(new Marksman(*card)) ;
    }
    else if (card->cardType == "Tank")
    {
        hand2.push_back(new Tank(*card)) ;
    }
    else if (card->cardType == "Mage")
    {
        hand2.push_back(new Mage(*card)) ;
    }
    else if (card->cardType == "Assasin")
    {
        hand2.push_back(new Assasin(*card)) ;
    }
    else if (card->cardType == "Support")
    {
        hand2.push_back(new Support(*card)) ;
    }

}

    system("cls") ;

    for(int i=5; i>0; i--)
    {
        cout << "Game will start in " << i << " seconds. Get ready.\n" ;
        Sleep(1000) ;
    }

    // start game
    bool ending = false;
    int turn;

    while(ending == false)
    {
        if(round % 2 == 1)
        {
            turn = 1;
        }
        else if(round % 2 == 0)
        {
            turn = 2;
        }


        if(turn == 1)
        {
            displayScreen(p1,p2,hand1,hand2,field1,field2,round) ;

            if(!hand1.empty())
            {
                cout << p1.name << "'s turn. ";
                p1.playCard(hand1,field1) ;
            }
            displayScreen(p1,p2,hand1,hand2,field1,field2,round) ;

            if(!hand2.empty())
            {
                cout << p2.name << "'s turn. ";
                p2.playCard(hand2,field2) ;
            }
            displayScreen(p1,p2,hand1,hand2,field1,field2,round) ;


        }

        else if(turn == 2)
        {
            displayScreen(p1,p2,hand1,hand2,field1,field2,round) ;

            if(!hand2.empty())
            {
                cout << p2.name << "'s turn. ";
                p2.playCard(hand2,field2) ;
            }

            displayScreen(p1,p2,hand1,hand2,field1,field2,round) ;

            if(!hand1.empty())
            {
                cout << p1.name << "'s turn. ";
                p1.playCard(hand1,field1) ;
            }

            displayScreen(p1,p2,hand1,hand2,field1,field2,round) ;
        }

        cout << "\n\n" ;

        for(int i=3; i>0; i--)
        {
            cout << "Battle starting in " << i << " seconds\n" ;
            Sleep(1000) ;
        }
        battleScreen(field1,field2,round,p1,p2) ;
        round++ ;

        if(hand1.empty() == true && field1.empty() == true)
        {
            system("cls") ;
            cout << "\n\n" << p2.name << " WON THE GAME!\n\n" ;
            ending = true;
        }

        if(hand2.empty() == true && field2.empty() == true)
        {
            system("cls") ;
            cout << "\n\n" << p1.name << " WON THE GAME!\n\n" ;
            ending = true;
        }
        // bi taraf kaybederse ending = true
    } // while bitisi

    cout << "\nPress anything to return main menu" ;
    cin.ignore(1000,'\n') ;
    getchar() ;


    for (Card* card : hand1)
    {
        delete card;
    }

    for (Card* card : hand2)
    {
        delete card;
    }
    for (Card* card : field1)
    {
        delete card;
    }
    for (Card* card : field2)
    {
        delete card;
    }
}
