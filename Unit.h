/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 * Updated for TDDD86, 2021.
 */

#ifndef UNIT_H
#define UNIT_H

#include "utilities.h"
#include <QGraphicsScene>

/* Root class for all pieces on the board.
 * Subclasses are Robot, Hero and Junk.
 */
class Unit {
public:

    /*
     * Create a unit at a random position
     */
    Unit();

    virtual Unit* clone() const;

    /*
    * Create unit at given point
    */
    Unit(const Point& p);

    virtual ~Unit(){}

    /*
    * Return Point representation of Unit
    */
    Point asPoint() const;

    /*
    * Am I in the same square as u?
    */
    bool at(const Unit& u) const;


    /*
    * Take one step closer to point
    */
    virtual void moveTowards(const Point&);


    /*
    * Teleport. Does not check for collision
    */
    void teleport();

    /*
    * Euclidean distance to u
    */
    double distanceTo(const Unit& u) const;


    /*
    * Draws this robot onto the given QGraphicsScene.
    */
    virtual void draw(QGraphicsScene* scene) const;

    virtual bool isAlive() const;

    virtual void doCrash();

    virtual bool isToBeJunked() const;



private:
    int x;  // x position of this unit
    int y;  // y position of this unit
    bool toBeJunked = false;
    // private helpers
    void checkBounds();
};

#endif // UNIT_H
