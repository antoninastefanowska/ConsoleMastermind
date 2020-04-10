#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <cstring>
using namespace std;
HANDLE hStdin=GetStdHandle(STD_INPUT_HANDLE);
HANDLE hStdout=GetStdHandle(STD_OUTPUT_HANDLE);
int tab1[4], tab2[4], punkty[10];
char nicki[10][10];
void rozmiar(int x, int y)
{
     COORD RozmiarBufora;
     RozmiarBufora.X=x;
     RozmiarBufora.Y=y;
     SMALL_RECT RozmiarOkna;
     RozmiarOkna.Left=0;
     RozmiarOkna.Top=0;
     RozmiarOkna.Right=x-1;
     RozmiarOkna.Bottom=y-1;
     SetConsoleScreenBufferSize(hStdout,RozmiarBufora);
     SetConsoleWindowInfo(hStdout,true,&RozmiarOkna);
     SetConsoleScreenBufferSize(hStdout,RozmiarBufora);
}
int gotoxy(int x, int y)
{
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void tekst(string s)
{
    int i;
    for (i=0; i<s.size(); i++)
    {
        cout<<s[i];
        _sleep(25);
    }
}
void losuj(int tab1[])
{
    
    int i, j;
    for (i=0; i<4; i++) 
    {
        tab1[i]=(int)rand()%6+1;
        for (j=0; j<4; j++) if ((i!=j)&&(tab1[i]==tab1[j])) i--;
    }
}
void wprowadz(ofstream &kombi1, int tab2[], int n)
{
    int i, j, k[4];
    char cyfra;
    bool e=false;
    blad:        
    ifstream kombi2("kombinacje.txt");         
    if (e)
    {
        gotoxy(6,n+2*(n+1)+2);
        cout<<"          Wprowadz ponownie!";
        e=false;
    }
    gotoxy(6,n+2*(n+1)+2);    
    for (i=0; i<4; i++)
    {
        cyfra=getch();
        tab2[i]=(int)cyfra-48;
        SetConsoleTextAttribute(hStdout,25+tab2[i]);
        if (((int)cyfra-48>6)||((int)cyfra-48<1))
        {
            SetConsoleTextAttribute(hStdout,23);                                                 
            e=true;
            goto blad;
        }        
        cout<<tab2[i]<<' ';
        SetConsoleTextAttribute(hStdout,23);
    }
    for (i=0; i<4; i++)
    {
        for (j=0; j<4; j++) if ((i!=j)&&(tab2[i]==tab2[j]))
        {
            e=true;
            goto blad;
        }
    }
    i=j=0;
    while (!kombi2.eof())
    {
        kombi2>>k[i];
        if (tab2[i]==k[i]) j++;
        i++;
        if (j==4)
        {
            e=true;
            goto blad;
        }
        if (i==4) i=j=0;        
    }
    for (i=0; i<4; i++) kombi1<<tab2[i]<<' ';
    kombi1<<endl; 
}
void porownaj(int tab1[], int tab2[], int &x, int &o, int &v, int n)
{
    int i, j;
    o=v=0;
    for (i=0; i<4; i++)
    {
        if (tab1[i]==tab2[i]) v++;
        for (j=0; j<4; j++) if (tab1[i]==tab2[j]) o++;
    }
    x=4-o;
    gotoxy(20,n+2*(n+1)+2);   
    cout<<"               "; 
    gotoxy(20,n+2*(n+1)+2);    
    _sleep(300);
    SetConsoleTextAttribute(hStdout,28);    
    for (i=0; i<=x; i++)
    {
        gotoxy(20,n+2*(n+1)+2);
        cout<<"X: "<<i;
        if (i>0) Beep(200,300);
    }
    SetConsoleTextAttribute(hStdout,30);
    for (i=0; i<=o; i++)
    {
        gotoxy(24,n+2*(n+1)+2);
        cout<<" O: "<<i;
        if (i>0) Beep(400,300);
    }
    SetConsoleTextAttribute(hStdout,26);
    for (i=0; i<=v; i++)
    {
        gotoxy(29,n+2*(n+1)+2);
        cout<<" V: "<<i;
        if (i>0) Beep(600,300);
    }  
    SetConsoleTextAttribute(hStdout,23);
    cout<<endl;
}
void wygrana(int i, int punkty[])
{
    string s;
    Beep(200,300);
    Beep(500,300);
    Beep(700,600);
    s="     Wygrana! \n     Wynik: ";
    tekst(s);
    cout<<i+1;
    if (i+1>=punkty[0])
    {
        s="\n     Najlepszy wynik: ";
        tekst(s);
        cout<<punkty[0];
        if (punkty[0]==1) s=" proba \n";
        if ((punkty[0]>1)&&(punkty[0]<5)) s=" proby \n";
        if (punkty[0]>=5) s=" prob \n";
        tekst(s);
    }
    else
    {
        s="\n     Nowy rekord! \n";
        tekst(s);
    }
}
void przegrana(int tab1[])
{
    string s;
    Beep(700,300);
    Beep(500,300);
    Beep(200,600);
    s="     Przegrana. \n     Prawidlowa kombinacja:\n     ";
    tekst(s);
    for (int i=0; i<4; i++) 
    {
        _sleep(500);
        SetConsoleTextAttribute(hStdout,25+tab1[i]);
        cout<<tab1[i]<<" ";      
    }
    _sleep(500);
    SetConsoleTextAttribute(hStdout,23);
    cout<<endl;
}
void baner()
{
    int i, j=0;
    string s="MASTERMIND";                          
    do
    {
        gotoxy(13,1);
        for (i=0; i<s.size(); i++)
        {    
            SetConsoleTextAttribute(hStdout,((int)rand()%6+26));
            cout<<s[i];
            if (j==0) _sleep(50);
        }
        if (j%3==0) Beep(200,500);
        if (j%3==1) Beep(400,500);
        if (j%3==2) Beep(600,500);
        j++;
    } while (!kbhit());
    SetConsoleTextAttribute(hStdout,23);
    gotoxy(0,4);
    getch();
}
void wynik(int n, int punkty[], char nicki[][10])
{
    int i, j, pkt1, pkt2;
    bool z=false;
    string s;
    char slowo1[10]={' '}, slowo2[10]={' '};
    ifstream wyniki1("wyniki.txt");
    s="\n     Podaj nick (max 10 znakow)\n     ";
    tekst(s);
    cin>>s;
    for (i=0; i<10; i++) 
    {
        if (i<=s.size()) slowo1[i]=s[i];
        else slowo1[i]=' ';
    }
    for (i=0; i<10; i++)
    {
        if ((n+1<punkty[i])&&(!z))
        {
              pkt1=n+1;
              z=true;
        }
        if (pkt1<=punkty[i])
        {
              pkt2=punkty[i];
              punkty[i]=pkt1;
              pkt1=pkt2;
              for (j=0; j<10; j++)
              {
                  slowo2[j]=nicki[j][i];
                  nicki[j][i]=slowo1[j];
                  slowo1[j]=slowo2[j];
              }
        }
    }
    ofstream wyniki("wyniki.txt");
    for (i=0; i<10; i++)
    {
        wyniki<<punkty[i]<<" ";
        for (j=0; j<10; j++) wyniki<<nicki[j][i];
        wyniki<<endl;
    }
}
void ranking(int punkty[], char nicki[][10], int &r)
{
    int i, j, key, k=0 ;
    char odp;
    string a="MENU", b="RESETUJ", s;
    for (i=0; i<10; i++)
    {
        gotoxy(1,i+2*(i+1)+2);
        cout<<i+1<<".";
        gotoxy(6,i+2*(i+1)+2);
        if (punkty[i]!=99) cout<<punkty[i];
        else cout<<"--";
        gotoxy(20,i+2*(i+1)+2);
        for (j=0; j<10; j++) cout<<nicki[j][i];
        _sleep(25);
        cout<<"\n____________________________________\n";
        _sleep(25);
    }
    gotoxy(6,i+2*(i+1)+2);
    tekst(a);
    gotoxy(20,i+2*(i+1)+2);
    tekst(b);
    while (key!=13)
    {
        if (k==0)
        {
           SetConsoleTextAttribute(hStdout,23);
           gotoxy(20,i+2*(i+1)+2);
           cout<<b;
           gotoxy(6,i+2*(i+1)+2);
           SetConsoleTextAttribute(hStdout,113);
           cout<<a;
        }
        if (k==1)
        {
           SetConsoleTextAttribute(hStdout,23);
           gotoxy(6,i+2*(i+1)+2);
           cout<<a;
           gotoxy(20,i+2*(i+1)+2);
           SetConsoleTextAttribute(hStdout,113);
           cout<<b;
        }
        do key=getch();
        while ((key!=13)&&(key!=75)&&(key!=77));
        if ((key==77)&&(k<1)) k++;
        if ((key==75)&&(k>0)) k--;
    }
    SetConsoleTextAttribute(hStdout,23);
    if ((key==13)&&(k==1))
    {
        gotoxy(4,i+2*(i+1)+4);
        s="Wymazac tabele wynikow? T/N";
        tekst(s);
        do odp=getch();
        while ((odp!='T')&&(odp!='t')&&(odp!='N')&&(odp!='n'));
        if ((odp=='T')||(odp=='t'))
        {
            ofstream wyniki("wyniki.txt");
            for (i=0; i<10; i++) wyniki<<99<<" "<<"----------"<<endl;
        }
    }
    for (i=4; i<40; i++)
    {
        gotoxy(0,i);
        cout<<"                                    ";
        _sleep(25);
    }
    r=1;
    gotoxy(0,4);                  
}
void menu(int &r)
{
    int key, i, k=0;
    string s, a="START", b="RANKING", c="KONIEC";
    gotoxy(6,4); 
    tekst(a);
    cout<<"\n____________________________________\n";
    _sleep(200);
    gotoxy(6,7);
    tekst(b);
    cout<<"\n____________________________________\n";
    _sleep(100);
    gotoxy(6,10);
    tekst(c);
    cout<<"\n____________________________________";
    _sleep(200);
    while (key!=13)
    {
        if (k==0)
        {
           SetConsoleTextAttribute(hStdout,23);
           gotoxy(6,7);
           cout<<b;
           gotoxy(6,10);
           cout<<c;
           gotoxy(6,4);
           SetConsoleTextAttribute(hStdout,113);
           cout<<a;
        }
        if (k==1)
        {
           SetConsoleTextAttribute(hStdout,23);
           gotoxy(6,4);
           cout<<a;
           gotoxy(6,10);
           cout<<c;
           gotoxy(6,7);
           SetConsoleTextAttribute(hStdout,113);
           cout<<b;
        }
        if (k==2)
        {
           SetConsoleTextAttribute(hStdout,23);
           gotoxy(6,4);
           cout<<a;
           gotoxy(6,7);
           cout<<b;
           gotoxy(6,10);
           SetConsoleTextAttribute(hStdout,113);
           cout<<c;
        }
        do key=getch();
        while ((key!=13)&&(key!=80)&&(key!=72));
        if ((key==80)&&(k<2)) k++;
        if ((key==72)&&(k>0)) k--;
    }
    SetConsoleTextAttribute(hStdout,23);
    for (i=4; i<20; i++)
    {
        gotoxy(0,i);
        cout<<"                                    ";
        _sleep(25);
    }
    gotoxy(0,4);
    if ((key==13)&&(k==1)) ranking(punkty,nicki,r);
    if ((key==13)&&(k==2)) r=2;
}       
void tabela(int punkty[], char nicki[][10])
{
    int i, j;
    ifstream wyniki("wyniki.txt");
    string slowo;
    for (i=0; i<10; i++) for (j=0; j<10; j++) nicki[j][i]=' ';
    for (i=0; i<10; i++)
    {
        wyniki>>punkty[i]>>slowo;
        for (j=0; j<slowo.size(); j++) nicki[j][i]=slowo[j];
    }
}  
int main()
{
    rozmiar(36,41);
    system("Color 17");
    int i, j, x, o, v, r;
    char odp;
    string s;
    s="\n\n____________________________________\n";
    tekst(s);
    baner();
    restart:         
    tabela(punkty,nicki);
    r=j=0;
    menu(r);
    if (r==1) goto restart;
    if (r==2) return 0;
    odnowa:
    ofstream kombi1("kombinacje.txt");           
    srand(time(NULL));
    losuj(tab1);
    gotoxy(0,4);
    for (i=0; i<10; i++)
    {
        cout<<" "<<i+1<<". ";
        wprowadz(kombi1,tab2,i);
        cout<<"             ";
        porownaj(tab1,tab2,x,o,v,i);
        s="____________________________________\n";
        tekst(s);
        if (v==4)
        {
            wygrana(i,punkty);
            if (i+1<punkty[9]) wynik(i,punkty,nicki);
            break;
        }
    }
    if (v!=4) przegrana(tab1);
    s="\n     Od nowa? T/N";
    tekst(s);
    do odp=getch();
    while ((odp!='T')&&(odp!='t')&&(odp!='N')&&(odp!='n'));
    for (i=4; i<40; i++)
    {
        gotoxy(0,i);
        cout<<"                                    ";
        _sleep(25);
    }
    if ((odp=='T')||(odp=='t')) goto odnowa;
    else goto restart;
}
