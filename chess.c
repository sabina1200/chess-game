#include <stdio.h>
#include <stdlib.h>
#include "chess.h"

void init(char table[][8])
{
    int i,j;
    for(i=0; i<8; i++)
        for(j=0; j<8; j++)
        {
            switch(i)
            {
            case 0:
                switch(j)
                {
                case 0:
                case 7:
                    table[i][j]='R';
                    break;
                case 1:
                case 6:
                    table[i][j]='N';
                    break;
                case 2:
                case 5:
                    table[i][j]='B';
                    break;
                case 3:
                    table[i][j]='Q';
                    break;
                case 4:
                    table[i][j]='K';
                    break;
                }
                break;
            case 1:
                table[i][j]='P';
                break;
            case 2:
            case 3:
            case 4:
            case 5:
                table[i][j]=' ';
                break;
            case 6:
                table[i][j]='p';
                break;
            case 7:
                switch(j)
                {
                case 0:
                case 7:
                    table[i][j]='r';
                    break;
                case 1:
                case 6:
                    table[i][j]='n';
                    break;
                case 2:
                case 5:
                    table[i][j]='b';
                    break;
                case 3:
                    table[i][j]='q';
                    break;
                case 4:
                    table[i][j]='k';
                    break;
                }
                break;
            }
        }
}

void print(char table[][8])
{
    int k=8;
    printf("  abcdefgh \n");
    for(int i=7; i>=0; i--)
    {
        printf("%d ", k);
        for(int j=0; j<8; j++)
            printf("%c", table[i][j]);
        printf(" %d", k);
        printf("\n");
        k--;
    }
    printf("  abcdefgh ");
}

int get_line(char table[][8], char start_col, int start_row,
             int dc, int dr, char line[])
{
    int k=0;
    int col=start_col-'a';
    int row=start_row-1;
    col+=dc;
    row+=dr;
    while(col>=0 && col<8 && row>=0 && row<8)
    {
        line[k++]=table[row][col];
        col+=dc;
        row+=dr;
    }
    return k;
}

void encode(char table[][8], char* fen)
{
    int k=0,cnt=0;
    for(int i=7; i>=0; i--)
    {
        cnt=0;
        for(int j=0; j<8; j++)
        {
            if(table[i][j]==' ')
                cnt++;
            else
            {
                if(cnt>0)
                {
                    fen[k++]='0'+cnt;
                    cnt=0;
                }
                fen[k++]=table[i][j];
            }
        }
        if(cnt>0)
            fen[k++]='0'+cnt;
        if(i>0)
            fen[k++]='/';
    }
    fen[k]='\0';
}

void decode(char table[][8], char* fen)
{
    for(int i=7; i>=0; i--)
    {
        for(int j=0; j<8; j++)
        {
            table[i][j]=' ';
        }
    }
    int  k=0,i=7,j=0;
    while (fen[k]!='\0' && i>=0)
    {
        if (fen[k]>='1' && fen[k]<='8')
        {
            int cnt=fen[k]-'0';
            j+=cnt;
        }
        else if(fen[k]=='/')
        {
            i--;
            j=0;
        }
        else
        {
            if(j<8)
            {
                table[i][j]=fen[k];
                j++;
            }
        }
        k++;
    }
}

move* all_moves(char table[][8], char tomove)
{
    int k=220,cnt=0;
    int dr[]= {-1,1,0,0,-1,-1,1,1}; //for i(up and down), first 4 are for rook, last 4 for bishop, all for queen
    int dc[]= {0,0,-1,1,-1,1,-1,1}; // for j(left and right), -||-
    move* moves=malloc(sizeof(move)*k);
    for(int i=7; i>=0; i--)
        for(int j=0; j<=7; j++)
        {
            if(table[i][j]==' ')
                continue;
            if((tomove=='b' && !(table[i][j]>='a' && table[i][j]<='z'))||
                    (tomove=='w' && !(table[i][j]>='A' && table[i][j]<='Z')))
                continue;
            int start=0,end=-1;
            if(table[i][j]=='R'||table[i][j]=='r'){
                start=0;
                end=3;
            }
            else if(table[i][j]=='b'||table[i][j]=='B'){
                start=4;
                end=7;
            }
            else if(table[i][j]=='q'||table[i][j]=='Q')
            {
                start=0;
                end=7;
            }
        for(int d=start;d<=end;d++){
            int r=i+dr[d];
            int c=j+dc[d];
            while(r>=0 && r<=7 && c>=0 && c<=7){
                if(table[r][c]==' '){
                    moves[cnt].c1='a'+j;
                    moves[cnt].r1=1+i;
                    moves[cnt].c2='a'+c;
                    moves[cnt].r2=1+r;
                    cnt++;
                }
                else{
                int is_w=(table[r][c]>'A'&&table[r][c]<'Z');
                int is_opp=((is_w && tomove=='b')||(!is_w && tomove=='w'));
                if(is_opp){
                    moves[cnt].c1='a'+j;
                    moves[cnt].r1=1+i;
                    moves[cnt].c2='a'+c;
                    moves[cnt].r2=1+r;
                    cnt++;
                }
                break;
                }
             r+=dr[d];
             c+=dc[d];
            }
        }
        }
    moves[cnt].c1=0;
    moves[cnt].r1=0;
    moves[cnt].c2=0;
    moves[cnt].r2=0;
    return moves;
}
