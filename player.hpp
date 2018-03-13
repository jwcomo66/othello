#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
#include <vector>
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();
     Board *b;
     Side color;
     int **w;
     int getScore(Board * b1, Side side);
     std::vector<Move*> getPossibleMoves(Board * b1, Side side);

     Move *doMove(Move *opponentsMove, int msLeft);
     int findMin(Board * b1, Move * move, int n);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    
};

#endif
