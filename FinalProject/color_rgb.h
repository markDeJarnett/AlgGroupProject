/*
* Author: Michelle Aurora
* Assignment Title: Program 0
* Assignment Description: This program contains
*   the color_rgb functions.
* Due Date: 1/28/109
* Date Created: 1/17/2019
* Date Last Modified: 1/25/2019
 */

#ifndef FINALPROJECT_COLOR_RGB_H
#define FINALPROJECT_COLOR_RGB_H

class color_rgb {
public:
    color_rgb();
    color_rgb(int r, int g, int b);
    virtual ~color_rgb();
    int getR();
    int getG();
    int getB();

    void setR(int r);
    void setG(int g);
    void setB(int b);

    void operator=(const color_rgb& c);

private:
    int r,g,b;
};

#endif //FINALPROJECT_COLOR_RGB_H
