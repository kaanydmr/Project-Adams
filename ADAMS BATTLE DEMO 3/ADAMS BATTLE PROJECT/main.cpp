#include "card.h"
#include "skills.h"
#include "game.h"
#include "player.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#define CARDCOUNT 18  // how many cards do we have

using namespace std;
typedef void (*FunctionPointer)(vector<Card*> &field1,vector<Card*> &field2, Card* card); // void function pointer type

    // functions
int displayMainMenu() ;
int credits() ;
void assignSkills(Card** cards, FunctionPointer* skills, int size) ;
void readCardsFromFile(const string& filename,Card** cards ,int size) ;
int askGameMode();
void tutorial() ;



int main()
{

    // get card array dynamically

    Card** cards = new Card*[CARDCOUNT] ;
    readCardsFromFile("cards.txt",cards,CARDCOUNT);  // read cards from cards.txt

     // get skills array dynamically. skills is a function pointer array
    FunctionPointer* skills = new FunctionPointer[CARDCOUNT];
    getSkills(skills,CARDCOUNT) ;  // skills.h

    // assign skill to each card
    assignSkills(cards,skills,CARDCOUNT) ; // skills.h

    // Prepared decks
    Card* d1[] = {cards[3],cards[4],cards[10],cards[1],cards[12],cards[0],cards[6]} ; // balanced deck
    Card* d2[] = {cards[0],cards[5],cards[14],cards[6],cards[1],cards[3],cards[10]} ; // assasins deck
    Card* d3[] = {cards[2],cards[3],cards[4],cards[7],cards[11],cards[15],cards[1]} ;  // Mage deck
    Card* d4[] = {cards[10],cards[17],cards[1],cards[6],cards[4],cards[14],cards[12]} ; // Marksman deck
    vector<vector<Card*>> preDecks ;

    preDecks.push_back(vector<Card*> (begin(d1), end(d1))) ;
    preDecks.push_back(vector<Card*> (begin(d2), end(d2))) ;
    preDecks.push_back(vector<Card*> (begin(d3), end(d3))) ;
    preDecks.push_back(vector<Card*> (begin(d4), end(d4))) ;

    Player p1("Player 1");
    Player p2("Player 2");
    Computer c;
    Boss boss;
    Game game;

    // start program
    int quitVariable = 0 ;
    while(quitVariable != 1)
    {
        switch(displayMainMenu())
        {
            case 1:
                // Play vs Computer

                switch(askGameMode())
                {
                    case 1:
                        // play vs computer classic
                        p1.selectDeck(preDecks,cards,CARDCOUNT) ;
                        c.selectDeck(preDecks,cards,CARDCOUNT) ;
                        game.play(p1,c) ;
                        break;

                    case 2:
                        // play vs boss
                        p1.selectDeck(preDecks,cards,CARDCOUNT) ;
                        game.playBOSS(boss,p1) ;
                        break;
                    case 9:
                        break;
                }


                break;
            case 2:
                // Player vs Player



                p1.selectDeck(preDecks,cards,CARDCOUNT) ;
                p2.selectDeck(preDecks,cards,CARDCOUNT) ;
                game.play(p1,p2) ;


                break;
            case 3:
                // Tutorial
                tutorial() ;
                break ;
            case 4:
                // view all Cards
                viewCards(cards,CARDCOUNT) ;
                break ;
            case 5:
                // credits
                credits() ;
                break ;
            case 6:
                cout << "\n\nExiting the game.." ;
                quitVariable = 1 ; // exit while loop and end the program
                break ;
            default:
                cout << "\nInvalid choice! Please select a number!\n" ;
                break;
        }
    }


    // Deallocate Memory
    for(int i = 0; i<CARDCOUNT; i++)
    {
        delete cards[i];
    }
    delete[] cards ;


    for(int i=0; i<7; i++)
    {
        delete p1.deck[i] ;
        delete p2.deck[i] ;
    }
    delete[] p1.deck ;
    delete[] p2.deck;
    delete[] skills;

    return(0) ;
}

