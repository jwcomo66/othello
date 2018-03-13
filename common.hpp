#ifndef __COMMON_H__
#define __COMMON_H__

#include "board.hpp"
class Board;

/*enum Side { 
    WHITE, BLACK
};
*/

class Move {
   
public:
    int x, y;
    Board * board;
    int score;
    Move(int x, int y) {
        this->x = x;
        this->y = y;        
    }
    ~Move() {
		// delete board;
		}

    int getX() { return x; }
    int getY() { return y; }

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
};

#endif
