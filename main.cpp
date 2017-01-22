#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <wincon.h>
#include <conio.h>
#include <time.h>


using namespace std;

int c1=37,c2=16,GO=0,dir[7],GW=0;
char m[101][101];

void scr()
{
for(int i=1;i<=40;i++)
        {
        for(int j=1;j<=31;j++)
            cout<<m[i][j];
        cout<<endl;
        }
}

void player_action()
{
    int mv;
    if(_kbhit()) mv=_getch();
    if(mv==119 && c1>25) c1--;
    else if(mv==115 && c1<40) c1++;
    else if(mv==97 && c2>1) c2--;
    else if(mv==100 && c2<31) c2++;
    else if(mv=='p')
    {
        int ok=1;
        for(int i=1;i<=31;i++)
            if(m[c1-2][i]=='+'||m[c1-3][i]=='+') ok=0;
        if(ok==1) m[c1-1][c2]='+';
    }
}

void sh()
{
    int i,j;
    for(i=1;i<=40;i++)
        for(j=1;j<=31;j++)
        if(m[i][j]=='+')
        {
            m[i][j]=' ';
            m[i-1][j]='+';
        }
    for(i=40;i>=1;i--)
        for(j=1;j<=31;j++)
        if(m[i][j]=='-')
        {
            if(m[i+1][j]=='T')
                if(j<31) m[i+1][j+1]='T';
                else m[i+1][j-1]='T';
            m[i][j]=' ';
            m[i+1][j]='-';
        }
}

void en_sh()
{
    srand(time(NULL));
    int i,j;
    for(i=1;i<=15;i++)
        for(j=1;j<=31;j++)
            if(m[i][j]=='T')
            {
                if(m[i+1][j]!='T')
                    if((m[i+2][j+1]!='-')&&(m[i+2][j-1]!='-'))
                        if((m[i+3][j+2]!='-')&&(m[i+3][j-2]!='-'))
                            if((m[i+4][j+3]!='-')&&(m[i+4][j-3]!='-'))
                                if((m[i+5][j+4]!='-')&&(m[i+5][j-4]!='-')) m[i+1][j]='-';
            }
}

void mvmnt_enemy()
{
    int i,j;
    int cnt=0;
    for(i=1;i<=10;i++)
        for(j=1;j<=31;j++)
            if(m[i][j]=='T')
            {
                cnt++;
                if(dir[cnt]==1)
                {
                    if(j>1)
                    {
                        m[i][j-1]='T';
                        m[i][j]=' ';
                    }
                    else if(j==1)
                    {
                        dir[cnt]=0;
                        m[i][j+1]='T';
                        m[i][j]=' ';
                        j++;
                    }
                }
                else if(dir[cnt]==0)
                {
                    if(j<31)
                    {
                        m[i][j+1]='T';
                        m[i][j]=' ';
                        j++;
                    }
                    else if(j==31)
                    {
                        dir[cnt]=1;
                        m[i][j-1]='T';
                        m[i][j]=' ';
                    }
                }
            }
}

void game_body()
{
    srand(time(NULL));
    int i;
    for(i=1;i<=6;i++)
    dir[i]=rand() % 1 + 0;
      for(i=1;i<=6;i++)
        cout<<dir[i];
    while((GO==0)&&(GW==0))
        {
            system("cls");
            scr();
            Sleep(20);
            m[c1][c2]=' ';
            player_action();
            if(m[c1][c2]=='-') GO=1;
            en_sh();
            if(GO==0) m[c1][c2]='A';
            sh();
            mvmnt_enemy();
            GW=1;
            GO=1;
            for(int i=1;i<=40;i++)
                for(int j=1;j<=31;j++)
                    {
                        if(m[i][j]=='T') GW=0;
                        if(m[i][j]=='A') GO=0;
                    }
        }
}

void rand_enemy(int e11, int e12, int nr)
{
    int ok,i,j,e21,e22;
    m[e11][e12]='T';
    nr--;
    if(nr>0)
    {
        ok=0;
        while(ok==0)
        {
            ok=1;
            e21=rand() % 10 + 1;
            for(i=1;i<=31;i++)
                if(m[e21][i]=='T')
                    {
                        e21=rand() % 10 + 1;
                        ok=0;
                    }
            e22=rand() % 31 + 1;
            for(i=1;i<=10;i++)
                if(m[i][e22]=='T')
                    {
                        e22=rand() % 31 + 1;
                        ok=0;
                    }
        }
        rand_enemy(e21,e22,nr);
    }
}

void game_dif(int dif)
{
    srand(time(NULL));
    int e11,e12,e21,e22;
    e11=rand() % 10 + 1;
    e12=rand() % 31 + 1;
    rand_enemy(e11,e12,dif*2);
    game_body();
}

void game_head()
{
    int dif,i,j; GO=0; GW=0;
    cout<<"Bun venit in lumea Space Invader, daca doriti sa jucati alegeti dificultatea."<<endl;
    cout<<"Apasati 1,2 sau 3 in functie de cat de greu doriti sa fie jocul iar apoi apasati tasta Enter."<<endl;
    cout<<"1:Usor"<<endl;
    cout<<"2:Mediu"<<endl;
    cout<<"3:Greu"<<endl;
    cin>>dif;
    for(i=1;i<=40;i++)
        for(j=1;j<=31;j++)
        m[i][j]=' ';
    m[c1][c2]='A';
    game_dif(dif);
}

int main()
{
    system("color 17");
    HWND hwnd=GetConsoleWindow();
    if(hwnd !=NULL) MoveWindow(hwnd,200,300,700,600,TRUE);
    game_head();
    if(GO==1&&GW==0) cout<<"Ai pierdut, apasa tasta 1 ca sa incerci din nou.";
    else if(GO==1&&GW==1) cout<<"Remiza, apasa tasta 1 ca sa incerci din nou.";
    else if(GO==0&&GW==1) cout<<"Ai castigat! Daca doresti sa joci din nou apasa tasta 1.";
    cout<<endl<<"Apasa tasta 2 pentru a iesi din joc.";
    int again;
    cin>>again;
    if(again==1) game_head();
    else if(again==2) exit(0);
}
