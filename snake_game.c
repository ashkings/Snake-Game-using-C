#include<stdio.h>
#include <conio.h>
#include<stdlib.h>
#include<string.h>
char mat[20][60];
FILE *fp ;
int score=0;
struct snake
{
    int x,y;
    char val;
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
int create_food(int x,int y)
{
    char *f=malloc(10*sizeof(char));
    if(x==0&&y==0)
     x=(rand()%(20-1))+(1),y=(rand()%(60-1))+(1);
      if(mat[x][y]=='*'||mat[x][y]=='#'||mat[x][y]=='P') create_food(0,0);
      else
    {
     mat[x][y]='F';
     return(x*100+y);
    }
}
int create_poison(int x,int y)
{
    if(x==0&&y==0)
      x=(rand()%(20-1))+(1),y=(rand()%(60-1))+(1);
      if(mat[x][y]=='*'||mat[x][y]=='#'||mat[x][y]=='F') create_poison(0,0);
      else
      {
          mat[x][y]='P';
          return(x*100+y);
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
int for_sum(char c)
{
    int r,sum=0;
    while(c!=',')
     {
      r=c-48;
      sum=sum*10+r;
      c=getc(fp);
      }
      return sum;
}
char to_skip(char c)
{
    while(c!='\n')
     {
      c=getc(fp);
     }
     c=getc(fp);
     return c;
}
int get_high_score()
{
    int high;
   fp=fopen("score.txt","r");
   char ch=getc(fp);
   if(ch==EOF) high=0;
   else
   {
    high=for_sum(ch);
   }
   return high;
}
int pboard()
{
    int i,j;
    int High=get_high_score();
    system("cls");
    printf("High Score %d\t\t\tYour Score %d\n",High,score);
    for(i=0;i<20;i++)
    {
        for(j=0;j<60;j++)
        {
            printf("%c",mat[i][j]);
        }
        printf("\n");
    }
    return High;
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
void create_score()
{
    score=score+3;
}
void del_score()
{
    score=score/2;
}
int check(int a,int b)
{
    if(mat[a][b]=='*'||mat[a][b]=='T')
        return 1;
}
void save_game(struct snake *t,int f,int p)
{
    if(t==NULL)
    {
        fp=fopen("save.txt","a++");
        fprintf(fp,"%d,%c\n",f,mat[f/100][f%100]);
        fprintf(fp,"%d,%c\n",p,mat[p/100][p%100]);
        return;
    }
    else
    {
        struct snake *temp=t;
        save_game(t->next,f,p);
        fp=fopen("save.txt","a++");
        fprintf(fp,"%d,%d,%c\n",temp->x,temp->y,mat[temp->x][temp->y]);
        fclose(fp);
    }
}
int for_food(int a,int b,int f)
{
    if(mat[a][b]=='F')
     {
      create_score();
      ins(a,b);
      f=create_food(0,0);
     }
     return f;
}
int for_poison(int a,int b,int p)
{
    if(mat[a][b]=='P')
    {
      del_score();
      shift();
      p=create_poison(0,0);
    }
    return p;
}
void scre(int h)
{
    char s[]="High Score";
    if(score>h)
     {
         fp=fopen("score.txt","w");
      fprintf(fp,"%d,%s\n",score,s);
      printf("Congratulations You Have Made High Score");
      fclose(fp);
     }
    else
     {
      printf("Your Score %d",score);
     }
}
void option(int x,int y,int f,int p)
{
    int c,flag=0;
    static int a;
    static int b;
    prin_snak();
    int h=pboard();
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
                    break;
                }
            case 'q':
                {
                    fp=fopen("save.txt","w");
                    fclose(fp);
                    save_game(head,f,p);
                    break;
                }
            }
            if(ch=='a'||ch=='w'||ch=='s'||ch=='d')
            {
             c=check(a,b);
             ins(a,b);
             f=for_food(a,b,f);
             p=for_poison(a,b,p);
            }
            if(c==1)
            {
                scre(h);
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
void for_save_game()
{
    int p,f,a,b;
      char c;
      fp=fopen("save.txt","r");
      c=getc(fp);
      if(c==EOF) printf("NO SAVED GAME");
      else
        {
         while(c!='H')
          {
            a=for_sum(c);
            c=getc(fp);
             b=for_sum(c);
             ins(a,b);
             c=getc(fp);
             if(c=='T'||c=='*')
              {
                  c=to_skip(c);
              }
            }
            c=getc(fp);
            c=getc(fp);
            while(c!='P')
             {
                f=for_sum(c);
                c=getc(fp);
                if(c=='F')
                {
                    c=to_skip(c);
                }
                p=for_sum(c);
                 c=getc(fp);
            }
            f=create_food(f/100,f%100);
            p=create_poison(p/100,p%100);
            option(a,b,f,p);
        }
}
void for_new_game()
{
    int a,b,f,p,i;
    a=10,b=20;
    for(i=0;i<4;i++)
     {
      cr_sn(a,b);
      b=b+1;
      }
    f=create_food(0,0);
    p=create_poison(0,0);
    option(a,b-1,f,p);
}
void create_matrix()
{
    int i,j;
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
}
int main()
{
    int choice;
    create_matrix();
        printf("\t\t\tWelcome To The Snake Game\n\n\tInformation About The Game\n\n\n\tPress 1 to start a new game\n\tPress 2 to start previously saved game\n");
        printf("\tPress 'a' to move left\n\tPress 'd' to move right\n\tPress 's' to move down\n\tPress 'w' to move up\n");
        printf("\tEat F to increase length\n\tCaution length decreases if you eat P\n");
        scanf("%d",&choice);
        if(choice==1)
        {
          for_new_game();
        }
        else if(choice==2)
        {
            for_save_game();
        }
        return 0;
}
