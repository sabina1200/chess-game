# chess-game
Contains following homeworks:

HW 5 - Modular programming

You will be developing a chess application. If you are not familiar with the move rules you can look them up. For now, we are only interested in representing the table, so check:
https://en.wikipedia.org/wiki/Algebraic_notation_(chess) 

Implement the following as a module called chess with two files: chess.c and chess.h. The module should be tested in the main module. You will continue implementation in these files in later homeworks.

1. Create a function which receives as input an 8x8 character matrix (2d array) and has the header given below. The function populates the matrix such that it represents the starting chess position, regardless of the previous state of the matrix. Use the following convention:

row 0 from the matrix corresponds to rank (row) 1 from the table;
column 0 form the matrix corresponds to file (column) a from the table;
white pieces are represented by upper-case letters;
black pieces are represented by lower-case letters;
empty cells are represented by the whitespace character ' ';
letter for each piece: pawn p/P; rook r/R; bishop b/B; knight n/N; king k/K; queen q/Q

void init(char table[][8])

2. Create a function which receives as input an 8x8 character matrix (2d array) and has the header given below. The function should print the contents of the matrix on the screen as a chess table along with the legend for rows and columns. Note, that rank 8 is printed on top, even though that is the last row from the matrix. Also, the legend is not stored in the table.

void print(char table[][8])

Example, the starting position would be printed as:

  abcdefgh  
8 rnbqkbnr 8
7 pppppppp 7
6          6
5          5
4          4
3          3
2 PPPPPPPP 2
1 RNBQKBNR 1
  abcdefgh    

3. Create a function which receives as input an 8x8 character matrix (2d array), a starting file (column), a starting rank (row), a direction vector as two values dc, dr and an array called line. The function saves all the elements from the matrix in the line array, starting from the given position and going in the indicated direction. The starting position is excluded. The function should return the number of elements saved. 

int get_line(char table[][8], char start_col, int start_row,
int dc, int dr, char line[])

Examples, using the starting position:
call
contents of line after call
nr
nr = get_line(table, 'd', 4, 1, 1, line)
{ ' ', ' ', 'p', 'r' }
4
nr = get_line(table, 'd', 4, 0, -1, line)
{ ' ', 'P', 'Q' }
3

<img width="564" height="571" alt="image" src="https://github.com/user-attachments/assets/b3cb1834-72df-4135-8e38-9215744e7a39" />

HW 10 - Structures
Define the following structure in your chess.h header file representing a chess move from column c1, row r1 to column c2, row r2:

typedef struct{
	char c1, c2;
	int r1, r2;
}move;

Implement the function called all_moves with the header given below. It receives as input the state of the chess table as a matrix table and a character tomove indicating the next player to move (can only be b for black and w for white). The function returns all the possible correct moves for the next player, considering all the pieces and the rules of chess. For this homework you only need to solve bishops, rooks and queens (the rest will be handled later). A capture is also considered a valid move. The array of possible moves is terminated with an additional structure with all fields equal to 0.

move* all_moves(char table[][8], char tomove)

Exemple, for the table with FEN = rnbqkbnr/pp1pppp1/8/8/8/7b/PPPPPPPP/RNBQKBNR

<img width="288" height="288" alt="Picture1" src="https://github.com/user-attachments/assets/35495fda-7dd3-4ede-9e25-9b67752b8cee" />

and for the black player the function returns the following array of all possible correct moves: 
{ 
d8-c7, d8-b6, d8-a5, 		//black queen 
h8-h7, h8-h6, h8-h5, h8-h4, 	//black rook
h3-g2, h3-g4, h3-f5, h3-e6,	//black bishop
00-00					//additional delimiting structure
}
In your application these will be structures (not string or any other type).
Note, pieces cannot jump over other pieces and can only capture the opponent's pieces.

HW 8 - Strings

Continue your implementation in chess.c/h. Write some tests in your main.

Study the Forsyth–Edwards Notation (FEN) for chess positions. For now, we are interested in the part that describes the positions of the pieces (field 1).

1. Write the function encode with the header given below. This receives as input an 8x8 char matrix and saves the notation representing the table in the given string. The string should be allocated in the parent function and should be sufficiently large for the general case.

void encode(char table[][8], char* fen);

Example, calling with the initial table configuration saves the following in fen:
rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR

2. Write the function decode with the header given below. This receives as input a FEN string and it updates the table to match it. The table is the output for this function.

void decode(char table[][8], char* fen);

Example, the following string input in fen generates the table shown below:
7q/8/8/8/8/8/8/P7

<img width="284" height="286" alt="Picture2" src="https://github.com/user-attachments/assets/03be860a-bb77-4851-9ce8-b587e7348230" />

