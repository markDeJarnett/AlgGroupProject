/*
* Author: Michelle Aurora, Zee Dugar, Mark DeJarnett,
*         Elisa Gonzalez, Elissa Skinner
* Assignment Title: Final Project
* Assignment Description: This program implements
*         the closet pair functions. The  two ways are
*         brute force and divide & conquer.
*  Due Date: 5/5/2019
* Date Created: 3/18/2019
* Date Last Modified: 3/24/2019
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <float.h>
#include <cstdlib>

#include "line.h"
#include "point.h"

using namespace std;

/*
* description: calculate the distance between two points
*              using the Euclidean formula (d = sqrt[(x2-x1)^2 + (y2-y1)^2])
* return: double
* precondition: the points p1 and p2 exist
* postcondition: return the distance between the points
*/
double calcDistance(point p1, point p2){
    return sqrt(pow(p1.getX() - p2.getX(), 2) + pow(p1.getY() - p2.getY(), 2));
}

/*
* description: the points in rectangular shape (easier to see than small dots)
* return: none
* precondition: g exists and point p is valid
* postcondition: plot the rectangular point
*/
void drawPoint(SDL_Plotter &g, point p){
    for(int x = p.getX() - 2; x < p.getX() + 2; x++){
        for(int y = p.getY() - 2; y < p.getY() + 2; y++){
            if(x > 0 && x < g.getCol() && y > 0 && y > 0){
                int yVal = y;
                g.plotPixel(x, yVal, p.getColor().getR(), p.getColor().getG(),
                            p.getColor().getB());               // changed yVal to y
            }
        }
    }
}

/*
* description: plot points which are in the vector set of points
* return: none
* precondition: g exists and set of points is valid
* postcondition: plots the points
*/
void plotPoints(SDL_Plotter &g, vector<point> setOfPoints){
    for(int i = 0; i <setOfPoints.size(); i++){
        if(setOfPoints[i].getX() > 0 && setOfPoints[i].getX() < g.getCol() &&
           setOfPoints[i].getY() > 0 && setOfPoints[i].getY() > 0){
            drawPoint(g, setOfPoints[i]);
        }
    }
}

/*
* description: find the closest pair of points in a given set
*              using the brute force method.
*
*             brute force goes through all points to find
*             all possible distances.
*
*             run time: 0(n^2)
* return: double
* precondition: g exists and the set contains valid points and
*               contains at a minimum 2 unique points.
* postcondition: return the closest pair of points
*/
double bruteForceClosestPair(SDL_Plotter &g, vector<point> setOfPoints){
    //plot the points
    plotPoints(g, setOfPoints);
    g.update();

    //to check if duplicate
    bool duplicatePoint = false;

    //initialize distance (will be overwritten, DBL_MAX is temp)
    double minDistance = DBL_MAX;

    //if distance is updated
    bool updateDistance = false;

    //go through all point in the set
    for(int i = 0; i < setOfPoints.size(); i++){
        //initialize the color for the point
        color_rgb color(57, 226, 198);

        //the current point its checking is light blue
        setOfPoints[i].setColor(color);
        drawPoint(g, setOfPoints[i]);
        g.update();

        //freeze so it doesn't go too fast
        g.Sleep(300);

        //go through next adjacent point
        for(int j = i + 1; j < setOfPoints.size(); j++){

            //check for duplicates
            if(setOfPoints[i].getX() != setOfPoints[j].getX() ||
               setOfPoints[i].getY() != setOfPoints[j].getY()){

                //if not duplicate, then calculate the distance between the points
                if(!duplicatePoint){
                    minDistance = calcDistance(setOfPoints[i], setOfPoints[j]);
                    duplicatePoint = true;
                    updateDistance = true;
                }

                //if distance is less than current min distance then update min distance
                if(calcDistance(setOfPoints[i], setOfPoints[j]) < minDistance) {
                    //calculate new min distance
                    minDistance = calcDistance(setOfPoints[i], setOfPoints[j]);
                    updateDistance = true;
                }

                //plot the min distance on the plotter
                if(updateDistance){
                    g.clear();

                    //plot the line
                    plotPoints(g, setOfPoints);

                    //start and end points for the line
                    point start(setOfPoints[i].getX(),
                                setOfPoints[i].getY());
                    point end(setOfPoints[j].getX(),
                              setOfPoints[j].getY());

                    //line for current
                    line currentClosestPair(start, end);

                    //color for the line
                    currentClosestPair.setColor(color);
                    currentClosestPair.draw(g);

                    //change to false to check other point distances
                    updateDistance = false;

                    g.update();

                    //freeze so it doesn't go too fast
                    g.Sleep(300);
                }
            }
        }
        //reset color back to black
        color.setR(0);
        color.setB(0);
        color.setG(0);

        setOfPoints[i].setColor(color);

        drawPoint(g, setOfPoints[i]);
        g.update();

    }
    g.update();
    return minDistance;
}

