/*
* Author: Michelle Aurora, Zee Dugar, Mark DeJarnett,
*         Elisa Gonzalez, Elissa Skinner
* Assignment Title: Final Project
* Assignment Description: This program implements
*         the point functions.
* Due Date: 4/5/2019
* Date Created: 1/17/2019
* Date Last Modified: 1/28/2019
*/

#ifndef FINALPROJECT_POINT_H
#define FINALPROJECT_POINT_H

#include <iostream>

#include "color_rgb.h"
#include "SDL_Plotter.h"

using namespace std;

class point {
public:
    point();
    point(int x, int y);
    point(const point& p);
    virtual ~point();
    void setY(int y);
    void setX(int x);
    void setColor(color_rgb c);
    int getX();
    int getY();
    color_rgb getColor();
    point& operator=(const point& rhs);
    void display(ostream&);
    void draw(SDL_Plotter&);

private:
    int x, y;
    color_rgb color;
};

#endif //FINALPROJECT_POINT_H
