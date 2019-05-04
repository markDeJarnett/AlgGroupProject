/*
* Author: Michelle Aurora, Zee Dugar, Mark DeJarnett,
*         Elisa Gonzalez, Elissa Skinner
* Assignment Title: Final Project
* Assignment Description: This program runs and shows the visualization of
*         the brute force closest pair and convex hull algorithms
*         and the divide & conquer closest pair and convex hull algorithms.
* Due Date: 5/5/2019
* Date Created: 3/18/2019
* Date Last Modified: 5/4/2019
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <time.h>

#include "closestPair.h"
#include "point.cpp"
#include "line.cpp"
#include "color_rgb.cpp"
#include "convexHull.h"

using namespace std;

//dimensions for sdl plotter
const int ROW_MAX = 500;
const int COL_MAX = 1000;
//for edges so points stay within
const int MARGIN = 25;

int main(int argc, char* argv[]){
    //initialize plotter with dimensions
    SDL_Plotter g(ROW_MAX, COL_MAX);
    g.update();

    //points
    vector<point> setOfPoints;

    //adjust coordinates so points don't pass
    int adjustYAxis = ROW_MAX-(MARGIN+1)*2;
    int adjustXAxis = COL_MAX-(MARGIN+1)*2;

    //while not quit
    while (!g.getQuit()) {
        //based on key entered
        if (g.kbhit()) {
            g.clear();
            setOfPoints.clear();

            srand(time(NULL));
            //randomize the points (30 currently for testing)
            for(int i = 0; i < 50; i++) {
                int maxPtY = (rand() % adjustYAxis) + MARGIN;
                int maxPtX = (rand() % adjustXAxis) + MARGIN;

                //make a random point
                point pt(maxPtX, maxPtY);

                //add to set of points
                setOfPoints.push_back(pt);
            }

            switch (g.getKey()) {
                //brute force closest pair
                case 'C':
                    bruteForceClosestPair(g, setOfPoints);
                    break;

                //divide and conquer closest pair
                case 'P': {
                    pair<point, point> pairOfPoints;
                    divideAndConquerClosestPair(g, setOfPoints, pairOfPoints);
                    break;
                }

                //divide and conquer convex hull
                case 'D': {
                    pair<point, point> pair1;
                    vector<point> temp = divideAndConquerConvexHull(g, setOfPoints);
                    drawConvex(g, temp, setOfPoints);
                    break;
                }

                //brute force convex hull
                case 'H': {
                    vector<point> temp = bruteForceConvexHull(g, setOfPoints);
                    drawConvex(g, temp, setOfPoints);
                }
            }
        }
    }
    return 0;
}