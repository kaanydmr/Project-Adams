#include <iostream>
#include "card.h"
#include "skills.h"
#include "player.h"
#include "game.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string>
using namespace std ;
typedef void (*FunctionPointer)(vector<Card*> &field1,vector<Card*> &field2, Card* card);

void skill0(vector<Card*> &field1,vector<Card*> &field2, Card* card) // Leoxane
{
    srand(time(0)) ;


    int critrate  = 50 ;
    int x=1;
    int y = rand() % 100;
    if(y > critrate)
    {
        x = 2;
    }


    int atk = card->getAtk() * x + 5 ;
    field1[0]->setHp(field1[0]->getHp() - atk) ;

    cout << "Leoxane is using his skill! Leoxane makes an empowered attack and deals " << atk << " damage to " << field1[0]->name << ". " << field1[0]->name << "'s remaining hp:" << field1[0]->getHp() << "\n" ;
    card->cdcounter = 0;
}

void skill1(vector<Card*> &field1,vector<Card*> &field2, Card* card) // Mobayi's skill
{

    cout << "Mobayi is using his skill! Mobayi gets +20 hp.\n" ;
    card->setHp(card->getHp() + 20) ;
    card->cdcounter = 0;
}


void skill2(vector<Card*> &field1,vector<Card*> &field2, Card* card) // Marcus
{
    card->setHp(card->getHp() - 5) ;
    card->setAtk(card->getAtk() + 5) ;
    field1[0]->setHp(field1[0]->getHp() - card->getAtk()) ;
    cout << "Marcus is using his skill! Marcus sacrificed 5 hp to gain 5 attack damage and attacked " << field1[0]->name << " for " << card->getAtk() << " damage. " << field1[0]->name << "'s remaining hp: " << field1[0]->getHp() << "\n" ;

    card->cdcounter = 0;
}

void skill3(vector<Card*> &field1,vector<Card*> &field2, Card* card) // Bebi
{

    cout << "Bebi is using her skill! Bebi gained +10 hp and +5 attack damage.\n" ;
    card->setAtk(card->getAtk()+5) ;
    card->setHp(card->getHp() +10) ;
    card->cdcounter = 0;
}

void skill4(vector<Card*> &field1,vector<Card*> &field2, Card* card) // Muccuk
{
    bool asasvarmi = false ;
    int asasindex;

    for( int i=0; i<field1.size(); i++)
    {
        if(field1[i]->cardType == "Assasin")
        {
            asasvarmi = true;
            asasindex = i ;
            break;
        }
    }
    if(asasvarmi == true)
    {
        field1[asasindex]->isStunned += 2;
        field1[asasindex]->setHp(field1[asasindex]->getHp() - card->getAtk() / 2) ;
        cout << "Muccuk is using his skill! Muccuk stuns and deals " << card->getAtk()/2 << " damage to " << field1[asasindex]->name << ". " <<  field1[asasindex]->name << "'s remaining hp: " <<  field1[asasindex]->getHp() << "\n" ;

    }
    else
    {
        field1[0]->isStunned += 2;
        field1[0]->setHp(field1[0]->getHp() - card->getAtk() / 2) ;
        cout << "Muccuk is using his skill! Muccuk stuns and deals " << card->getAtk()/2 << " damage to " << field1[0]->name << ". " <<  field1[0]->name << "'s remaining hp: " <<  field1[0]->getHp() << "\n" ;

    }
    card->cdcounter = 0;
}

void skill5(vector<Card*> &field1,vector<Card*> &field2, Card* card) // Bedocan
{
    field1[0]->setHp(field1[0]->getHp() - (card->getAtk() + 10)) ;
    cout << "Bedocan is using his skill! Bedocan makes an empowered attack to  " << field1[0]->name << " and deals " << card->getAtk() + 10 << " damage. " <<  field1[0]->name << "'s remaining hp: " <<  field1[0]->getHp() << "\n" ;

    card->cdcounter = 0;
}

void skill6(vector<Card*> &field1,vector<Card*> &field2, Card* card) // Lorach
{


    int asasindex=0;

    for( int i=0; i<field2.size(); i++)
    {
        if(field2[i]->cardType == "Assasin")
        {

            asasindex = i ;
            break;
        }
    }


        cout << "Lorach is using his skill! Lorach heals " << field2[asasindex]->name << " +15 hp and grants +3 attack bonus.\n" ;
        field2[asasindex]->setHp(field2[asasindex]->getHp() + 10) ;
        field2[asasindex]->setAtk(field2[asasindex]->getAtk() + 3) ;


    card->cdcounter = 0;
}

