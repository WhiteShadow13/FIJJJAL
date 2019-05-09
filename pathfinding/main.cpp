#include <iostream>
#include <string>

#include "pathfinding.h"
#include "struct.h"

using namespace std;

int main()
{
    loc_t loc_start;
    loc_t loc_end;

    loc_start.x = 10;
    loc_start.y = 10;

    loc_end.x = 90;
    loc_end.y = 90;

    Pathfinding path = Pathfinding(loc_start, loc_end, 1);

    string way =path.aStar();

    path.draw(way);
}