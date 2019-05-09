#ifndef NODE_H
#define NODE_H

#include "struct.h"

using namespace std;

class Node
{
    public:
        Node(const loc_t &location, int g, int f);

        loc_t loc;
        int x_pos;
        int y_pos;
        int g_value;
        int f_value;  

        void calculateFValue(const loc_t& locDest);
        void updateGValue(const int & i);

    	friend bool operator<(const Node & a, const Node & b)
	    {
	        return a.f_value > b.f_value;
	    }

};
#endif