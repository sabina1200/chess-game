#ifndef CHECKMATE_H_INCLUDED
#define CHECKMATE_H_INCLUDED

void run_tests();
void decode(char table[][8], char* fen);
int solve(char table[][8], char tomove, int mode, FILE *out);
int is_attacked(char table[][8], char color);
typedef struct{
    char c1,c2;
    int r1,r2;
}move;
#endif // CHECKMATE_H_INCLUDED
