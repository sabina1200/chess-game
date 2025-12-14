#ifndef CHESS_H_INCLUDED
#define CHESS_H_INCLUDED

void init(char table[][8]);
void print(char table[][8]);
int get_line(char table[][8], char start_col, int start_row,
             int dc, int dr, char line[]);
void encode(char table[][8], char* fen);
void decode(char table[][8], char* fen);
typedef struct{
	char c1, c2;
	int r1, r2;
}move;
move* all_moves(char table[][8], char tomove);

#endif // CHESS_H_INCLUDED
