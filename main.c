#include <stdio.h>
#include <stdlib.h>
#include "chess.h"

int main()
{
    char table[8][8];
    init(table);
    printf("~~~Exercise 2\n\n");
    print(table);
    printf("\n\n");
    printf("~~~Exercise 3\n\n");
    char line[8];
    int nr=get_line(table, 'd', 4, 1, 1, line);
    printf("First call: %d\n", nr);
    printf("Contents of line after call:");
    for(int i=0; i<nr; i++)
        printf("'%c', ",line[i]);
    printf("\n\n");
    nr = get_line(table, 'd', 4, 0, -1, line);
    printf("Second call: %d\n",nr);
    printf("Contents of line after call:");
    for(int i=0; i<nr; i++)
        printf("'%c', ",line[i]);
    printf("\n\n");
    char* fen;
    encode(table, fen);
    printf("Encoding for initial table is: %s", fen);
    puts("\n");
    fen="7q/8/8/8/8/8/8/P7";
    decode(table, fen);
    printf("Decoding is:\n");
    print(table);
    puts("\n");
    puts("Possible moves for example table is: \n");
    fen="rnbqkbnr/pp1pppp1/8/8/8/7b/PPPPPPPP/RNBQKBNR";
    decode(table,fen);
    move* moves=all_moves(table, 'b');
    int i=0;
    while(moves[i].r1!=0)
    {
        printf("%c%d-%c%d, \n", moves[i].c1, moves[i].r1, moves[i].c2,moves[i].r2);
        i++;
    }
    free(moves);
    return 0;
}
