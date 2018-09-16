#include <stdio.h>
#include<conio.h>`
int grid[9][9],fixed[9][9],g;

  void print_solution(g)
 {
   static int nsol = 0;
   int k,k1,r,c,l,x,x2,y,yl,s,sp,one;
   char a[90],b[10],ones[10];
 
     clrscr();
      textcolor(15);
        printf("solution no: %d\n", ++nsol);
         
		 for(k=0;k<9;k++)
           {
             for(k1=0;k1<9;k1++)
                {
                   if(fixed[k][k1]==grid[k][k1])
                          textcolor(4);
                   else
                         textcolor(15);

                 printf("|%d| ",grid[k][k1]);
                }
             printf("\n");
            }
  
     getch();

          if(nsol>=g)
           {
        	   nsol=0;
               getch();
               printf("enter [1] to continue, other key to exit  :");
take:
               scanf("%d",&one);
               delay(100);
              
			  if(one==1)
                {
                   for(k=0;k<9;k++)
                      for(k1=0;k1<9;k1++)
                          grid[k][k1]=fixed[k][k1]=0;
                  clrscr();
                  call();
                }
              else
                {
                 clrscr();
                   exit(0);
                }
            }
        getch();
    }
 
 int safe(int row,int col,int n)
   {
      int r,c,br,bc;
      
	  if(grid[row][col]==n)
		  return 1;
      if(grid[row][col]!=0)
		  return 0;
      for(c=0;c<9;c++)
        if(grid[row][c]==n) 
			return 0;
      for(r=0;r<9;r++)
        if(grid[r][col]==n)
			return 0;
     br=row/3;
     bc=col/3;
     for(r=br*3;r<(br+1)*3;r++)
        for(c=bc*3;c<(bc+1)*3;c++)
	     if(grid[r][c]==n)
			 return 0;
     return 1;
    }
 
 void solve(int row, int col,int g)
  {
	  int n,t;
    
	if(row==9)
        print_solution(g);
    else
       for(n=1;n<=9;n++)
	      if(safe(row,col,n)) 
		    {
	           t=grid[row][col];
	            grid[row][col]=n;
	            if(col==8)
	                solve(row+1,0,g);
	            else
	                solve(row,col+1,g);
	           grid[row][col]=t;
            }
    }
 
 int main()
  {

    call();
     return(0);
  }

  int call()
   {
     int i,p,j,l,ck,m,n,s;
     char l2[81],m2[81],n2[81],g2[81];
 
      clrscr();

     for(i=0;i<9;i++)
        for(j=0;j<9;j++)
           {
             grid[i][j]=0;
            }
      for(s=81;s>1;s--)
        {
 
row:      if(p==1)
 	       {
 			  p=0;
 	          clrscr();
 
	       }

          printf("enter row:");
           scanf("%d",&n);

          if(n-1>=9)
           {
 
 fall:
             textcolor(4);
             printf("\nENTER 0 - 9 only");
             textcolor(15);
             getch();
             clrscr();
             goto row;
           }
          if(n==0)
           {
             s=0;
             goto star;
           }
          printf("\nenter column:");
          scanf("%d",&l);
          if(l-1>=9)
           {
              goto fall;
           }
          if(l==0)
           {
             s=0;
             goto star;
            }
          printf("\nenter data:");
          scanf("%d",&m);
          delay(50);
          if(m-1>=9)
           {
             goto fall;
           }
         if (m==0)
          {
            s=0;
            goto star;
          }
         ck=check(m,n-1,l-1);
         if(ck==1)
          {
             textcolor(4); 
             printf("INCONSISTANT NUMABER");
 
             textcolor(15);
             getch();
             clrscr();
             goto row;
          }
          else
             grid[n-1][l-1]=m;
    
          p=1;
          star:
        }
     for(i=0;i<9;i++)
        for(j=0;j<9;j++)
          {
             fixed[i][j]=grid[i][j];
          }
      clrscr();
      printf("\nenter how many number of sol u want:");
      scanf("%d",&g);
      delay(50);
      solve(0,0,g);
      return 0;
   }
 
   int check( int data, int rown,int coln)
    {
         int sr=0,sc=0,ii=0,gr=0,gc=0,jj=0,smt=0;

		 smt=checkg(rown,coln);

		 for(ii=0;ii<9;ii++)
           {
             if(grid[rown][ii]==data)
                      return(1);
             if(grid[ii][coln]==data)
                      return(1);
           }
         if(smt==1)
           {
             sc=sr=0;
           }
         else if(smt==2)
           {
             sr=0;
             sc=3;
           }
         else if(smt==3)
           {
             sr=0;
             sc=6;
           }
         else if(smt==4)
          { 
            sr=3;
            sc=0;
          }
         else if(smt==7)
          {
            sr=6;
            sc=0;
          }
         else if(smt==8)
          {
            sr=6;
            sc=3;
          }
         else if(smt==6)
          {
            sr=3;
            sc=6;
          }
         else if(smt==9)
          {
            sr=sc=6;
          }
         else if(smt==5)
          {
            sr=sc=3;
          } 
         gr=sr+3;
         gc=sc+3;
         for(ii=sr;ii<gr;ii++)
            for(jj=sc;jj<gc;jj++)
             {
                if(grid[ii][jj]==data)
                return(1);
             }
         return(0);
   } 
 
 int checkg(rown,coln)
  {
    int st ;

	if(rown<9&&rown>5)
      {
        if(coln<9&&coln>5)
           st=9;
        else if(coln<6&&coln>2)
           st=8;
        else if(coln<3&&coln>=0)
           st=7;
      }
    else if(rown<6&&rown>2)
      {
         if(coln<9&&coln>5)
           st=6;
         else if(coln<6&&coln>2)
           st=5;
         else if(coln<3&&coln>=0)
           st=4;
      }
    else if(rown<3)
     {
         if(coln<9&&coln>5)
           st=3;
         else if(coln<6&&coln>2)
           st=2;
         else if(coln<3&&coln>=0)
           st=1;
     }
   return(st);
 }








