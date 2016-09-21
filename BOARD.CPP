#include "BOARD.H"
#include "STACK.H"
Board::Board()
/* 
 
Post: The Board is initialized as empty.
 
*/

{
   for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
         squares[i][j] = 0;
   moves_done = 0;
}
 
bool Board::done() const
/* 
 
Post: Return true if the game is over; either because
a player has already won
or because all nine squares have been filled.
 
*/
{
   return moves_done == 9 || the_winner() > 0;
}
 
void Board::print() const
/* 
 
Post: The Board is printed.
 
*/

{
   int i, j;
   for (i = 0; i < 5; i++) cout << "-"; cout << "\n";
   for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++)
         if (!squares[i][j]) cout << " ";
         else if (squares[i][j] == 1) cout << "X";
         else cout << "O";
      cout << "\n";
   }
}
 
void Board::instructions() const
/* 
 
Post: Instructions for tic-tac-toe are printed.
 
*/
{
   cout << " This game plays Tic Tac To \n";
}
 
bool Board::better(int value, int old_value) const
/* 
 
Post: Return true if the next player to move prefers
a game situation value rather than a game situation old_value.
 
*/

{
   return (moves_done % 2 && (value < old_value)) ||
          (!(moves_done % 2) && value > old_value);
}
 
void Board::play(Move try_it)
/* 
 
Post: The Move try_it is played on the Board.
 
*/

{
   squares[try_it.row][try_it.col] = moves_done % 2 + 1;
   moves_done++;
}
 
int Board::worst_case() const
/* 
 
Post: Return the value of a worst case scenario for the mover.
 
*/

{
   if (moves_done % 2) return 10;
   else return -10;
}
 
int Board::the_winner() const
/* 
 
Post: Return either a value of 0 for a position where neither player has won,
a value of 1 if the first player has won,
or a value of 2 if the second player has won.
 
*/

{
   int i;
   for (i = 0; i < 3; i++)
      if (squares[i][0] && squares[i][0] == squares[i][1]
                        && squares[i][0] == squares[i][2])
            return squares[i][0];

   for (i = 0; i < 3; i++)
      if (squares[0][i] && squares[0][i] == squares[1][i]
                        && squares[0][i] == squares[2][i])
            return squares[0][i];

 
   if (squares[0][0] && squares[0][0] == squares[1][1]
                     && squares[0][0] == squares[2][2])
            return squares[0][0];

   if (squares[0][2] && squares[0][2] == squares[1][1]
                     && squares[2][0] == squares[0][2])
            return squares[0][2];
   return 0;
}
 
int Board::evaluate() const
/* 
 
Post: Return either a value of 0 for a position where neither player has won,
a positive value between 1 and 9 if the first player has won,
or a negative value between -1 and -9 if the second player has won,
 
*/

{
   int winner = the_winner();
   if (winner == 1) return 10 - moves_done;
   else if (winner == 2) return moves_done - 10;
   else return 0;
}
 
int Board::legal_moves(Stack &moves) const
/* 
 
Post: The parameter Stack moves is set up to contain all
possible legal moves on the Board.
 
*/

{
   int count = 0;
   while (!moves.empty()) moves.pop();
   for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
         if (squares[i][j] == 0) {
            Move can_play(i,j);
            moves.push(can_play);
            count++;
         }
   return count;
}
