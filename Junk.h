/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef JUNK_H
#define JUNK_H

#include "Unit.h"
#include <QGraphicsScene>

class Junk : public Unit {
public:



    Junk() : Unit() {}

     Junk(const Point& p): Unit(p){}

     Junk* clone() const override;

    /*
     * did not crash yet
     */
     bool isAlive() const override;

    /*
     * Crashes and remembers it
     */
     void doCrash() override;

    /*
     * Return whether the robot crashed
     */
     bool isToBeJunked() const override;


     void moveTowards(const Point &) override;

    /*
    * Draws this junk onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const ;
};

#endif // JUNK_H
