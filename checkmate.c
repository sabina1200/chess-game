#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "checkmate.h"

void decode(char table[][8], char* fen)
{
    for(int i=7; i>=0; i--)
    {
        for(int j=0; j<8; j++)
        {
            table[i][j]=' ';
        }
    }
    int k=0,i=7,j=0;
    while(fen[k]!='\0' && i>=0)
    {
        if(fen[k]>='1' && fen[k]<='8')
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

int is_attacked(char table[][8], char tomove)
{
    int kr=-1, kc=-1;
    char king=(tomove=='w')?'K':'k';
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            if(table[i][j]==king)
            {
                kr=i;
                kc=j;
            }
    char n_opp=(tomove=='w')?'n':'N';
    char r_opp=(tomove=='w')?'r':'R';
    char b_opp=(tomove=='w')?'b':'B';
    char q_opp=(tomove=='w')?'q':'Q';
    char p_opp=(tomove=='w')?'p':'P';
    char k_opp=(tomove=='w')?'k':'K';
    int ndr[]= {2, 1, -1, -2, -2, -1, 1, 2};
    int ndc[]= {1, 2, 2, 1, -1, -2, -2, -1};
    for(int k=0; k<8; k++)
    {
        int r=kr+ndr[k], c=kc+ndc[k];
        if(r>=0 && r<8 && c>=0 && c<8 && table[r][c]==n_opp) return 1;
    }
    int dr[]= {-1, 1, 0, 0, -1, -1, 1, 1};
    int dc[]= {0, 0, -1, 1, -1, 1, -1, 1};
    for(int k=0; k<8; k++)
    {
        for(int s=1; s<8; s++)
        {
            int r=kr+dr[k]*s, c=kc+dc[k]*s;
            if(r<0 || r>7 || c<0 || c>7) break;
            char p=table[r][c];
            if(p!=' ')
            {
                if(p==q_opp) return 1;//queens attack from any direction
                if(k<4 && p==r_opp) return 1;
                if(k>=4 && p==b_opp) return 1;
                if(s==1 && p==k_opp) return 1;
                break;
            }
        }
    }
    int pd=(tomove=='w')?1:-1;//enemy black pawns are above while enemy white pawns are below
    if(kr+pd>=0 && kr+pd<8)
    {
        if(kc-1>=0 && table[kr+pd][kc-1]==p_opp) return 1;
        if(kc+1<8 && table[kr+pd][kc+1]==p_opp) return 1;
    }
    return 0;
}

int solve(char table[][8], char tomove, int mode, FILE *out)
{
    char opp=(tomove=='w')?'b':'w';
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            char p=table[i][j];
            if(p==' ') continue;
            if(tomove=='w' && (p<'A' || p>'Z')) continue;
            if(tomove=='b' && (p<'a' || p>'z')) continue;
            int dr[]= {-1, 1, 0, 0, -1, -1, 1, 1};
            int dc[]= {0, 0, -1, 1, -1, 1, -1, 1};
            int n_dr[]= {2, 1, -1, -2, -2, -1, 1, 2};
            int n_dc[]= {1, 2, 2, 1, -1, -2, -2, -1};
            int *current_dr=dr, *current_dc=dc;
            int start=0, end=8, steps=8;
            if(p=='N' || p=='n')
            {
                current_dr=n_dr;
                current_dc=n_dc;
                steps=1;
            }
            else if(p=='K' || p=='k')
                steps=1;
            else if(p=='R' || p=='r')
                end=4;
            else if(p=='B' || p=='b')
                start=4;
            else if(p=='P' || p=='p')
                end=0;//disable loop for pawns
            for(int d=start; d<end; d++)
            {
                for(int s=1; s<=steps; s++)
                {
                    int nr=i+current_dr[d]*s, nc=j+current_dc[d]*s;
                    if(nr<0 || nr>7 || nc<0 || nc>7) break;
                    char target=table[nr][nc];
                    if(tomove=='w' && target>='A' && target<='Z') break;
                    if(tomove=='b' && target>='a' && target<='z') break;
                    table[i][j]=' ';
                    table[nr][nc]=p;
                    int success=0;
                    if(!is_attacked(table, tomove))//checks if own king is safe
                    {
                        if(mode==0) success=1;
                        else if(is_attacked(table, opp) && !solve(table, opp, 0, out))
                        {
                            move m;
                            m.c1=j+'a';
                            m.r1=i+1;
                            m.c2=nc+'a';
                            m.r2=nr+1;
                            fprintf(out, "%c%d-%c%d\n", m.c1, m.r1, m.c2, m.r2);
                            success=1;
                        }
                    }
                    table[i][j]=p;
                    table[nr][nc]=target;
                    if(success) return 1;
                    if(target!=' ') break;
                }
            }
            if(p=='P' || p=='p')
            {
                int pd=(tomove=='w')?1:-1;
                int start_rank=(tomove=='w')?1:6;
                int max_steps=(i==start_rank)?2:1;
                for(int step=1; step<=max_steps; step++)
                {
                    int nr=i+pd*step;
                    if(nr<0 || nr>7 || table[nr][j]!=' ') break;
                    table[i][j]=' ';
                    table[nr][j]=p;
                    int success=0;
                    if(!is_attacked(table, tomove))
                    {
                        if(mode==0) success=1;
                        else if(is_attacked(table, opp) && !solve(table, opp, 0, out))
                        {
                            move m;
                            m.c1=j+'a';
                            m.r1=i+1;
                            m.c2=j+'a';
                            m.r2=i+pd+1;
                            fprintf(out, "%c%d-%c%d\n", m.c1, m.r1, m.c2, m.r2);
                            success=1;
                        }
                    }
                    table[i][j]=p;
                    table[i+pd][j]=' ';
                    if(success) return 1;
                }
                for(int dx=-1; dx<=1; dx+=2)
                {
                    if(j+dx>=0 && j+dx<8 && i+pd>=0 && i+pd<8 && table[i+pd][j+dx]!=' ')
                    {
                        char trg=table[i+pd][j+dx];
                        int is_eny=(tomove=='w')?(trg>='a' && trg<='z'):(trg>='A' && trg<='Z');
                        if(is_eny)
                        {
                            table[i][j]=' ';
                            table[i+pd][j+dx]=p;
                            int success=0;
                            if(!is_attacked(table, tomove))
                            {
                                if(mode==0) success=1;
                                else if(is_attacked(table, opp) && !solve(table, opp, 0, out))
                                {
                                    move m;
                                    m.c1=j+'a';
                                    m.r1=i+1;
                                    m.c2=j+dx+'a';
                                    m.r2=i+pd+1;
                                    fprintf(out, "%c%d-%c%d\n", m.c1, m.r1, m.c2, m.r2);
                                    success=1;
                                }
                            }
                            table[i][j]=p;
                            table[i+pd][j+dx]=trg;
                            if(success) return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

void run_tests()
{
    FILE* bf=fopen("chess_in.bin", "rb");
    FILE* out=fopen("chess_out.txt", "w");
    if(!bf || !out) return;
    unsigned char n_in,key_in;
    fread(&n_in, sizeof(unsigned char), 1, bf);
    fread(&key_in, sizeof(unsigned char), 1, bf);
    int n=n_in;
    int key=key_in;
    char fen[120], tomove, c;
    while(n--)
    {
        int i=0;
        while(1)
        {
            fread(&c, sizeof(char), 1, bf);
            c=c^key;
            fen[i++]=c;
            if(c=='\0') break;
        }
        fread(&tomove, sizeof(char), 1, bf);
        tomove=tomove^key;
        char table[8][8];
        decode(table, fen);
        solve(table, tomove, 1, out);
    }
    fclose(bf);
    fclose(out);
}
