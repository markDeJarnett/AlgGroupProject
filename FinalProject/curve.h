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

#ifndef FINALPROJECT_CURVE_H
#define FINALPROJECT_CURVE_H

#include <iostream>
#include <vector>

#include "line.h"

using namespace std;

typedef vector<pair<int,long double>> DataSet_t;
typedef vector<DataSet_t> Data_t;

class curve {
public:
    curve();
    virtual ~curve();
    void display(Data_t data, ostream&);
    void draw(Data_t data, SDL_Plotter&);
    bool getSameScale(){ return sameScale;}
    void setSameScale(bool t){sameScale = t;}

private:
    void plotAxis(int margin, int maxX, int maxY, SDL_Plotter& g);
    void plotTickMarks(int margin, int maxX, int maxY, SDL_Plotter& g);
    bool goodPoints(line a, int margin, SDL_Plotter& g);
    bool sameScale;

};

#endif //FINALPROJECT_CURVE_H