void skill7(vector<Card*> &field1,vector<Card*> &field2, Card* card) // Umai
{
    int atk;
    if(field1.size() > 2)
    {
        atk = card->getAtk() *3/5;
        field1[0]->setHp(field1[0]->getHp()- atk) ;
        field1[1]->setHp(field1[1]->getHp()- atk) ;
        field1[2]->setHp(field1[2]->getHp()- atk) ;

        cout << "Umai is using his skill! Umai's attack deals " << atk << " area damage to " << field1[0]->name << ", " << field1[1]->name << " and " <<  field1[2]->name << ".\n" ;
    }
    else if(field1.size() == 2)
    {
        atk = card->getAtk() *4/5;
        field1[0]->setHp(field1[0]->getHp()- atk) ;
        field1[1]->setHp(field1[1]->getHp()- atk) ;
        cout << "Umai is using his skill! Umai's attack deals " << atk << " area damage to " << field1[0]->name << " and " << field1[1]->name << ".\n" ;
    }
    else if(field1.size() == 1)
    {
        atk = card->getAtk() * 6/5;
        field1[0]->setHp(field1[0]->getHp()- atk) ;
         cout << "Umai is using his skill! Umai's attack deals " << atk << " single target damage to " << field1[0]->name << ".\n" ;
    }


    card->cdcounter = 0;
}

void skill8(vector<Card*> &field1,vector<Card*> &field2, Card* card) // Bromen
{

    cout << "Bromen is using his skill! Bromen provided everyone in his team 3 hp shield.\n" ;
    for(int i=0; i<field2.size(); i++)
    {
        field2[i]->setHp(field2[i]->getHp()+3) ;
    }
    card->cdcounter = 0;
}

void skill9(vector<Card*> &field1,vector<Card*> &field2, Card* card) // Jagu
{

    int enazcanindex = 0;

    for(int i=0; i<field1.size(); i++)
    {
        if(field1[i]->getHp() < field1[enazcanindex]->getHp())
        {
            enazcanindex = i ;
        }
    }
    int atk = card->getAtk() + 5;

    field1[enazcanindex]->setHp(field1[enazcanindex]->getHp() - atk) ;
    card->setHp(card->getHp() + atk/2) ;
    cout << "Jagu is using his skill! Jagu increased his skill damage by 5 and deals " << atk << " damage to " << field1[enazcanindex]->name << ". Jagu heals himself +" << atk/2 << " hp. " << field1[enazcanindex]->name << "'s remaining hp: " << field1[enazcanindex]->getHp() << "\n" ;

    card->cdcounter = 0;
}

void skill10(vector<Card*> &field1,vector<Card*> &field2, Card* card) // Atreus
{

    int encokindex = 0;
    for(int i=0; i<field1.size(); i++)
    {
        if(field1[i]->getAtk() > field1[encokindex]->getAtk())
        {
            encokindex = i;
        }
    }
    field1[encokindex]->setHp(field1[encokindex]->getHp() - (card->getAtk() +5)) ;
    card->setAtk(card->getAtk()+5) ;
    cout << "Atreus is using his skill! Atreus attacked " << field1[encokindex]->name << " for " << card->getAtk()  << " damage. " << field1[encokindex]->name << "'s remaining hp: " << field1[encokindex]->getHp() << ". Atreus increased his attack damage by 5.\n" ;

    card->cdcounter = 0;
}
void skill11(vector<Card*> &field1,vector<Card*> &field2, Card* card) // Lisa
{

    int encokindex = 0;
    for(int i=0; i<field1.size(); i++)
    {
        if(field1[i]->getAtk() > field1[encokindex]->getAtk())
        {
            encokindex = i;
        }
    }
    cout << "Lisa is using her skill! " << field1[encokindex]->name << " is stunned.\n" ;
    field1[encokindex]->isStunned += 2;
    card->cdcounter = 0;
}

void skill12(vector<Card*> &field1,vector<Card*> &field2, Card* card) // Gus
{

    int encokindex = 0;
    for(int i=0; i<field1.size(); i++)
    {
        if(field1[i]->getAtk() > field1[encokindex]->getAtk())
        {
            encokindex = i;
        }
    }
     cout << "Gus is using his skill! " << field1[encokindex]->name << " is stunned and their attack damage is reduced by 5\n" ;
     field1[encokindex]->isStunned += 2;

     field1[encokindex]->setAtk(field1[encokindex]->getAtk()-5);
     card->cdcounter = 0;
}

