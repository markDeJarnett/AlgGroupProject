/*
* Author: Michelle Aurora, Zee Dugar, Mark DeJarnett,
*         Elisa Gonzalez, Elissa Skinner
* Assignment Title: Final Project
* Assignment Description: This program implements
*         the line functions.
* Due Date: 4/5/2019
* Date Created: 1/17/2019
* Date Last Modified: 1/28/2019
*/

#include "line.h"

//how many different colors there are
const int NUMOFCOLORS = 10;

/*
 * description: line default constructor
 * return: none
 * precondition: none
 * postcondition: set the p1, p2, and color values
*/
line::line(){
    p1 = point();
    p2 = point();

    //color is black
    color = color_rgb(0, 0, 0);

    currentColor = 0;
    nextColor();
}

/*
 * description: line constructor
 * return: none
 * precondition: none
 * postcondition: set the p1, p2, and color values
*/
line::line(point p1, point p2) {
    this->p1 = p1;
    this->p2 = p2;

    color = color_rgb(0, 0, 0);

    currentColor = 0;
    nextColor();
}

/*
 * description: line destructor
 * return: none
 * precondition: none
 * postcondition: set all values to 0
*/
line::~line() {
    //reset points
    p1.setX(0);
    p1.setY(0);
    p2.setX(0);
    p2.setY(0);

    color = color_rgb(0, 0, 0);

    currentColor = 0;
}

/*
 * description: setter for p1 value
 * return: none
 * precondition: valid p exists
 * postcondition: set p1
*/
void line::setP1(point p){
    p1 = p;
}

/*
 * description: setter for p2 value
 * return: none
 * precondition: valid p exists
 * postcondition: set p2
*/
void line::setP2(point p){
    p2 = p;
}

/*
 * description: increment to next color
 * return: none
 * precondition: none
 * postcondition: increment current color
*/
void line::nextColor(){
    // These are all the colors curves can get plotted in.
    color_rgb colors[NUMOFCOLORS] = { color_rgb(0,0,0),
                                      color_rgb(255,0,0),
                                      color_rgb(0,0,255),
                                      color_rgb(0, 255, 0),
                                      color_rgb(236,255,102),
                                      color_rgb(52,213,100),
                                      color_rgb(111,52,113),
                                      color_rgb(213,117,52),
                                      color_rgb(213, 52, 208),
                                      color_rgb(52, 213, 213)
                                    };
    //change color (go through above colors
    currentColor = currentColor % NUMOFCOLORS;

    //update color variable
    color = colors[currentColor];
}

/*
 * description: reset color
 * return: none
 * precondition: none
 * postcondition: value of color set to 0
*/
void line::resetColor(){
    currentColor = 0;
}

/*
 * description: displays the coordinates (x1, y1) (x2, y2) of the line
 * return: none
 * precondition: valid out exists
 * postcondition: prints
*/
void line::display(ostream& out){
    //Line: p1->p2 - (x1, y1) -> (x2, y2)
    out << "Line: p1 -> p2 - (" <<
        p1.getX() << ", " << p1.getY() << ") -> (" <<
        p2.getX() << ", " << p2.getY() << ")" << endl;
}

/*
 * description: plots points for the line
 * return: none
 * precondition: valid g exists
 * postcondition: plots line onto SDL_Plotter
*/
void line::draw(SDL_Plotter& g){
    double slopeM, interB;
    int y;
    //y = mx+ b - line equation

    //for small intervals of points
    double incrementBy = 0.001;

    if(slope(slopeM)) {
        intercept(interB);
        if(p1.getX() < p2.getX()) {
            for(double x = p1.getX(); x <= p2.getX(); x += incrementBy) {
                y = slopeM * x + interB;
                g.plotPixel(x, y, color.getR(), color.getG(), color.getB());
            }
        }
        else {
            for(double x2 = p1.getX(); x2 >= p2.getX(); x2 -= incrementBy) {
                y = slopeM * x2 + interB;
                g.plotPixel(x2, y, color.getR(), color.getG(), color.getB());
            }
        }
    }
    else {
//        if(p1.getY() > p2.getY()) {
//            incrementBy = -1;
//        }
//        for(int y = p1.getY(); p1.getY() != p2.getY(); y += incrementBy) {
//            g.plotPixel(p1.getX(), y, color.getR(), color.getG(), color.getB());
//        }

        for(double y = min(p1.getY(), p2.getY()); y < max(p1.getY(), p2.getY()); y += incrementBy) {
            g.plotPixel(p1.getX(), y, color.getR(), color.getG(), color.getB());
        }
    }

    g.update();
}

/*
 * description: determine if line has slope
 * return: bool
 * precondition: valid m exists
 * postcondition: return if slope exists
*/
bool line::slope(double& m){
    bool isSlope = false;

    isSlope = (p1.getX() != p2.getX());

    if(isSlope){
        m = double(p1.getY() - p2.getY())/(p1.getX() - p2.getX());
    }
    return isSlope;
}

/*
 * description: determine if line has intercept
 * return: bool
 * precondition: valid b exists
 * postcondition: return if intercept exists
*/
bool line::intercept(double& b) {
    bool isIntercept = false;
    double slopeM;

    isIntercept = slope(slopeM);

    if (isIntercept) {
        b = p1.getY() - (slopeM * p1.getX());
    }
    return isIntercept;
}