/*
* description: compare the x values of two points
* return: bool
* precondition: the points p1 and p2 are valid
* postcondition: return if second point x is
*                greater than first point x value
*/
bool compareXValues(point p1, point p2){
    return (p2.getX() > p1.getX());
}

/*
* description: compare the y values of two points
* return: bool
* precondition: the points p1 and p2 are valid
* postcondition: return if second point y is
*                greater than first point y value
*/
bool compareYValues(point p1, point p2){
    return (p2.getY() > p1.getY());
}

/*
* description: find the closest pair of points in a given set
*              using the divide and conquer method.
*
*             divide and conquer splits the set of points in half,
*             checks the half with the current min distance
*             until smallest min distance is found.
*             recursive algorithm.
*
*             run time: 0(n logn)
* return: double
* precondition: the set contains valid points and
*               contains at a minimum 2 unique points.
* postcondition: return the closest pair of points
*/
double divideAndConquerClosestPair(SDL_Plotter &g, vector<point> setOfPoints,
                                   pair<point, point> &closest){
    //if no points in set (empty) then distance is 0
    //also if only 1 point then there's nothing to compare so distance is 0
    if(setOfPoints.size() == 0 ||
       setOfPoints.size() == 1){
        return 0;
    }

    //if there's only two points then compare them (base case)
    if(setOfPoints.size() == 2){
        //store the two points in a pair
        closest.first = point(setOfPoints[0].getX(),
                              setOfPoints[0].getY());
        closest.second = point(setOfPoints[1].getX(),
                               setOfPoints[1].getY());

        return calcDistance(setOfPoints[0], setOfPoints[1]);
    }

        //if set has three points then D&C won't work, since it
        //will split into set of 1 point which will then return 0 (special case)
    else if(setOfPoints.size() == 3){
        //use brute force method to handle this case
        double minDistance = DBL_MAX;
        //if duplicate
        bool duplicatePoint = false;
        //if distance updated
        bool updateDistance = false;

        //brute force method
        for(int i = 0; i < setOfPoints.size(); i++){
            for(int j = i + 1; j < setOfPoints.size(); j++){
                //if duplicated point
                if(setOfPoints[i].getX() != setOfPoints[j].getX() ||
                   setOfPoints[i].getY() != setOfPoints[j].getY()){
                    if(!updateDistance){
                        //if distance has not been updated, then calculate min distance
                        minDistance = calcDistance(setOfPoints[i], setOfPoints[j]);

                        updateDistance = true;
                        duplicatePoint = true;

                        //store the point pair
                        closest.first = point(setOfPoints[i].getX(),
                                              setOfPoints[i].getY());
                        closest.second = point(setOfPoints[j].getX(),
                                               setOfPoints[j].getY());
                    }

                    //current distance is less than min distance then update min distance
                    if(calcDistance(setOfPoints[i], setOfPoints[j]) < minDistance){
                        minDistance = calcDistance(setOfPoints[i], setOfPoints[j]);
                        updateDistance = true;

                        //store point pair
                        closest.first = point(setOfPoints[i].getX(),
                                              setOfPoints[i].getY());
                        closest.second = point(setOfPoints[j].getX(),
                                               setOfPoints[j].getY());
                    }

                    //current closest pair.
                    if(updateDistance){
                        //reset
                        updateDistance = false;
                    }
                }
            }
        }

        return minDistance;
    }

    //sort by x values (least to greatest)
    sort(setOfPoints.begin(), setOfPoints.end(), compareXValues);

    //divide set into two parts
    int median = setOfPoints.size()/2;

    //plot points
    g.clear();
    plotPoints(g, setOfPoints);

    //median line
    point medianStart(setOfPoints[median].getX(), 30);
    point medianEnd(setOfPoints[median].getX(), g.getRow() - 30);

    //draw the median
    line medianArea(medianStart, medianEnd);
    color_rgb color(0,255,0); //green
    medianArea.setColor(color);
    medianArea.draw(g);


    //pair for the left of median points
    pair<point, point> lPoints;
    //pair for the right of median points
    pair<point, point> rPoints;

    //sub sets based on median
    vector<point> halfOne(setOfPoints.begin(), setOfPoints.begin() + median);
    vector<point> halfTwo(setOfPoints.begin() + median, setOfPoints.end());

    //recursively to find distance
    double distanceOfFirstHalf = divideAndConquerClosestPair(g, halfOne, lPoints);
    double distanceOfOtherHalf = divideAndConquerClosestPair(g, halfTwo, rPoints);

    //minimum of the two distances
    double minDistance;

    //set the min distance accordingly based on which half is better
    if(distanceOfFirstHalf < distanceOfOtherHalf){
        closest = lPoints;
        minDistance = distanceOfFirstHalf;
    }
    else{
        closest = rPoints;
        minDistance = distanceOfOtherHalf;
    }

    //draw the points
    g.clear();
    plotPoints(g, setOfPoints);

    //line for the closest pair in first half
    line closestInFirst(lPoints.first, lPoints.second);
    closestInFirst.draw(g);

    //line for the closest pair in second half
    line closestInOther(rPoints.first, rPoints.second);
    closestInOther.draw(g);

    //draw median
    medianArea.draw(g);
    g.update();

    //freeze
    g.Sleep(2000);

    //handle is closest pair seperated by median
    //to hold possible points that could have a min distance but are split
    vector<point> dividedPoints;

    //check if points that are divided into sub sets have a closest pair
    for(int i = 0; i < setOfPoints.size(); i++){

        //check how fair the point is from the median (the x value distance)
        if(abs(setOfPoints[i].getX() - setOfPoints[median].getX()) <= minDistance){
            //if it is less than or equal to the current min distance
            //add it to the set
            dividedPoints.push_back(setOfPoints[i]);
        }
    }

    //the set of median possible points are sorted by y points now
    sort(dividedPoints.begin(), dividedPoints.end(), compareYValues);

    //go through all divided points
    for(int i = 0; i < dividedPoints.size(); i++){
        //compare to adjacent point
        //and if the y value difference is less than or equal to
        //the current min distance then calculate the new
        //min distance
        for(int j = i + 1; j < dividedPoints.size() &&
                           dividedPoints[j].getY() - dividedPoints[i].getY() <= minDistance; j++) {

            if (calcDistance(dividedPoints[i], dividedPoints[j]) < minDistance) {

                minDistance = calcDistance(dividedPoints[i], dividedPoints[j]);

                //store points in pair
                closest.first = point(dividedPoints[i].getX(),
                                      dividedPoints[i].getY());
                closest.second = point(dividedPoints[j].getX(),
                                       dividedPoints[j].getY());
            }
        }
    }

    g.clear();
    plotPoints(g, setOfPoints);

    //closest pair
    line closestPair(closest.first, closest.second);

    point modP1(closestPair.getP1().getX(),
                closestPair.getP1().getY());
    modP1.setColor(color_rgb(255,0,0));

    point modP2(closestPair.getP2().getX(),
                closestPair.getP2().getY());
    modP2.setColor(color_rgb(255,0,0));

    drawPoint(g, modP1);
    drawPoint(g, modP2);

    closestPair.setColor(color_rgb(0,0,255)); //blue
    closestPair.draw(g);

    g.update();

    return minDistance;
}