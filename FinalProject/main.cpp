/*
* Author: Michelle Aurora, Zee Dugar, Mark DeJarnett,
*         Elisa Gonzalez, Elissa Skinner
* Assignment Title: Final Project
* Assignment Description: This program runs and shows the visualization of
*         the brute force closest pair and convex hull algorithms
*         and the divide & conquer closest pair and convex hull algorithms.
* Due Date: 4/5/2019
* Date Created: 3/18/2019
* Date Last Modified: 3/28/2019
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <time.h>

#include "closestPair.h"
#include "point.cpp"
#include "line.cpp"
#include "curve.cpp"
#include "color_rgb.cpp"
#include "convexHull.h"

/*TO DO
 * - divide and conquer convex hull
 * - graphics
 *      * need to slow down the bf closest pir graphics (press key C)
 *
 *
 * DONE
 *  - brute force closest pair
 *  - div and conquer closest pair
 *  - brute force convex hull
 *
 *  - github repo set up
 */

using namespace std;

//dimensions for sdl plotter
const int ROW_MAX = 500;
const int COL_MAX = 1000;
//for axis
const int MARGIN = 25;

//const int ROW_MAX = 10;
//const int COL_MAX = 10;
//const int MARGIN = 1;

int main(int argc, char* argv[]){
    //initialize plotter with dimensions
    SDL_Plotter g(ROW_MAX, COL_MAX);
    g.update();

    //points
    vector<point> setOfPoints;

    //adjust the coordinates of the axes based on the margin
    int adjustYAxis = ROW_MAX-(MARGIN+1)*2;
    int adjustXAxis = COL_MAX-(MARGIN+1)*2;

    cout << adjustXAxis << " " << adjustYAxis << endl;

    while (!g.getQuit()) {
        //plot axes on screen
        //crv.plotAxis(MARGIN, adjustXAxis, adjustYAxis, g);

        if (g.kbhit()) {
            g.clear();
            setOfPoints.clear();

            srand(time(NULL));
            //randomize the points (30 currently for testing)
            for(int i = 0; i < 50; i++){
                int maxPtY = (rand() % adjustYAxis) + MARGIN;
                int maxPtX = (rand() % adjustXAxis) + MARGIN;

                //make a random point
                point pt(maxPtX, maxPtY);

                //add to set of points
                setOfPoints.push_back(pt);
            }

// another divot
//            point p0(56,468);
//            setOfPoints.push_back(p0);
//            point p1(322,156);
//            setOfPoints.push_back(p1);
//            point p2(179,377);
//            setOfPoints.push_back(p2);
//            point p3(162,43);
//            setOfPoints.push_back(p3);
//            point p4(654,148);
//            setOfPoints.push_back(p4);
//            point p5(198,135);
//            setOfPoints.push_back(p5);
//            point p8(455,226);
//            setOfPoints.push_back(p8);
//            point p6(659,321);
//            setOfPoints.push_back(p6);
//            point p9(469,339);
//            setOfPoints.push_back(p9);
//            point p10(26,155);
//            setOfPoints.push_back(p10);

// smaller test case with little divot that was fixed...fairly easily
//            point p0(724,327);
//            setOfPoints.push_back(p0);
//            point p1(873,126);
//            setOfPoints.push_back(p1);
//            point p2(532,29);
//            setOfPoints.push_back(p2);
//            point p3(627,251);
//            setOfPoints.push_back(p3);
//            point p4(337,226);
//            setOfPoints.push_back(p4);
//            point p5(30,456);
//            setOfPoints.push_back(p5);
//            point p8(299,87);
//            setOfPoints.push_back(p8);
//            point p6(788,52);
//            setOfPoints.push_back(p6);
//            point p9(142,420);
//            setOfPoints.push_back(p9);
//            point p10(439,265);
//            setOfPoints.push_back(p10);

// weird upward breaking one that causing me tears
//            point p1(260,106);
//            setOfPoints.push_back(p1);
//            point p2(425,46);
//            setOfPoints.push_back(p2);
//            point p3(222,64);
//            setOfPoints.push_back(p3);
//            point p4(906,90);
//            setOfPoints.push_back(p4);
//            point p5(258,184);
//            setOfPoints.push_back(p5);
//            point p8(636,200);
//            setOfPoints.push_back(p8);
//            point p6(349,91);
//            setOfPoints.push_back(p6);
//            point p9(973,416);
//            setOfPoints.push_back(p9);
//            point p10(405,429);
//            setOfPoints.push_back(p10);
//            point p11(642,167);
//            setOfPoints.push_back(p11);
//            point p12(784,38);
//            setOfPoints.push_back(p12);
//            point p112(26,124);
//            setOfPoints.push_back(p112);
//            point p102(54,350);
//            setOfPoints.push_back(p102);
//            point p113(895,98);
//            setOfPoints.push_back(p113);
//            point p103(926,166);
//            setOfPoints.push_back(p103);
//            point p121(942,394);
//            setOfPoints.push_back(p121);
//            point p1121(95,59);
//            setOfPoints.push_back(p1121);
//            point p1021(170,398);
//            setOfPoints.push_back(p1021);
//            point p1131(786,46);
//            setOfPoints.push_back(p1131);
//            point p1031(574,455);
//            setOfPoints.push_back(p1031);



            switch (g.getKey()) {
                case 'C':
                    bruteForceClosestPair(g, setOfPoints);
                    break;

                case 'P': {
                    pair<point, point> pairOfPoints;
                    divideAndConquerClosestPair(g, setOfPoints, pairOfPoints);
                    break;
                }

                case 'D': {
//                    for (int i = 0; i < setOfPoints.size(); i++) {
//                        cout << setOfPoints[i].getX() << ',' << setOfPoints[i].getY() << endl;
//                    }
                    pair<point, point> pair1;
                    vector<point> temp = divideAndConquerConvexHull(g, setOfPoints);
                    drawConvex(g, temp, setOfPoints);
                    cout << endl;
//                    for (int i = 0; i < temp.size(); i++) {
//                        cout << temp[i].getX() << ',' << temp[i].getY() << endl;
//                    }
                    break;
                }

                case 'H': {
                    vector<point> temp = bruteForceConvexHull(g, setOfPoints);
                    drawConvex(g, temp, setOfPoints);
                }
            }
        }
    }

    return 0;
}
