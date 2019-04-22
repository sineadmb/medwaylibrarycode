  char board [9] = {49,50,51,52,53,54,55,56,57};
  int input;
  int player = 1;
  int p;
  

void setup() {
  Serial.begin(9600);
}

void loop() 
{
  
printBoard();
CheckWinner();
getInput();

}

 void CheckWinner()
 {
 if (player == 1)
 { 
  p = 88;
 }
 else 
 {
  //player is 2
  p = 79;
 }

 //check
 checkRowsAndColumns();
 
//swap
if (player == 1)
 { 
  player = 2;
  p = 79;
 }
 else 
 {
  player = 1;
  p = 88;
 }

//check again
checkRowsAndColumns();
 
 //change back to original
 if (player == 1)
 { 
  player = 2;
  p = 79;
 }
 else 
 {
  player = 1;
  p = 88;
 }
 }

 void checkTop()
 {
if ( board[0] == p && board[1] == p && board[2] == p)
{
  GameOver();
}
 }

 void checkMiddleAcross()
 {
  if ( board[3] == p && board[4] == p && board[5] == p)
    {
   GameOver();
}
}

void checkBottom()
{
 if ( board[6] == p && board[7] == p && board[8] == p)
{
   GameOver();
}
 } 

void checkLeft()
{
 if ( board[0] == p && board[3] == p && board[6] == p)
{
   GameOver();
}
 } 

 void checkMiddleDown()
 {
 if ( board[1] == p && board[4] == p && board[7] == p)
{
   GameOver();
}
 } 

 void checkRight()
{
 if ( board[2] == p && board[5] == p && board[8] == p)
{
   GameOver();
}
 } 

 void checkDown()
 {
 if ( board[0] == p && board[4] == p && board[8] == p)
{
   GameOver();
}
 } 

 void checkUp()
 {
 if ( board[6] == p && board[4] == p && board[2] == p)
{
  GameOver();
}
 } 

 void GameOver()
 {
  
  Serial.println("Game over");
  Serial.print("Player ");
  Serial.print(player);
  Serial.println(" Wins");
  resetBoard();
 }

 void resetBoard()
 {
  board[0] = 49;
  board[1] = 50;
  board[2] = 51;
  board[3] = 52;
  board[4] = 53;
  board[5] = 54;
  board[6] = 55;
  board[7] = 56;
  board[8] = 57;
  Serial.println(" ");
  Serial.println("Play again:");
  Serial.println("Player 2 (O) goes first");
  printBoard();
  player = 1;
 }

void printBoard()
{
  Serial.print("_");
Serial.print(board[0]);
Serial.print("_|_");
Serial.print(board[1]);
Serial.print("_|_");
Serial.print(board[2]);
Serial.println("_");
//end line
Serial.print("_");
Serial.print(board[3]);
Serial.print("_|_");
Serial.print(board[4]);
Serial.print("_|_");
Serial.print(board[5]);
Serial.println("_");
//end of line
Serial.print(" ");
Serial.print(board[6]);
Serial.print(" | ");
Serial.print(board[7]);
Serial.print(" | ");
Serial.print(board[8]);
Serial.println(" ");
delay(50);
}

void getInput()
{
  if (player == 1)
  {
    Serial.println("Player 1, select square");
  }

  if (player == 2)
  {
    Serial.println("Player 2, select square");
  }
  
while (!Serial.available())
{
delay(50);
}
input = Serial.parseInt();
if (player == 1) 
{
  board[input-1] = 88;
  player = 2;
}
else
{
  board[input-1] = 79;
  player = 1;
}
}

void checkTie()
{
if (board[0] != 49 && board[1] != 50 && board[2] != 51 && board[3] != 52 && board[4] != 53 && board[5] != 54 && board[6] != 55 && board[7] != 56 && board[8] != 57)
{
  Serial.println("Tie Game");
  Serial.println(" ");
  resetBoard();
}
}

void checkRowsAndColumns()
{
  checkTop();
 checkMiddleAcross();
 checkBottom();
 checkLeft();
 checkMiddleDown();
 checkRight();
 checkDown();
 checkUp();
 checkTie();

}

