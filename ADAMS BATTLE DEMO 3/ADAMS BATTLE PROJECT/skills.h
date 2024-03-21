#ifndef  SKILLS_H
#define  SKILLS_H

#include <iostream>
#include "card.h"
#include <vector>


using namespace std;

typedef void (*FunctionPointer)(vector<Card*> &field1,vector<Card*> &field2, Card* card);

void skill0(vector<Card*> &field1,vector<Card*> &field2, Card* card) ;
void skill1(vector<Card*> &field1,vector<Card*> &field2, Card* card) ;
void skill2(vector<Card*> &field1,vector<Card*> &field2, Card* card) ;
void skill3(vector<Card*> &field1,vector<Card*> &field2, Card* card) ;
void skill4(vector<Card*> &field1,vector<Card*> &field2, Card* card) ;
void skill5(vector<Card*> &field1,vector<Card*> &field2, Card* card) ;
void skill6(vector<Card*> &field1,vector<Card*> &field2, Card* card) ;
void skill7(vector<Card*> &field1,vector<Card*> &field2, Card* card) ;
void skill8(vector<Card*> &field1,vector<Card*> &field2, Card* card) ;
void skill9(vector<Card*> &field1,vector<Card*> &field2, Card* card) ;
void skill10(vector<Card*> &field1,vector<Card*> &field2, Card* card) ;
void skill11(vector<Card*> &field1,vector<Card*> &field2, Card* card) ;
void skill12(vector<Card*> &field1,vector<Card*> &field2, Card* card) ;
void skill13(vector<Card*> &field1,vector<Card*> &field2, Card* card) ;
void skill14(vector<Card*> &field1,vector<Card*> &field2, Card* card) ;
void skill15(vector<Card*> &field1,vector<Card*> &field2, Card* card) ;
void skill16(vector<Card*> &field1,vector<Card*> &field2, Card* card) ;
void skillBOSS(vector<Card*> &field1, vector<Card*> &field2, Card* card) ;

void getSkills(FunctionPointer* skills, int size) ;
void assignSkills(Card** cards, FunctionPointer* skills, int size) ;


#endif // SKILLS_H
