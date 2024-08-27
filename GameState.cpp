/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 * Updated for TDDD86, 2021.
 */

#include "GameState.h"
#include "utilities.h"
#include "constants.h"
#include <iostream>

using namespace std;
    /*
    * Contructor of new Robots at the begining of rounds depending on amount of numberOfRobots variable and check that they are not at same pos
    *
   */
GameState::GameState(int numberOfRobots) {
   for (int i = 0; i < numberOfRobots; i++) {

        Robot *robot = new Robot();


        while(!isEmpty(*robot)){

            delete robot;
            robot = new Robot();
        }

        unitVector.push_back(robot);

    }
    teleportHero();
}
    /*
        will preform a copy of right hand data into the new init object on the left. object = right hand data.
    */
GameState::GameState(const GameState& object){
    hero = object.hero;
    // upcasting unitvector object to unit and create copy of old unit with new pointer and value
    for (Unit *unit : object.unitVector){
        unitVector.push_back(unit->clone());
    }

}
/*
    when gamestate is out of scope or deleted delete all units from unitvector
*/
GameState::~GameState(){
    // destructor deletes construtor created object

    for(Unit *unit : unitVector){
        delete unit;
    }
}
/*
    will be called when we want to copy already initialised GameState class
    gamestate = GameState(10)
    want to copy right hand data to left hand already initalised GameState variable
*/
GameState & GameState::operator=(const GameState & object){

    // similar to copy constructor but must clean up the data of assigment target
    // protects against invalid self-assignment
    if (this != &object){

        for (Unit *unit : unitVector){
            // dellocated old memory
            delete unit;

        }

        hero = object.hero;
        unitVector.clear();
        // assign the new memory to object
        // upcasting unitvector object to unit and create copy of old unit with new pointer and value

        for (Unit *unit :object.unitVector){

            unitVector.push_back(unit->clone());
        }

    }
     cout << "xd" << endl;
    return *this;
}
/*
* clear scene and draw hero and units in unitvector
*/
void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();
    hero.draw(scene);
    for (int i = 0;i < unitVector.size(); i++)
    {
        unitVector[i]->draw(scene);

    }


}
/*
* teleport hero to random point
*/
void GameState::teleportHero() {
    do hero.teleport();
    while (!isEmpty(hero));
}
/*
* move robots in unitvector towards hero 
*/
void GameState::moveRobots() {
    for (int i = 0;i < unitVector.size(); i++)
    {
       unitVector[i]->moveTowards (hero.asPoint());
    }
}

/*
* loop through unit vector and if unit is at the same point as another unit call do crash function on both
* either doing nothing if unit is junk or mark the unit to be junked if robot.
*/

void GameState::updateCrashes() {
     for(unsigned i=0; i < unitVector.size(); ++i){

        for(unsigned o=i+1; o < unitVector.size(); ++o){
            if(unitVector[i]->at(*unitVector[o])){

                unitVector[i]->doCrash();
                unitVector[o]->doCrash();


            }
        }

    }



}
/*
  loop through unitvector if unit is to be junked increase number Destroyed  
*/
int GameState::countToBeJunked()const{
    
    int numberDestroyed =0;
    for(unsigned i=0; i < unitVector.size(); ++i)
        if(unitVector[i]->isToBeJunked()){
            numberDestroyed++;
        }
    return numberDestroyed;
}

/*
* loop through unit vector and if unit isToBeJunked() create a new junk at the point of the Robot and add it to unitvector
* delete and remove old robot from unitvector
*/
void GameState::junkTheCrashed(){

    for(unsigned i=0; i < unitVector.size(); ++i){
        if (unitVector[i]->isToBeJunked()) {
            unitVector.push_back(new Junk(unitVector[i]->asPoint()));
            delete unitVector[i];
            unitVector[i] = unitVector[unitVector.size()-1];
            unitVector.pop_back();
        }
    }
}
// check if there are robots left alive
bool GameState::someRobotsAlive() const {
    for(unsigned i=0; i < unitVector.size(); ++i)
        if(unitVector[i]->isAlive())
            return true;
    return false;
}

// check if hero has collided with junk or robots and therfore should be killed
bool GameState::heroDead() const {
    for(const Unit* unit: unitVector){
        if(hero.at(*unit)){
            return true;
        }
    }

    return false;
}

// move hero towards given direction
void GameState::moveHeroTowards(const Point& dir) {
    hero.moveTowards(dir);
}
// return points of hero 
Point GameState::getHeroAsPoint() const {return hero.asPoint();}

/*
 * Free of robots and junk
 */
bool GameState::isEmpty(const Unit& unite) const {
    for(const Unit* unit: unitVector)
        if(unit->at(unite))
            return false;

    return true;
}