void skill13(vector<Card*> &field1,vector<Card*> &field2, Card* card) // Saul
{

    bool tankvarmi = false ;
    int tankindex = 0;

    for( int i=0; i<field2.size(); i++)
    {
        if(field2[i]->cardType == "Tank")
        {
            tankvarmi = true;
            tankindex = i ;
            break;
        }
    }

    cout << "Saul is using his skill! " << field2[tankindex]->name << " is healed 15 hp.\n" ;
    field2[tankindex]->setHp(field2[tankindex]->getHp() + 15) ;
    card->cdcounter = 0;

}

void skill14(vector<Card*> &field1,vector<Card*> &field2, Card* card) // Hector
{
    srand(time(0)) ;


    int x = rand() % field1.size();

    cout << "Hector is using his skill! Hector kills " << field1[x]->name << " in exchange of his own life.\n" ;
    field1[x]->setHp(-99) ;
    card->setHp(0) ;
    card->cdcounter = 0;
}

void skill15(vector<Card*> &field1,vector<Card*> &field2, Card* card) // Xeno
{

    cout << "Xeno is using her skill! Xeno gains 5 hp shield and deals " << card->getAtk() *2/5 << " damage to everyone in enemy team.\n" ;
    card->setHp(card->getHp()+ 5) ;
    for(int i=0; i<field1.size(); i++)
    {
        field1[i]->setHp(field1[i]->getHp() - (card->getAtk()*2/5) ) ;
    }
    card->cdcounter = 0;
}

void skill16(vector<Card*> &field1,vector<Card*> &field2, Card* card) // Terra
{


    int enazindex = 0;
    for(int i=0; i<field2.size(); i++)
    {
        if(field2[i]->getHp() < field2[enazindex]->getHp())
        {
            enazindex = i;
        }
    }
    cout << "Terra is using his skill! Terra healed " << field2[enazindex]->name << " 20 hp and increased their attack by 5.\n" ;
    field2[enazindex]->setHp(field2[enazindex]->getHp() + 20) ;
    field2[enazindex]->setAtk(field2[enazindex]->getAtk() + 5) ;

    card->cdcounter = 0;
}

void skill17(vector<Card*> &field1,vector<Card*> &field2, Card* card) // Napo
{

    for(int i=0; i<field2.size(); i++)
    {
        field2[i]->setAtk(field2[i]->getAtk() + 3) ;
    }
    cout << "Napo is using his skill! Napo boosts everyone's attack in his team by 3.\n" ;
    card->cdcounter = 0;
}


void skillBOSS(vector<Card*> &field1, vector<Card*> &field2, Card* card) //BOSS SKIll
{
    srand(time(0));

    int bossSkill = rand() % 4;


    if(bossSkill == 0){
        card->setAtk(card->getAtk()+5) ;
        cout << "\033[1;34mIncreased +5 attack\033[0m\n";

    }
    else if(bossSkill == 1){

        cout << "\033[1;32mGained +50 hp.\033[0m\n" ;

        card->setHp(card->getHp() +50) ;

    }
    else if (bossSkill == 2){


        cout << "\033[1;31mAttacked everyone for \033[0m "<< card->getAtk() << " \033[1;31mDamage\033[0m\n" ;
        for(int i=0; i<field1.size(); i++)
        {
            field1[i]->setHp(field1[i]->getHp() - (card->getAtk())) ;
        }

    }
    else if (bossSkill == 3){

        cout << "\033[1;33mBoss missed skill\033[0m\n",
        Sleep(30);
    }


    card->cdcounter = 0;
}

void getSkills(FunctionPointer* skills, int size)
{
    for (int i = 0; i < size; i++)
    {
        skills[i] = nullptr;
    }

    skills[0] = skill0;
    skills[1] = skill1;
    skills[2] = skill2;
    skills[3] = skill3;
    skills[4] = skill4;
    skills[5] = skill5;
    skills[6] = skill6;
    skills[7] = skill7;
    skills[8] = skill8;
    skills[9] = skill9;
    skills[10] = skill10;
    skills[11] = skill11;
    skills[12] = skill12;
    skills[13] = skill13;
    skills[14] = skill14;
    skills[15] = skill15;
    skills[16] = skill16;
    skills[17] = skill17;

}

void assignSkills(Card** cards, FunctionPointer* skills,int size)
{
    for (int i = 0; i <size; i++)
    {
        cards[i]->skill = skills[i];
    }

}
