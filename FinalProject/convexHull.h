/*
* Author: Michelle Aurora, Zee Dugar, Mark DeJarnett,
*         Elisa Gonzalez, Elissa Skinner
* Assignment Title: Final Project
* Assignment Description: This program implements
*         the convex hull functions. The  two ways are
*         brute force and divide & conquer.
* Due Date: 4/5/2019
* Date Created: 3/18/2019
* Date Last Modified: 3/22/2019
*/

#ifndef FINALPROJECT_CONVEXHULL_H
#define FINALPROJECT_CONVEXHULL_H

#include <cmath>
#include <vector>
#include <algorithm>

#include "point.h"

/*
 * description: finds the points belonging to the convex hull of a given set
 *      of points using a brute force algorithm
 * return: a vector of points
 * precondition: points contains at least 3 distinct points
 * postcondition: a vector of points containing the points in the convex hull
 *      is returned; the parameter, points, is unchanged after the function call
 *
*/
vector<point> *bruteForceConvexHull(vector<point> setOfPoints);

/*
 * description: get the left most point of set of points
 * return: point
 * precondition: a set of points exists
 * postcondition: returns the left most point
 *
*/
point getLeftMostPoint(vector<point> setOfPoints){
    int leftX = 0;
    int leftY = 0;
    point temp;

    leftX = setOfPoints[0].getX();
    leftY = setOfPoints[0].getY();

    for (int i = 1; i < setOfPoints.size(); i++){
        if (setOfPoints[i].getX() < leftX){
            leftX = setOfPoints[i].getX();
            leftY = setOfPoints[i].getY();
        }
    }

    temp.setX(leftX);
    temp.setY(leftY);

    return temp;
}

/*
 * description: get the right most point of set of points
 * return: point
 * precondition: a set of points exists
 * postcondition: returns the right most point
 *
*/
point getRightMostPoint(vector<point> setOfPoints){
    int rightX = 0;
    int rightY = 0;
    point temp;

    rightX = setOfPoints[0].getX();
    rightY = setOfPoints[0].getY();

    for (int i = 1; i < setOfPoints.size(); i++){
        if (setOfPoints[i].getX() > rightX){
            rightX = setOfPoints[i].getX();
            rightY = setOfPoints[i].getY();
        }
    }

    temp.setX(rightX);
    temp.setY(rightY);

    return temp;
}

/*
* description: compare the y values of two points
* return: bool
* precondition: the points p1 and p2 are valid
* postcondition: return if second point y is
*                greater than first point y value
*/
bool compareY(point p1, point p2){
    return (p2.getY() > p1.getY());
}

/*
 * description:
 * return: point
 * precondition:
 * postcondition:
 *
*/
double getY(line l, int x){
    point p1(l.getP1());
    point p2(l.getP2());
    if (p1.getX() != p2.getX()){
        double m = double((p1.getY() - p2.getY())) / (p1.getX() - p2.getX());
        double b = p1.getY() - (m * p1.getX());
        return x * m + b;
    }

    return INT8_MAX;
}

/*
 * description:
 * return: point
 * precondition:
 * postcondition:
 *
*/
double getX(line l, int y){
    point p1(l.getP1());
    point p2(l.getP2());
    if (p1.getY() != p2.getY() && p1.getX() != p2.getX()){
        double m = double((p1.getY() - p2.getY())) / (p1.getX() - p2.getX());
        double b = p1.getY() - (m * p1.getX());
        return (y - b) / m;
    }else if(p1.getY() != p2.getY() && p1.getX() == p2.getX()){
        return p1.getX();
    }

    return INT8_MAX;
}

