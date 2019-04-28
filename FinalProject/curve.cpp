/*
* Author: Michelle Aurora, Zee Dugar, Mark DeJarnett,
*         Elisa Gonzalez, Elissa Skinner
* Assignment Title: Final Project
* Assignment Description: This program implements
*         the curve functions.
* Due Date: 4/5/2019
* Date Created: 1/17/2019
* Date Last Modified: 1/28/2019
*/

#include "curve.h"
#include <cmath>

//constants (dimensions)
const int ROW_MAXIMUM = 500;
const int COL_MAXIMUM = 1000;

//margin for graph (axis)
const int MARG = 50;

/*
 * description: curve default constructor
 * return: none
 * precondition: none
 * postcondition: set sameScale value to true
*/
curve::curve() {
    //set sameScale to true
    sameScale = true;
}

/*
 * description: curve destructor
 * return: none
 * precondition: none
 * postcondition: set sameScale value to false
*/
curve::~curve(){
    sameScale = false;
}

/*
 * description: displays curve
 * return: none
 * precondition: valid out exists
 * postcondition: prints
*/
void curve::display(Data_t data, ostream& out){
    out << "curve" << endl;
}

/*
 * description: plots curve based on data
 * return: none
 * precondition: valid g exists
 * postcondition: plots curve onto SDL_Plotter
*/
void curve::draw(Data_t data, SDL_Plotter& g){
    int maxX = 0;
    int maxY = 0;
    int dataSize = data.size();

    //scales for x & y depending
    double scaleFactorX;
    double scaleFactorY;

    int startX;
    int startY;
    int endX;
    int endY;

    line l;

    //line or curve for each data element
    for(int i = 0; i < dataSize; i++){
        int numOfPoints = data[i].size();

        double numX = 0;
        double numY = 0;

        for(int j = 0; j < numOfPoints; j++){
            //scale
            //fix data according to the scale

            //if same scale then factor = 1
            if(sameScale){
                scaleFactorY = 1;
                scaleFactorX = 1;
            }

                //not same scale
            else {
                //exponential i = 0 in dataset (driver)
                if(i == 0){
                    scaleFactorY = 1;
                    scaleFactorY = 150;

                }
                //linear function
                if(i == 1){
                    scaleFactorY = 1;
                    scaleFactorX = COL_MAXIMUM/ROW_MAXIMUM;
                }
                //squared
                if(i == 2){
                    scaleFactorY = 1;
                    scaleFactorX = COL_MAXIMUM/sqrt(ROW_MAXIMUM);
                }
                //cubed
                if(i == 3){
                    scaleFactorY = 1;
                    scaleFactorX = COL_MAXIMUM/cbrt(ROW_MAXIMUM);
                }
                //logarithmic function
                if(i == 4){
                    scaleFactorY = 40;
                    scaleFactorX = 1.0/40.0;
                }
            }

            //points depending on scale factor
            startX = data[i][j].first * scaleFactorX + MARG;
            startY = ROW_MAXIMUM - MARG - (data[i][j].second * scaleFactorY);

            endX = data[i][j+1].first * scaleFactorX + MARG;
            endY = ROW_MAXIMUM - MARG - (data[i][j+1].second * scaleFactorY);

            //points
            point p1(startX, startY);
            point p2(endX, endY);

            //line
            l.setP1(p1);
            l.setP2(p2);

            //check if good points
            //draw line if good
            if(goodPoints(l, MARG, g)){
                l.draw(g);
            }

            //x points in data
            //check to find max
            if(data[i][j].first > maxX &&
               data[i][j].first < COL_MAXIMUM-MARG){
                numX = data[i][j].first;
            }

            //y points in data
            //check to find max
            if(data[i][j].second > maxY &&
               data[i][j].second < ROW_MAXIMUM-MARG){
                numY = data[i][j].second;
            }
        }

        //change color
        l.nextColor();

        //set to max of points
        //x points in curve
        if(numX > maxX){
            maxX = numX;
        }
        //y points in curve
        if(numY > maxY) {
            maxY = numY;
        }
    }
    //x and y axis - plotAxis (which will plot tick marks)
    plotAxis(MARG, maxX, maxY, g);
}

/*
 * description: plots x and y axis
 * return: none
 * precondition: valid margin, maxX, maxY, and g exists
 * postcondition: plots both axis onto SDL_Plotter
*/
void curve::plotAxis(int margin, int maxX, int maxY, SDL_Plotter& g) {
    //start points of x & y axis
    point axisXStart (margin, maxY);
    point axisYStart (margin, maxY);

    //end points of x & y axis
    point axisXEnd (maxX, maxY);
    point axisYEnd (margin-1, margin);

    //lines for the 2 axis
    line axisX(axisXStart, axisXEnd);
    line axisY(axisYStart, axisYEnd);

    //draw x & y axis
    axisX.draw(g);
    axisY.draw(g);

    //update plotter
    g.update();

    //tick marks for the axis
    plotTickMarks(MARG, maxX, maxY, g);
}

/*
 * description: plots x and y axis tick marks
 * return: none
 * precondition: valid margin, maxX, maxY, and g exists
 * postcondition: plots tick marks onto SDL_Plotter
*/
void curve::plotTickMarks(int margin, int maxX, int maxY, SDL_Plotter& g){
    int currentPos = 0;
    int tickSize = 15;

    currentPos = margin;
    //y axis tick marks
    while(currentPos <= maxY){
        //points for tick marks
        point startTick(margin - tickSize, currentPos);
        point endTick(margin + tickSize, currentPos);

        //line
        line tickLineY(startTick, endTick);

        tickLineY.draw(g);

        //move position
        currentPos += (margin-10);
    }

    //x axis tick marks
    currentPos = margin*2-10;
    while(currentPos <= maxX){
        //point for tick marks
        point startTickX(currentPos+margin, tickSize + maxY);
        point endTickX(currentPos-1+margin, maxY - tickSize);

        //line
        line tickLineX(startTickX, endTickX);

        tickLineX.draw(g);

        //move position
        currentPos += (margin*2-10);
    }
    g.update();
}

/*
 * description: determine if point is valid (non negative & within range)
 * return: bool
 * precondition: valid margin, a, and g exists
 * postcondition: returns if point is good
*/
bool curve::goodPoints(line a, int margin, SDL_Plotter &g) {
    bool flag = true;

    //points of the line
    int startX = a.getP1().getX();
    int startY = a.getP1().getY();
    int endX = a.getP2().getX();
    int endY = a.getP2().getY();

    //check if startX, startY are good
    if(startX < margin || startX >  (COL_MAXIMUM-margin) ||
       startY < margin || startY> (ROW_MAXIMUM-margin)){
        flag = false;
    }

    //check if endX, endX are good
    if(endX < margin || endX >  (COL_MAXIMUM-margin) ||
       endY < margin || endY > (ROW_MAXIMUM-margin)){
        flag = false;
    }
    return flag;
}