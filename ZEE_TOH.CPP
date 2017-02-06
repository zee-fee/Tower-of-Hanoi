#include<graphics.h>
#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
# define Y 20
union REGS in,out;
int n,delaytime,peg1[5],peg2[5],peg3[5],top1,top2=-1,top3=-1,val[5];


int callmouse()
 {
  in.x.ax=1;
  int86(51,&in,&out);
  return 1;
 }

void mouseposi(int &xpos,int &ypos,int &click)
 {
  in.x.ax=3;
  int86(51,&in,&out);
  click=out.x.bx;
  xpos=out.x.cx;
  ypos=out.x.dx;
 }


int mousehide()
 {
  in.x.ax=2;
  int86(51,&in,&out);
  return 1;
 }

void setposi(int &xpos,int &ypos)
 {
  in.x.ax=4;
  in.x.cx=xpos;
  in.x.dx=ypos;
  int86(51,&in,&out);
 }

struct peg
 {
  int pos,top,x1[6],y1[6],x2[6],y2[6];
 }source,dest,aux;

int pop(int peg[],int &top)
 {
  int disk;
  if(top!=-1)
   {
    disk=peg[top];
    top--;
   }
  return disk;
 }

void push(int disk,int peg[],int &top)
 {
  top++;
  peg[top]=disk;
 }

int check(int peg[],int top,int disk,peg a)
 {
  if(peg[top]<disk)
   {
    switch(a.pos)
     {
      case 0: push(disk,peg1,top1);
	      break;
      case 1: push(disk,peg2,top2);
	      break;
      case 2: push(disk,peg3,top3);
	      break;
     }
    return 1;
   }
  else
   return 0;
 }

void create(peg &p1,int &top1,peg &p2,int &top2)
 {
  int x,y;
  top2++;
  x=p1.x1[top1];
  y=p2.y1[top2-1];
  p2.y1[top2]=y-30;
  if(p1.pos==0&&p2.pos==2)
   p2.x1[top2]=x+430;
  else if(p1.pos==0&&p2.pos==1)
   p2.x1[top2]=x+215;
  else if(p1.pos==1&&p2.pos==2)
   p2.x1[top2]=x+215;
  else if(p1.pos==2&&p2.pos==1)
   p2.x1[top2]=x-215;
  else if(p1.pos==2&&p2.pos==0)
   p2.x1[top2]=x-430;
  else if(p1.pos==1&&p2.pos==0)
   p2.x1[top2]=x-215;
 }

void towerm();
void set();

void movedisk(int a,peg &from,peg &to,int mode)
 {
  mousehide();
  int x,y,size=val[a-1]*40,tx,ty,c,cl;
  char ch;
  x=from.x1[from.top];
  y=from.y1[from.top];
  do
   {
    setfillstyle(SOLID_FILL,BLACK);
    bar(x,y,x+size,y+Y);
    setfillstyle(SOLID_FILL,BLUE);
    bar(x+size/2-5,y,x+size/2+5 ,y+Y);
    y-=30;
    setfillstyle(SOLID_FILL,10+n-a);
    bar(x,y,x+size,y+Y);
    delay(delaytime);
   }while(y>60);
  tx=to.x1[to.top];
  do
   {
    setfillstyle(SOLID_FILL,BLACK);
    bar(x,y,x+size,y+Y);
    if(tx<x) x-=43; else x+=43;
    setfillstyle(SOLID_FILL,10+n-a);
    bar(x,y,x+size,y+Y);
    delay(delaytime);
   }while(x!=tx);
 ty=to.y1[to.top];
 int j=0;
 do
  {
   setfillstyle(SOLID_FILL,BLACK);
   bar(x,y,x+size,y+Y);
   if(j>0)
    {
     setfillstyle(SOLID_FILL,BLUE);
     bar(x+size/2-5,y,x+size/2+5 ,y+Y);
    }
   y+=30;
   setfillstyle(SOLID_FILL,10+n-a);
   bar(x,y,x+size,y+Y);
   delay(delaytime);
   j++;
  }while(y<ty);

  if(mode==1)
  {
  c=getch();
  if (c=='x')
   {
   callmouse();
   int u=100,v=100;
   setposi(u,v);
  do
   {
   mouseposi(x,y,cl);
   gotoxy(10,9);
   if(cl==1&&x>=550&&x<=600&&y>=324&&y<=346)
    exit(1);
   if(cl==1&&x>=3&&x<=170&&y>=324&&y<=346)
   {
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(200,335,500,357);
    outtextxy(210,330,"YOU ARE IN MANNUAL MODE");
    delay(1000);
    setfillstyle(SOLID_FILL,BLACK);
    bar(200,335,510,357);
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(200,325,510,370);
    outtextxy(210,326,"FIRST CLICK ON SOURCE PEG");
    outtextxy(210,350,"THEN CLICK ON DESTINATION PEG");
    delay(1000);
    setfillstyle(SOLID_FILL,BLACK);
    bar(200,325,510,370);
    from.top--;
    towerm();
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(200,324,500,400);
    outtextxy(240,330,"DO YOU WANT TO RESET?");
    setfillstyle(SOLID_FILL,BLUE);
    bar(250,365,320,390);
    setcolor(WHITE);
    outtextxy(268,368,"YES");
    setfillstyle(SOLID_FILL,BLUE);
    bar(380,365,450,390);
    setcolor(WHITE);
    outtextxy(399,368,"NO");
    do
     {
     mouseposi(x,y,cl);
     if(cl==1&&x>=250&&x<=320&&y>=365&&y<=390)
      {
      mousehide();
      cleardevice();
      delay(1000);
      set();
      }
     else if(cl==1&&x>=380&&x<=450&&y>=365&&y<=390)
     exit(1);
     }while(!kbhit());
   }
   } while(!kbhit());
  }
  }
  callmouse();
  int u=100,v=400;
  setposi(u,v);
  delay(1000);
}