/*
 * description: find the convex hull of a set of points by dividing and conquering
 * the points
 * return: vector<point>
 * precondition: a set of points exists
 * postcondition: returns the set of points in the convex hull
 *
*/
vector<point> divideAndConquerConvexHull(SDL_Plotter &g, vector<point> setOfPoints){

    vector<point> convexHull;

    g.clear();
    plotPoints(g, setOfPoints);
    g.update();
    g.Sleep(300);

    // check if multiple points on same line
    bool isLine = true;
    for (int i = 1; i < setOfPoints.size(); i++) {
        if (setOfPoints[i].getX() != setOfPoints[i-1].getX()) {
            isLine = false;
        }
    }

    // if < 3 points, connect
    if (setOfPoints.size() <= 3 || isLine){
        return setOfPoints;
    }else{

        // left & right groups
        vector<point> leftGroup;
        vector<point> rightGroup;

        // left & right side of convex hull
        vector<point> leftEdge;
        vector<point> rightEdge;

        // find the left & right most point
        point leftMostPoint = getLeftMostPoint(setOfPoints);
        point rightMostPoint = getRightMostPoint(setOfPoints);

        // find halfway point
        point halfwayPoint;
        halfwayPoint.setX(((rightMostPoint.getX() - leftMostPoint.getX()) / 2) + leftMostPoint.getX());

        line l = line({halfwayPoint.getX(), 0}, {halfwayPoint.getX(), ROW_MAXIMUM});
        l.draw(g);
        g.update();
        g.Sleep(300);

        // dividing points in half
        for (int i = 0; i < setOfPoints.size(); i++){
            if (setOfPoints[i].getX() <= halfwayPoint.getX()){
                leftGroup.push_back(setOfPoints[i]);
            }else if(setOfPoints[i].getX() > halfwayPoint.getX()){
                rightGroup.push_back(setOfPoints[i]);
            }
        }

        // left & right side of convex hull
        leftEdge = divideAndConquerConvexHull(g, leftGroup);
        rightEdge = divideAndConquerConvexHull(g, rightGroup);

        g.clear();
        plotPoints(g, leftEdge);
        plotPoints(g, rightEdge);
        l.draw(g);
        g.update();
        g.Sleep(300);


        // sort left & right edge by y value
        sort(leftEdge.begin(), leftEdge.end(), compareY);
        sort(rightEdge.begin(), rightEdge.end(), compareY);

        bool isFound = false;
        int leftCount  = 0;
        int rightCount = 0;
        line line1;

        while (!isFound){
            isFound = true;
            line1 = line(leftEdge.at(leftCount), rightEdge.at(rightCount));

            if (leftCount+1 < leftEdge.size()) {
                for (int j = leftCount + 1; j < leftEdge.size() && isFound; j++) {
                    double tempY = getY(line1, leftEdge.at(leftCount + 1).getX());
                    if (tempY > leftEdge.at(leftCount + 1).getY()) {
                        isFound = false;
                        leftCount++;
                    }
                }
            }
            if (rightCount+1 < rightEdge.size()) {
                for (int j = rightCount + 1; j < rightEdge.size() && isFound; j++) {
                    double temp1Y = getY(line1, rightEdge.at(j).getX());
                    if (temp1Y > rightEdge.at(j).getY()) {
                        isFound = false;
                        rightCount = j;
                    }
                }
            }
            if (isFound) {
                for (int j = leftEdge.size()-1; j >= 0 && isFound; j--) {
                    double tempY = getY(line1, leftEdge.at(j).getX());
                    if ((int)round(tempY) > leftEdge.at(j).getY()) {
                        isFound = false;
                        leftCount = j;
                    }
                }
                for (int j = rightEdge.size()-1; j >= 0 && isFound; j--) {
                    double temp1Y = getY(line1, rightEdge.at(j).getX());
                    if ((int)round(temp1Y) > rightEdge.at(j).getY()) {
                        isFound = false;
                        rightCount = j;
                    }
                }
                if (!isFound) {
                    int leftCount = 0;
                    int rightCount = 1;
                }
            }
        }
        line1.draw(g);
        g.update();

        line line5;
        isFound = false;
        int lCount = leftEdge.size()-1;
        int rCount = rightEdge.size()-1;
        while(!isFound){
            isFound = true;
            line5 = line(leftEdge.at(lCount), rightEdge.at(rCount));

            if (lCount-1 >= 0) {
                for (int j = lCount-1; j >= 0 && isFound; j--) {
                    double tempY = getY(line5, leftEdge.at(j).getX());
                    if (tempY < leftEdge.at(j).getY()) {
                        isFound = false;
                        lCount = j;
                    }
                }
            }
            if (rCount-1 >= 0 && isFound) {
                for (int j = rCount-1; j >= 0 && isFound; j--) {
                    double temp1Y = getY(line5, rightEdge.at(j).getX());
                    if (temp1Y < rightEdge.at(j).getY()) {
                        isFound = false;
                        rCount = j;
                    }
                }
            }
            if (isFound) {
                for (int j = leftEdge.size()-1; j >= 0 && isFound; j--) {
                    double tempY = getY(line5, leftEdge.at(j).getX());
                    if ((int)round(tempY) < leftEdge.at(j).getY()) {
                        isFound = false;
                        lCount = j;
                    }
                }
                for (int j = rightEdge.size()-1; j >= 0 && isFound; j--) {
                    double temp1Y = getY(line5, rightEdge.at(j).getX());
                    if ((int)round(temp1Y) < rightEdge.at(j).getY()) {
                        isFound = false;
                        rCount = j;
                    }
                }
                if (!isFound) {
                    int lCount = leftEdge.size()-1;
                    int rCount = rightEdge.size()-2;
                }
            }
        }
        line5.draw(g);
        g.update();
        g.Sleep(500);

        line line2(leftEdge.at(leftCount), leftEdge.at(lCount));
        line line3(rightEdge.at(rightCount), rightEdge.at(rCount));

        for (int i = 0; i < leftEdge.size(); i++){
            int tempX = (int)round(getX(line2, leftEdge.at(i).getY()));

            if ((tempX > leftEdge.at(i).getX()
                    || ((int)round(getY(line2, leftEdge.at(i).getX())) > leftEdge.at(i).getY()
                        && (int)round(getY(line3, leftEdge.at(i).getX())) > leftEdge.at(i).getY()
                        && leftEdge.at(i).getY() < line2.getP1().getY()
                        && leftEdge.at(i).getY() < line2.getP2().getY()
                        && leftEdge.at(i).getY() < line3.getP1().getY()
                        && leftEdge.at(i).getY() < line3.getP2().getY())
                    || ((int)round(getY(line2, leftEdge.at(i).getX())) < leftEdge.at(i).getY()
                        && (int)round(getY(line3, leftEdge.at(i).getX())) < leftEdge.at(i).getY()
                        && leftEdge.at(i).getY() > line2.getP1().getY()
                        && leftEdge.at(i).getY() > line2.getP2().getY()
                        && leftEdge.at(i).getY() < line3.getP1().getY()
                        && leftEdge.at(i).getY() < line3.getP2().getY()))
                    && leftCount != lCount){
                convexHull.push_back(leftEdge.at(i));
            }
        }

        for (int i = 0; i < rightEdge.size(); i++){
            int temp1X = (int)round(getX(line3, rightEdge.at(i).getY()));

            int a = (int)round(getY(line2, rightEdge.at(i).getX()));
            int b = (int)round(getY(line3, rightEdge.at(i).getX()));
            int c = (int)round(getY(line2, rightEdge.at(i).getX()));
            int d = (int)round(getY(line3, rightEdge.at(i).getX()));

            if ((temp1X < rightEdge.at(i).getX()
                || ((int)round(getY(line2, rightEdge.at(i).getX())) > rightEdge.at(i).getY()
                    && (int)round(getY(line3, rightEdge.at(i).getX())) > rightEdge.at(i).getY()
                    && rightEdge.at(i).getY() < line2.getP1().getY()
                    && rightEdge.at(i).getY() < line2.getP2().getY()
                    && rightEdge.at(i).getY() < line3.getP1().getY()
                    && rightEdge.at(i).getY() < line3.getP2().getY())
                || ((int)round(getY(line2, rightEdge.at(i).getX())) < rightEdge.at(i).getY()
                    && (int)round(getY(line3, rightEdge.at(i).getX())) < rightEdge.at(i).getY()
                    && rightEdge.at(i).getY() > line2.getP1().getY()
                    && rightEdge.at(i).getY() > line2.getP2().getY()
                    && rightEdge.at(i).getY() > line3.getP1().getY()
                    && rightEdge.at(i).getY() > line3.getP2().getY()))
                && rightCount != rCount){
                convexHull.push_back(rightEdge.at(i));
            }
        }

        convexHull.push_back(leftEdge.at(leftCount));

        if (leftCount != lCount)
            convexHull.push_back(leftEdge.at(lCount));

        convexHull.push_back(rightEdge.at(rightCount));

        if (rightCount != rCount)
            convexHull.push_back(rightEdge.at(rCount));

        // draws the points of convex hull
        g.clear();
        plotPoints(g, convexHull);
        g.update();
        g.Sleep(300);

        return convexHull;

    }

}


