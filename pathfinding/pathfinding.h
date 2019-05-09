#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <string>
#include <vector>

#include "struct.h"
#include "node.h"

class Pathfinding
{
    public:
        Pathfinding(const loc_t &locStart , const loc_t &locFinish, int step);

        string aStar();
        void addObstacles(loc_t obstacle);
        void draw(string path);

        int XDIM;
        int YDIM; 

        std::vector<loc_t> obstacles;

    private:
        void buildMap(const loc_t &loc_start , const loc_t &loc_finish, int step);
        loc_t loc_start;
        loc_t loc_finish;
};
#endif