void towerm()
 {
  int x,y,cl,flag=0,disk,ch,a=100,b=400;
  peg *s,*d;
  callmouse();
  setposi(a,b);
  do
   {
    mouseposi(x,y,cl);
    gotoxy(10,9);
    if(cl==1&&x>=550&&x<=600&&y>=324&&y<=346)
    exit(1);
    else if(cl==1&&x>=100&&x<=110&&y>=100&&y<=300)
     {s=&source;flag=1;disk=pop(peg1,top1);}
    else if(cl==1&&x>=315&&x<=325&&y>=100&&y<=300)
     {s=&aux;flag=1;disk=pop(peg2,top2);}
    else if(cl==1&&x>=530&&x<=540&&y>=100&&y<=300)
     {s=&dest;flag=1;disk=pop(peg3,top3);}
   }while(flag==0);

  flag=0;
  setposi(a,b);
  callmouse();
  do
   {
    mouseposi(x,y,cl);
    gotoxy(10,9);
    if(cl==1&&x>=550&&x<=600&&y>=324&&y<=346)
     exit(1);
    else if(cl==1&&x>=100&&x<=110&&y>=100&&y<=300)
     {
      d=&source;flag=1;
      ch=check(peg1,top1,disk,*s);
      if(ch==0)
      push(disk,peg1,top1);
     }
    else if(cl==1&&x>=315&&x<=325&&y>=100&&y<=300)
     {
      d=&aux;flag=1;
      ch=check(peg2,top2,disk,*s);
      if(ch==0)
      push(disk,peg2,top2);
     }
    else if(cl==1&&x>=530&&x<=540&&y>=100&&y<=300)
     {
      d=&dest;flag=1;
      ch=check(peg3,top3,disk,*s);
      if(ch==0)
      push(disk,peg3,top3);
     }
   }while(flag==0);
  if(ch==0)
   {
    create(*s,s->top,*d,d->top);
    movedisk(disk,*s,*d,0);
    s->top--;
   }
  else
   {
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(200,335,400,357);
    outtextxy(210,330,"Invalid Move");
    delay(1000);
    setfillstyle(SOLID_FILL,BLACK);
    bar(200,335,400,357);
   }
  setposi(a,b);
  if(top3!=n-1)
  {
  towerm();
  }
  else
  {
  setfillstyle(SOLID_FILL,LIGHTGRAY);
  bar(200,335,300,357);
  outtextxy(220,330,"SOLVED");
  delay(1000);
  setfillstyle(SOLID_FILL,BLACK);
  bar(200,335,400,357);
  }
 }

void update(peg from, peg to)
 {
  int disk;
  switch(from.pos)
  {
  case 0 : disk=pop(peg1,top1);break;
  case 1 : disk=pop(peg2,top2);break;
  case 2 : disk=pop(peg3,top3);break;
  }
  switch(to.pos)
  {
  case 0 : push(disk,peg1,top1);break;
  case 1 : push(disk,peg2,top2);break;
  case 2 : push(disk,peg3,top3);break;
  }
 }


