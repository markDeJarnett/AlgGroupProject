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

#include "point.h"

/*
 * description: point default constructor
 * return: none
 * precondition: none
 * postcondition: set the x, y, and color values
*/
point::point() {
    x = 0;
    y = 0;

    color.setR(0);
    color.setG(0);
    color.setB(0);
}

/*
 * description: point constructor
 * return: none
 * precondition: none
 * postcondition: set the x and y values
*/
point::point(int x, int y) {
    this->x = x;
    this->y = y;

    color.setR(0);
    color.setG(0);
    color.setB(0);
}

/*
 * description: point copy constructor
 * return: none
 * precondition: valid p exists
 * postcondition: set the x, y, and color values
*/
point::point(const point& p){
    this->x = p.x;
    this->y = p.y;
    this->color = p.color;
}

/*
 * description: point destructor
 * return: none
 * precondition: none
 * postcondition: set x and y to 0 and color values to 0
*/
point::~point(){
    x = 0;
    y = 0;

    color.setR(0);
    color.setB(0);
    color.setG(0);
}

/*
 * description: setter for x value
 * return: none
 * precondition: valid x exists
 * postcondition: set x
*/
void point::setX(int x){
    this->x = x;
}

/*
 * description: getter for x value
 * return: int
 * precondition: none
 * postcondition: return x value
*/
int point::getX(){
    return x;
}

/*
 * description: setter for y value
 * return: none
 * precondition: valid y exists
 * postcondition: set y
*/
void point::setY(int y){
    this->y = y;
}

/*
 * description: getter for y value
 * return: int
 * precondition: none
 * postcondition: return y value
*/
int point::getY(){
    return y;
}

/*
 * description: setter for color value
 * return: none
 * precondition: valid c exists
 * postcondition: set c
*/
void point::setColor(color_rgb c){
    this->color = c;
}

/*
 * description: getter for color value
 * return: color_rgb
 * precondition: none
 * postcondition: return color value
*/
color_rgb point::getColor(){
    return color;
}

/*
 * description: overloaded assignment operator
 *      for point class
 * return: point
 * precondition: valid rhs exists
 * postcondition: sets x, y, and color values
*/
point& point::operator=(const point& rhs){
    this->x = rhs.x;
    this->y = rhs.y;
    this->color = rhs.color;

    return *this;
}

/*
 * description: displays the coordinates (x, y)
 * return: none
 * precondition: valid out exists
 * postcondition: prints (x , y)
*/
void point::display(ostream& out){
    out << "(" << x << ", " << y << ")" << endl;
}

/*
 * description: plots points
 * return: none
 * precondition: valid g exists
 * postcondition: plots point onto SDL_Plotter
*/
void point::draw(SDL_Plotter& g) {
    g.plotPixel(x, y, color.getR(), color.getG(), color.getB());
    g.update();
}
