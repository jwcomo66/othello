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
    testingMinimax = true;
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

//finds the miminum score of the opponents moves given a move and board
int Player::findMin(Board * b1, Move * move, int n){
	 
	 
	//perform our move on board copy
	  b1->doMove(move, color);
	  
	   Side other = (color == BLACK) ? WHITE : BLACK; 
	  
	 //create vectors to hold ourmoves and oppmoves
	 std::vector<Move*>ourMoves;
	 std::vector<Move*> oppMoves;
	 //oppMoves.reserve(10000);
	 
	 oppMoves = getPossibleMoves(b1, other);
	 
	
	 /*std::vector <Board*> boardStatesOurMoves;
	 std::vector <Board*> boardStatesOppMoves;*/
	 std::vector<int> scores;
	 //scores.reserve(500);
	  for (int i = 1; i <=n; i++){
		  if(i == n){
			  
			  for (unsigned int j = 0; j<oppMoves.size(); j++){
				 //that is the baord after the opponents move has been made
				  Board * b2 = oppMoves[j]->board;
				  
				  //b2->doMove(oppMoves[j], other);
				  //fprintf(stderr, "how big? %d\n", scores.size());
				  scores.push_back(getScore(b2, color));
			  }
				  
				  if (scores.size() == 0){
					  return getScore(b1,color);
					  
			        }
					//now just return the minimum score from scores
					int min = scores[0];
					for (unsigned int p = 0; p < scores.size(); p++)
					{
						if (scores[p] < min)
						{
							min = scores[p];
						}
					}
					//fprintf(stderr, "Sending score\n");
					return min;
					
				  }
			  
			  
			
			else{
				
				//first clear ourMoves
				for (unsigned int l = 0; l<ourMoves.size(); l++){
					delete ourMoves[l];
					}
				ourMoves.clear();
				
				
				//use oppMoves to fill ourMoves
				for(unsigned int j = 0; j < oppMoves.size(); j++){
					//Move * oppMove = oppMoves[j];
					
					std::vector<Move*> ourNextMoves;
					
					ourNextMoves = getPossibleMoves(oppMoves[j]->board, color);
					
					//now add this shit to our big moves vector
					
					for (unsigned int k = 0; k < ourNextMoves.size(); k++){
						 ourMoves.push_back(ourNextMoves[k]);
						// fprintf(stderr, "Added move to ours \n");
						}
					
						
					//our moves vector is filled!!!!!!!!
		
					}
					
				//clear oppMoves so we can update it
				for (unsigned int l = 0; l<oppMoves.size(); l++){
					delete oppMoves[l];
					
					}
				//fprintf(stderr, "OurMOves size %d \n", ourMoves.size());
				
				oppMoves.clear();
				
					
				std::vector<Move*> oppNextMoves;
				//now use the new version of ourMOves to update oppmoves for the next iteration
				for(unsigned int j = 0; j < ourMoves.size(); j++){
					
					oppNextMoves = getPossibleMoves(ourMoves[j]->board, other);
					
					//now add this shit to opp moves vector
					
		
					for (unsigned int m = 0; m < oppNextMoves.size(); m++){

						
						oppMoves.push_back(oppNextMoves[m]);
						 
						// fprintf(stderr, "Added move to theirs\n");
						
					     
						}
						
					
						
				oppNextMoves.clear();
				}
				//fprintf(stderr, "OppMOves size %d \n", oppMoves.size());
		  
		  
		  }
	  
	}
	return 100;
}
	
//returns a vector of the possible moves (with their boardstates filled) for a given color
std::vector<Move*> Player::getPossibleMoves(Board * b1, Side side){
	
	   std::vector<Move*> moves;

		for (int i = 0; i < 8; i++) 
		{
			for (int j = 0; j < 8; j++) 
			   {
				
				Move * moneyMove = new Move(i, j);
                
                if (b1->checkMove(moneyMove, side))
                { 
                    Board * b3 = b1->copy();
                    b3->doMove(moneyMove,side);
                    moneyMove->board = b3;
                    
					moves.push_back(moneyMove);
					
				
					
                  //fprintf(stderr, "Added move \n");
			     }
			    else
			     {
					 delete moneyMove;
				  }
	  
			   }
			   
	}
	return moves;

}


//Scores the board for a given side

int Player::getScore(Board* b1, Side side){
	 Side other = (color == BLACK) ? WHITE : BLACK;
	 
	 int score = 0;
	 for (int row = 0; row < 8; row++){
		 for (int col = 0; col < 8; col++){
			 
			 if(b1->get(side, col, row)){
				 score += w[row][col];
				 }
			 else if(b1->get(other, col, row)){
				 score -= w[row][col];
				 }
			 
			 }
		 }
	return score;
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
		   //fprintf(stderr, "Opponent move: %d %d\n", opponentsMove->getX(), opponentsMove->getY());
		   b->doMove(opponentsMove, other);
	   } 
       int n = 2;
       std::vector<Move*> moves;
       std::vector<int> min_score;

		for (int i = 0; i < 8; i++) 
		{
			for (int j = 0; j < 8; j++) 
			   {
				
				Move * moneyMove = new Move(i, j);
                
                if (b->checkMove(moneyMove, color))
                { 
					Board * copy = b->copy();
					
					
					int min = findMin(copy, moneyMove, n);
					moves.push_back(moneyMove);
					min_score.push_back(min);
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
		 int max_min = min_score[index];
		 for (unsigned int i = 0; i < min_score.size(); i++){
			 if(min_score[i] > max_min){
				 max_min = min_score[i];
				 index = i;
				 }
			 
			 }
		 b->doMove(moves[index], color);
		  //fprintf(stderr, "Our move: %d %d\n", moves[index]->getX(), moves[index]->getY());
		 return moves[index];
		 
	   }
		  //fprintf(stderr, "Returned nullptr\n");
		 
		 return nullptr;
}