int displayMainMenu()
{

    system("cls") ;
    cout << "          ADAMS BATTLE         |\n" ;
    cout << "_______________________________|\n\n" ;
    cout << "Press the number you want to select.\n\n" ;
    cout << "1. Player vs Computer\n" ;
    cout << "2. Player vs Player\n" ;
    cout << "3. Tutorial\n" ;
    cout << "4. Cards\n" ;
    cout << "5. Credits\n" ;
    cout << "6. Quit\n\n" ;

    string s;
    int select;
    bool validInput = false;
    while(validInput == false)
    {
        try
            {
                cin >> s;
                select = stoi(s);

                if(select<0)
                {
                    throw invalid_argument("\nNegative input not allowed!\n") ;
                }
                if(select>6)
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

    return select;
}



void readCardsFromFile(const string& filename, Card** cards ,int size)
{
    ifstream cardFile(filename);

    if (!cardFile.is_open())
    {
        cerr << "Error opening the file!" << endl;
    }


    int i;
    string cardtype ;


    for(i = 0; i<size; i++)
    {

        getline(cardFile, cardtype, '\t');

        if(cardtype == "Assasin")
        {
            cards[i] = new Assasin();
        }
        else if(cardtype == "Tank")
        {
            cards[i] = new Tank();

        }
        else if(cardtype == "Mage")
        {
            cards[i] = new Mage();

        }
        else if(cardtype == "Marksman")
        {
            cards[i] = new Marksman();

        }
        else if(cardtype == "Support")
        {
            cards[i] = new Support();

        }
        else
        {
            continue;
        }

        int hp, atk ,cd;
        cards[i]->cardType = cardtype ;
        getline(cardFile, cards[i]->element, '\t');
        getline(cardFile, cards[i]->name, '\t');
        cardFile >> cards[i]->cardIndex ;
        cardFile >> ws;
        cardFile >> atk;
        cardFile >> ws;
        cardFile >> hp;
        cardFile >> ws;
        cardFile >> cd ;
        cardFile >> ws;
        getline(cardFile, cards[i]->skillString, '\n') ;


        cards[i]->setAtk(atk) ;
        cards[i]->setHp(hp) ;
        cards[i]->cooldown = cd;

    }

    cardFile.close();

}

void tutorial()
{


    string s;
    int select;


    while(true)
    {
        system("cls") ;
        cout << "Welcome to tutorial. Select the topic you want to learn.(x for returning main menu): \n\n" ;

        cout << "1. Card Attributes\n" ;
        cout << "2. Element Superiority\n" ;
        cout << "3. Skills\n" ;
        cout << "4. Battle screen\n" ;
        cout << "5. Playing vs Boss\n" ;

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
                    if(select>5)
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
            break ;

        switch(select)
        {
            case 1: // card attributes
                system("cls") ;
                cout << "*** Cards have name, attack, hp, element, Type and skill.\n\n" ;
                cout << "          -Bromen  6     81    earth     Tank-\n" ;
                cout << "             |     |     |       |         |\n";
                cout << "             V     V     V       V         V\n";
                cout << "           name   atk    hp    element   card type\n\n" ;
                cout << "-> Attack decides how much damage will the card deal.\n" ;
                cout << "-> Hp is the health point of the card. If it falls below 0, character will die.\n";
                cout << "\n  There are 5 types of Cards:\n";
                cout << "1. Tank:\n" ;
                cout << "- Tanks have high health points to take the front damage. If there is a Tank type card on the enemy field, cards will attack the Tank first.\n";
                cout << "\n2.Support:\n";
                cout << "- Supports are here to heal your cards. Their automatic attack doesn't deal any damage but it will increase the HP of a card in your team.\n";
                cout << "\n3.Mage:\n";
                cout << "- Mages will get stronger as the game goes on. When a Mage type card attacks, they get +5 attack increase permanently. But they are weak early game.\n";
                cout << "\n4.Marksman:\n";
                cout << "- Marksmans will carry the damage load for your team. Marksman type cards have the possibility to deal Critical Damage. It will double their damage.(x2)\n" ;
                cout << "\n5.Assasin:\n";
                cout << "- Assasins will target the Lowest Health card. Assasins can bypass the Tank type in enemy field. Assasins have high attack damage early game.\n" ;
                cout << "\nPress anything to continue." ;
                cin.ignore(1000,'\n');
                getchar() ;
                break ;

            case 2:  // element superiority
                system("cls") ;
                cout << "-> There are 3 element types:\n";
                cout << "1.fire\n2.earth\n3.water\n\n";
                cout << "-> Elements counter each other like a triangle.\n\n" ;
                cout << "   fire>earth, earth>water, water>fire\n\n";
                cout << "-> When a card attacks, the elements of the card they are attacking are compared.\n";
                cout << "-> If the attacking card's element is superior, the damage is doubled.\n-> Element superior doesn't affect defending or skills." ;
                cout << "\n\nPress anything to continue." ;
                cin.ignore(1000,'\n');
                getchar() ;
                break ;

            case 3: // skills
                system("cls") ;
                cout << "-> Each card have their unique skill.\n-> Skills have cooldown so they can't always use their skill (except if their cooldown is 0).\n\n" ;
                cout << "-> When the round ends, cooldowns of the cards on the field will be reduced by 1.\n-> When the time comes for the card, they will use their skill!\n\n-> You can see it in Battle Info part.\n\n";
                cout << "\nPress anything to continue." ;
                cin.ignore(1000,'\n');
                getchar() ;
                break ;

            case 4:  // gameplay
                system("cls") ;
                cout << "-> When the game starts, Players will choose a card to play from their deck. This card is placed in the Field section.\n-> After the cards are selected, battle will start.\n" ;
                cout << "\n-> Cards fight automatically on the battle screen.\n-> You can view what is happening from the Battle Info section.\n" ;
                cout << "\n-> When round ends, player will go back to the screen where they are playing card. This continues until one side has no cards left.\n" ;
                cout << "\n-> You can develop different strategies to win.\n-> Enjoy our game!\n" ;
                cout << "\n\nPress anything to continue." ;
                cin.ignore(1000,'\n');
                getchar() ;
                break ;

            case 5: // Playing vs Boss
                system("cls") ;
                cout << "-> Boss has the following attributes:\n\n" ;
                cout << "hp: 500\n\n";
                cout << "atk: 15\n\n";
                cout << "Card type: Tank\n\n" ;
                cout << "Element: fire\n\n";
                cout << "Boss have 4 different skills:\n\n";
                cout << "->1. Increases attack by 5.\n";
                cout << "->2. Heals +50 hp.\n";
                cout << "->3. Deals damage to EVERYONE equal to atk.\n" ;
                cout << "->4. Miss skill.\n" ;
                cout << "\n\nPress anything to continue." ;
                cin.ignore(1000,'\n');
                getchar() ;
                break ;
        }
    }
}



int credits()
{
    system("cls") ;
    cout << "Developers\n" << endl;
    cout << "Kaan Aydemir" << endl;
    cout << "Edip Alper Selcuk" << endl;
    cout << "Fatih Gazi Goc" << endl;



    cout << "\n\nPress anything to return main menu\n" ;
    cin.ignore(1000,'\n') ;
    getchar() ;

    return 0;
}

int askGameMode()
{
    system("cls") ;
    cout << "1.Play vs Computer Classic Mode\n" ;
    cout << "2.Play vs Boss\n\n" ;
    cout << "Select game mode(x for returning main menu): ";

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
        return 9;
    return select;
}

