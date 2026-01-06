#ifndef CHECKMATE_H_INCLUDED
#define CHECKMATE_H_INCLUDED

void run_tests();
void decode(char table[][8], char* fen);
int solve(char table[][8], char tomove, int mode, FILE *out);
int is_attacked(char table[][8], char color);

#endif // CHECKMATE_H_INCLUDED
