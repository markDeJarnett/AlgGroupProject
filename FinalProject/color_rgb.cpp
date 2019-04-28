/*
* Author: Michelle Aurora
* Assignment Title: Program 0
* Assignment Description: This program implements
*   the color_rgb functions.
* Due Date: 1/28/109
* Date Created: 1/17/2019
* Date Last Modified: 1/25/2019
 */

#include "color_rgb.h"

/*
 * description: color_rgb default constructor
 * return: none
 * precondition: none
 * postcondition: set the r, g, b values
*/
color_rgb::color_rgb() {
    r = 0;
    g = 0;
    b = 0;
}

/*
 * description: color_rgb constructor
 * return: none
 * precondition: valid r, g, b exist
 * postcondition: set the r, g, b values
*/
color_rgb::color_rgb(int r, int g, int b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

/*
 * description: color_rgb destructor
 * return: none
 * precondition: none
 * postcondition: set r, g, b values to 0
*/
color_rgb::~color_rgb(){
    r = 0;
    g = 0;
    b = 0;
}

/*
 * description: setter for r value
 * return: none
 * precondition: valid r exists
 * postcondition: set r
*/
void color_rgb::setR(int r) {
    this->r = r;
}

/*
 * description: getter for r value
 * return: int
 * precondition: none
 * postcondition: return r value
*/
int color_rgb::getR() {
    return r;
}

/*
 * description: setter for g value
 * return: none
 * precondition: valid g exists
 * postcondition: set g
*/
void color_rgb::setG(int g) {
    this->g = g;
}

/*
 * description: getter for g value
 * return: int
 * precondition: none
 * postcondition: return g value
*/
int color_rgb::getG() {
    return g;
}

/*
 * description: setter for b value
 * return: none
 * precondition: valid b exists
 * postcondition: set b
*/
void color_rgb::setB(int b) {
    this->b = b;
}

/*
 * description: getter for b value
 * return: int
 * precondition: none
 * postcondition: return b value
*/
int color_rgb::getB() {
    return b;
}

/*
 * description: overloaded assignment operator
 *      for color_rgb class
 * return: none
 * precondition: valid c exists
 * postcondition: sets r, g, b, values
*/
void color_rgb::operator=(const color_rgb& c){
    r = c.r;
    g = c.g;
    b = c.b;
}