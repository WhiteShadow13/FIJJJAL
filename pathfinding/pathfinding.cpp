#include <iostream>
#include <iomanip>
#include <math.h>
#include <ctime>
#include <string>
#include <queue>

#include "pathfinding.h"
#include "node.h"

const int NDIR = 4; 
const int xDir[NDIR] = {1, 0, -1, 0};
const int yDir[NDIR] = {0, 1, 0, -1};

Pathfinding::Pathfinding(const loc_t &loc_start , const loc_t &loc_finish, int step) {
    this->loc_finish = loc_finish;
    this->loc_start = loc_start;
    this->buildMap(loc_start, loc_finish, step);
}

void Pathfinding::buildMap(const loc_t &loc_start , const loc_t &loc_finish, int step) {
    this->XDIM = 100;
    this->YDIM = 100;
}

void Pathfinding::addObstacles(loc_t obstacle) {
    obstacles.push_back(obstacle);
}

string Pathfinding::aStar() {
    int closedNodes[XDIM][YDIM];
    int openNodes[XDIM][YDIM];
    int dirMap[XDIM][YDIM];
    int squares[XDIM][YDIM];

    for(std::vector<Node>::size_type i = 0; i != obstacles.size(); i++) {
        squares[obstacles[i].x][obstacles[i].y] = 1;
    }
    
    // list of open (not-yet-checked-out) nodes
    static priority_queue<Node> q[2]; 

    // q index
    static int qi; 

    static Node* pNode1;
    static Node* pNode2;
    static int i, j, x, y, xNext, yNext;
    static char c;
    qi = 0;

    // reset the Node lists (0 = ".")
    for(j = 0; j < YDIM; j++) {
        for(i = 0; i < XDIM; i++) {
            closedNodes[i][j] = 0;
            openNodes[i][j] = 0;
        }
    }
    
    // create the start node and push into list of open nodes
    pNode1 = new Node(loc_start, 0, 0); 
    pNode1->calculateFValue(loc_finish);
    q[qi].push(*pNode1);
 
    // A* search
    while(!q[qi].empty()) {
        // get the current node w/ the lowest FValue
        // from the list of open nodes
        pNode1 = new Node(q[qi].top().loc, q[qi].top().g_value, q[qi].top().f_value);

        x = pNode1->x_pos; 
	    y = pNode1->y_pos;

	    // remove the node from the open list
        q[qi].pop(); 
        openNodes[x][y] = 0;

        // mark it on the closed nodes list
        closedNodes[x][y] = 1;

        // stop searching when the goal state is reached
        if(x == loc_finish.x && y == loc_finish.y) {

	    // generate the path from finish to start from dirMap
        string path = "";
        while(!(x == loc_start.x && y == loc_start.y)) {
            
                j = dirMap[x][y];
                c = '0' + (j + NDIR/2) % NDIR;
                path = c + path;
                x += xDir[j];
                y += yDir[j];
            }

            // garbage collection
            delete pNode1;

            // empty the leftover nodes
            while(!q[qi].empty()) q[qi].pop();           
            return path;
        }

        // generate moves in all possible directions
        for(i = 0; i < NDIR; i++) {
            xNext = x + xDir[i]; 
	        yNext = y + yDir[i];

	        // if not wall (obstacle) nor in the closed list
            if(!(xNext < 0 || xNext > XDIM - 1 || yNext < 0 || yNext > YDIM - 1 || 
			squares[xNext][yNext] == 1 || closedNodes[xNext][yNext] == 1)) {
               
		        // generate a child node
                loc_t loc;
                loc.x = xNext;
                loc.y = yNext;
                pNode2 = new Node(loc, pNode1->g_value, pNode1->f_value);
                pNode2->updateGValue(i);
                pNode2->calculateFValue(loc_finish);

                // if it is not in the open list then add into that
                if(openNodes[xNext][yNext] == 0) {
                    openNodes[xNext][yNext] = pNode2->f_value;
                    q[qi].push(*pNode2);
                    // mark its parent node direction
                    dirMap[xNext][yNext] = (i + NDIR/2) % NDIR;
                }

		        // already in the open list
                else if(openNodes[xNext][yNext] > pNode2->f_value) {
                    // update the FValue info
                    openNodes[xNext][yNext] = pNode2->f_value;

                    // update the parent direction info,  mark its parent node direction
                    dirMap[xNext][yNext] = (i + NDIR/2) % NDIR;

                    // replace the node by emptying one q to the other one
                    // except the node to be replaced will be ignored
                    // and the new node will be pushed in instead
                    while(!(q[qi].top().x_pos == xNext && 
                        q[qi].top().y_pos== yNext)) {                
                        q[1 - qi].push(q[qi].top());
                        q[qi].pop();       
                    }

		            // remove the wanted node
                    q[qi].pop(); 
                    
                    // empty the larger size q to the smaller one
                    if(q[qi].size() > q[1 - qi].size()) qi = 1 - qi;
                    while(!q[qi].empty()) {                
                        q[1 - qi].push(q[qi].top());
                        q[qi].pop();       
                    }
                    qi = 1 - qi;

		            // add the better node instead
                    q[qi].push(*pNode2); 
                }
                else delete pNode2; 
            }
        }
        delete pNode1; 
    }
    // no path found
    return ""; 
}

void Pathfinding::draw(string path) {
    int squares[XDIM][YDIM];

    // create empty squares
    for(int j = 0; j < XDIM; j++) {
        for(int i = 0; i < YDIM; i++) squares[i][j] = 0;
    }
 
    cout << "path: " << path << endl;

    // follow the path on the squares and display it 
    if(path.length() > 0) {
        char c;
	    int m,n;
        int x = loc_start.x;
        int y = loc_finish.y;
        squares[x][y] = 2;

        for(m = 0; m < path.length(); m++) {
            c = path.at(m);
            n = atoi(&c); 
            x = x + xDir[n];
            y = y + yDir[n];
            squares[x][y] = 3;
        }
        squares[x][y] = 4;
    
        // display the squares with the path
        for(int j = YDIM - 1; j >= 0; j--) {
            for(int i = 0; i < XDIM; i++) {
                if(squares[i][j] == 0)
                    cout << ".";
                else if(squares[i][j] == 1)
                    cout << "O"; //obstacle
                else if(squares[i][j] == 2)
                    cout << "I"; //Initial
                else if(squares[i][j] == 3)
                    cout << "P"; //path
                else if(squares[i][j] == 4)
                    cout << "F"; //final
	    }
            cout << endl;
        }
    }
}


