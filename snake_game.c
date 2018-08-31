#include<stdio.h>
#include <conio.h>
#include<stdlib.h>
char mat[20][60];
struct snake
{
    int x,y;
struct  snake *next;
};
struct snake *head=NULL;
struct snake *create(int a,int b)
{
    struct snake *ptr=(struct snake*)malloc(10000*sizeof(struct snake));
    ptr->x=a;
    ptr->y=b;
    ptr->next=NULL;
    return(ptr);
}
void create_food()
{
    int x=(rand()%(20-1))+(1),y=(rand()%(60-1))+(1);
    if(x>0&&x<20||y>0&&y<80)
    {
      if(mat[x][y]=='*'||mat[x][y]=='#'||mat[x][y]=='P') create_food();
      else mat[x][y]='F';
    }
}
void create_poison()
{
    int x=(rand()%(20-1))+(1),y=(rand()%(60-1))+(1);
    if(x>0&&x<20||y>0&&y<80)
    {
      if(mat[x][y]=='*'||mat[x][y]=='#'||mat[x][y]=='F') create_poison();
      else mat[x][y]='P';
    }
}
void ins(int x,int y)
{
    struct snake *temp;
    temp=create(x,y);
    if(head==NULL)
    {
        head=temp;
    }
    else
    {
     temp->next=head;
     head=temp;
    }
}
void cr_sn(int x,int y)
{
    ins(x,y);
}
void prin_snak()
{
 struct snake *t;
 t=head;
 mat[head->x][head->y]='H';
 t=t->next;
      while(t->next!=NULL)
     {
         mat[t->x][t->y]='*';
         t=t->next;
     }
     mat[t->x][t->y]='T';
     t=head;
}
void pboard()
{
    int i,j;
    printf("Welcome To The Snake Game\nPress 'a' to move left\nPress 'd' to move right\nPress 's' to move down\nPress 'w' to move up\n");
    printf("Eat F to increase length\nCaution length decreases if you eat P\n");
    for(i=0;i<20;i++)
    {
        for(j=0;j<60;j++)
        {
            printf("%c",mat[i][j]);
        }
        printf("\n");
    }
}
void shift()
{
    struct snake *t,*temp;
    t=head;
        while(t->next!=NULL)
        {
            temp=t;
            t=t->next;
        }
    temp->next=NULL;
    mat[t->x][t->y]=' ';
}
int check(int a,int b)
{
    if(mat[a][b]=='*'||mat[a][b]=='T')
        return 1;
}
void option(int x,int y)
{
    int c;
    static int a;
    static int b;
    a=x;
    b=y;
    char ch;
        while(1)
        {
             ch=getch();
            switch(ch)
            {
            case 'a':
                {
                    shift();
                    b=b-1;
                    if(b==0)
                    {
                      b=58;
                    }
                    ins(a,b);
                    c=check(a,b);
                    break;
                }
            case 'd':
                {
                    shift();
                    b=b+1;
                    if(b==59)
                    {
                        b=1;
                    }
                    ins(a,b);
                    c=check(a,b);
                    break;
                }
            case 's':
                {
                    shift();
                    a=a+1;
                    if(a==19)
                    {
                        a=1;
                    }
                    ins(a,b);
                    c=check(a,b);
                    break;
                }
            case 'w':
                {
                    shift();
                    a=a-1;
                    if(a==0)
                    {
                        a=18;
                    }
                    ins(a,b);
                    c=check(a,b);
                    break;
                }
            }
            if(mat[a][b]=='F')
            {
                ins(a,b);
                create_food();
            }
            else if(mat[a][b]=='P')
            {
                shift();
                create_poison();
            }
            if(c==1)
            {
                printf("\n\n*************GAME OVER*************");
                break;
            }
            else
            {
             system("cls");
             prin_snak();
             pboard();
            }
        }
}
int main()
{
    int i=0,j=0;
        for(i=0;i<20;i++)
        {
            for(j=0;j<60;j++)
            {
                if(i==0||j==0||j==59||i==19)
                {
                    mat[i][j]='#';
                }
                else
                {
                    mat[i][j]=' ';
                }
            }
        }
        int a=10,b=20;
        for(i=0;i<4;i++)
        {
         cr_sn(a,b);
         b=b+1;
        }
        create_food();
        create_poison();
        prin_snak();
        pboard();
        option(a,b-1);
        return 0;
}
