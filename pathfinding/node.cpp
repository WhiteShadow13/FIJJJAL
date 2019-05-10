#include <math.h>

#include "node.h"
#include "struct.h"

Node::Node(const loc_t &loc, int g, int f) {
    this->loc = loc;
    this->x_pos = loc.x; 
    this->y_pos = loc.y; 
    this->g_value = g; 
    this->f_value = f;
}

void Node::calculateFValue(const loc_t &locDest) {
    static int xd, yd, d;
    xd = locDest.x - x_pos;
    yd = locDest.y - y_pos;         

    d = abs(xd) + abs(yd);
    f_value = g_value + d * 10; 
}

void Node::updateGValue(const int & i) {
    g_value += (4 == 8 ? (i % 2 == 0 ? 10 : 14) : 10);  
}