void tower(int n,peg &from,peg &to,peg &aux)
 {
  if(n==1)
   {
    create(from,from.top,to,to.top);
    update(from,to);
    movedisk(1,from,to,1);
    from.top--;
    return;
   }
  tower(n-1,from,aux,to);
  create(from,from.top,to,to.top);
  update(from,to);
  movedisk(n,from,to,1);
  from.top--;
  tower(n-1,aux,to,from);
 }

int main();
void set()
{
  int i;
  char ch;
  settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
  setbkcolor(BLACK);
  setfillstyle(SOLID_FILL,LIGHTGRAY);
  bar(150,13,490,33);
  bar(30,324,170,346);
  bar(550,324,600,346);
  bar(30,355,170,377);
  setcolor(RED);
  outtextxy(180,10,"T O W E R  O F  H A N O I");
  setcolor(BLUE);
  outtextxy(60,321,"MANUAL");
  setcolor(BLUE);
  outtextxy(555,321,"EXIT");
  setcolor(BLUE);
  outtextxy(60,356,"COMPUTER");
  setfillstyle(SOLID_FILL,BLUE);
  bar(100,100,110,300);
  bar(315,100,325,300);
  bar(530,100,540,300);
  bar(0,300,640,310);
  for(i=0;i<5;i++)
  {
   source.x1[i]=5+20*i;
   source.y1[i]=270-30*i;
   source.x2[i]=205-20*i;
   source.y2[i]=290-30*i;
  }
  source.y1[-1]=300;
  dest.y1[-1]=300;
  aux.y1[-1]=300;
  source.pos=0;
  aux.pos=1;
  dest.pos=2;
  source.top=n-1;
  dest.top=-1;
  aux.top=-1;
  int z=5;
  for(i=n-1;i>=0;i--)
  val[i]=z--;
  for(i=0;i<n;i++)
   {
    setfillstyle(SOLID_FILL,10+i);
    bar(source.x1[i],source.y1[i],source.x2[i],source.y2[i]);
   }
  top1=n-1;
  for(i=0;i<n;i++)
  peg1[i]=n-i;
  peg2[-1]=10;
  peg3[-1]=10;
  int x,y,cl,a,b;
  a=100;
  b=400;
  setposi(a,b);
  callmouse();
  do
   {
    mouseposi(x,y,cl);
    gotoxy(10,9);
    if(cl==1&&x>=550&&x<=600&&y>=324&&y<=346)
    exit(1);
    else if(cl==1&&x>=30&&x<=170&&y>=355&&y<=377)
    tower(n,source,dest,aux);
    else if(cl==1&&x>=30&&x<=170&&y>=324&&y<=346)
     {
       setfillstyle(SOLID_FILL,LIGHTGRAY);
       bar(200,335,500,357);
       outtextxy(210,330,"YOU ARE IN MANNUAL MODE");
       delay(1000);
       setfillstyle(SOLID_FILL,BLACK);
       bar(200,335,510,357);
       setfillstyle(SOLID_FILL,LIGHTGRAY);
       bar(200,325,510,370);
       outtextxy(210,326,"FIRST CLICK ON SOURCE PEG");
       outtextxy(210,350,"THEN CLICK ON DESTINATION PEG");
       delay(1000);
       setfillstyle(SOLID_FILL,BLACK);
       bar(200,325,510,370);
       towerm();
     }

   }while(!kbhit());
  cleardevice();
  cout<<"Do you want to play again?"<<endl;
  cin>>ch;
  if(ch=='y'||ch=='Y')
  main();
  else
  {
   mousehide();
   closegraph();
   return;
  }

}

int main()
 {
  int gd=DETECT,gm,errorcode;
  do
   {
     printf("\nEnter no. of disks :-limit(1-5):-  ");
     scanf("%d",&n);
   }while((n<1)&&(n>5));
  delaytime=100;
  initgraph(&gd,&gm,"C://TURBOC3//BGI");
  errorcode = graphresult();
  if (errorcode != grOk)
  {
   printf("Graphics error: %s\n", grapherrormsg(errorcode));
   printf("Press any key to halt:");
   getch();
   exit(1);
  }
  set();
  return 0;
 }