/*
 * description: determine if two points have the same x and y values
 * return: bool
 * precondition: points p1 and p2 exist and are valid
 * postcondition: returns if the x and y values of the two points are the same
 *
*/
bool operator==(point p1, point p2){
    return (p1.getY() == p2.getY() && p1.getX() == p2.getX());
}

/*
 * description: draws the convex hull, first left side then right side, then top and bottom
 * return: nothing
 * precondition: convex hull is found
 * postcondition: convex hull is drawn
 *
*/
void drawConvex(SDL_Plotter &g, vector<point> convexHull, vector<point> allPoints){
    vector<point> leftConvexHull;
    vector<point> rightConvexHull;

    // find the left & right most point
    point leftMostPoint = getLeftMostPoint(convexHull);
    point rightMostPoint = getRightMostPoint(convexHull);

    // find halfway point
    sort(convexHull.begin(), convexHull.end(), compareYValues);
    line halfwayLine(convexHull[0], convexHull[convexHull.size()-1]);

    // dividing points in half
    for (int i = 0; i < convexHull.size(); i++){
        if (convexHull[i].getX() < getX(halfwayLine, convexHull[i].getY())){
            leftConvexHull.push_back(convexHull[i]);
        }else if(convexHull[i].getX() >= getX(halfwayLine, convexHull[i].getY())){
            rightConvexHull.push_back(convexHull[i]);
        }
    }

    // sort left and right side by y
    sort(leftConvexHull.begin(), leftConvexHull.end(), compareYValues);

    for (int i = 1; i < leftConvexHull.size()-1; i++) {
        if (leftConvexHull[i].getX() > leftConvexHull[i-1].getX() && leftConvexHull[i].getX() > leftConvexHull[i+1].getX()) {
            rightConvexHull.push_back(leftConvexHull[i]);
            leftConvexHull[i].setY(-1);
        }
    }

    sort(rightConvexHull.begin(), rightConvexHull.end(), compareYValues);

    for (int i = 1; i < rightConvexHull.size()-1; i++) {
        if (rightConvexHull[i].getX() < rightConvexHull[i-1].getX() && rightConvexHull[i].getX() < rightConvexHull[i+1].getX()) {
            leftConvexHull.push_back(rightConvexHull[i]);
            rightConvexHull[i].setY(-1);
        }
    }

    sort(leftConvexHull.begin(), leftConvexHull.end(), compareYValues);
    sort(rightConvexHull.begin(), rightConvexHull.end(), compareYValues);

    int lStart = 0;
    int rStart = 0;


    // draw the left side of the convex
    for (int k = 0; k < leftConvexHull.size(); k++){

        if (k != leftConvexHull.size()-1 && leftConvexHull[k].getY() != -1) {
            line line4(leftConvexHull[k], leftConvexHull[k + 1]);
            line4.setColor(color_rgb(182, 66, 244));
            line4.draw(g);
            g.update();
        } else if (leftConvexHull[k].getY() == -1) {
            lStart = k + 1;
        }
    }

    // draw the right side of the convex
    for (int k = 0; k < rightConvexHull.size(); k++){

        if (k != rightConvexHull.size()-1 && rightConvexHull[k].getY() != -1){
            line line4(rightConvexHull[k], rightConvexHull[k + 1]);
            line4.setColor(color_rgb(182, 66, 244));
            line4.draw(g);
            g.update();
        } else if (rightConvexHull[k].getY() == -1) {
            rStart = k + 1;
        }
    }

    // connect the top part of the convex
    line topConvex(leftConvexHull[lStart], rightConvexHull[rStart]);
    topConvex.setColor(color_rgb(182, 66, 244));
    topConvex.draw(g);
    g.update();
    //g.Sleep(1000);

    // connect the bottom part of the convex
    line bottomConvex(leftConvexHull[leftConvexHull.size()-1], rightConvexHull[rightConvexHull.size()-1]);
    bottomConvex.setColor(color_rgb(182, 66, 244));
    bottomConvex.draw(g);
    g.update();
    //g.Sleep(1000);

    // draw the rest of the points
    plotPoints(g, allPoints);
    g.update();
    //g.Sleep(1000);
}



#endif //FINALPROJECT_CONVEXHULL_H
