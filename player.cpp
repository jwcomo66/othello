#include "player.hpp"
#include <vector>
// joe has made a small change!

//Rohan also made a small change ! ! ! ! ! 
/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
 
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    b = new Board();
    color = side;
    w = new int*[8];
    for (int i = 0; i < 8; i++) {
		w[i] = new int[8];
	}
    // top left quadrant
    
    w[0][0] = 120;
    w[0][1] = -20;
    w[0][2] = 20;
    w[0][3] = 5;
    w[1][0] = -20;
    w[1][1] = -40;
    w[1][2] = -5;
    w[1][3] = -5;
    w[2][0] = 20;
    w[2][1]= -5;
    w[2][2] = 15;
    w[2][3] = 3;
    w[3][0] = 5;
    w[3][1] = -5;
    w[3][2] = 3;
    w[3][3] = 3;
    
    //fill upper right quadrand mirroring upper left quad
    for (int i = 0; i < 4; i++)
    {
		for (int j = 4; j < 8; j++)
		{
			w[i][j] = w[i][7 - j];
		}
	}
	// fill lower left quadrant 
	for (int i = 4; i < 8; i++)
    {
		for (int j = 0; j < 4; j++)
		{
			w[i][j] = w[7 - i][j];
		}
	}
	// fill lower right quadrant
	for (int i = 4; i < 8; i++)
    {
		for (int j = 4; j < 8; j++)
		{
			w[i][j] = w[7 - i][7 - j];
		}
	}
    
    

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
     
       //fprintf(stderr, "Doing move.\n");
       
       
       Side other = (color == BLACK) ? WHITE : BLACK; 
       if (opponentsMove != nullptr) {
		   b->doMove(opponentsMove, other);
	   } 
       
       std::vector<Move*> moves;
       std::vector<int> weights;

		for (int i = 0; i < 8; i++) 
		{
			for (int j = 0; j < 8; j++) 
			   {
				
				Move * moneyMove = new Move(i, j);
                
                if (b->checkMove(moneyMove, color))
                { 
				  moves.push_back(moneyMove);
				  weights.push_back(w[i][j]);
                  //fprintf(stderr, "Added move \n");
			     }
			    else
			     {
					 delete moneyMove;
				  }
	  
			   }
		 }
		 
		 
		 //fprintf(stderr, "%d\n", moves.size());
		 if (moves.size() != 0){
		 
		 int index = 0;
		 int maxWeight = weights[index];
		 for (unsigned int i = 0; i < weights.size(); i++){
			 if(weights[i] > maxWeight){
				 maxWeight = weights[i];
				 index = i;
				 }
			 
			 }
		 b->doMove(moves[index], color);
		 return moves[index];
		 
	   }
		 
		 
		 return nullptr;
     

}
