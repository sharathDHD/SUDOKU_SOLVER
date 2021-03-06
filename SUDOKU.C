/*program to solve sudoku in graphics mode*/ 
#include < stdio.h>
#include < graphics.h >
int grid[9][9], fixed[9][9], g;
char ww[][8] = {
     { 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55  }, //0
     { 0xF0, 0xF0, 0xF0, 0xF0, 0x0F, 0x0F, 0x0F, 0x0F  }, //1
  };
int again() //to print out put screen
{
    int r, c, l, x, x2, y, yl, s, sp, y2 = getmaxy() / 2, m = getmaxy() / 2, one;
    char a[90], b[10], ones[10];
    clrscr();
    x2 = getmaxx() / 2;
    x = getmaxx() / 2 - 9;
    y = getmaxy() / 2 - 9;
    cleardevice();
    setcolor(4);
    //  printf("\n\n\n\n\t\t\t");

    setlinestyle(0, 0, 1);
    setfillpattern( & ww[0][0], RED);
   
    setcolor(15);
    rectangle(14, 14, getmaxx() - 10, getmaxy() - 10);
    setcolor(15);
    rectangle(getmaxx() / 2 - 90, getmaxy() / 2 - 90, getmaxx() / 2 + 90, getmaxy() / 2 + 90);
    settextstyle(4, 0, 4);
    outtextxy(100, 30, "SUDOKU");
    for (l = getmaxx() / 2 - 90; l < getmaxx() / 2 + 90; y2 = y2 + 20, l = l + 20) {
        line(l, m - 90, l, m + 90);
        line(x2 - 90, y2 - 90, x2 + 90, y2 - 90);
    }
    setcolor(1);
    setlinestyle(3, 5, 3);
    rectangle(getmaxx() / 2 - 95, getmaxy() / 2 - 95, getmaxx() / 2 + 95, getmaxy() / 2 + 95);
    settextstyle(2, 0, 4);
    for (y = getmaxy() / 2 - 85, r = 0; r < 9; r++, y = y + 20)
        for (x = getmaxx() / 2 - 80, c = 0; c < 9; c++, x = x + 20) {
            setcolor(4);
            sprintf(a, "%d", grid[r][c]);
            if (grid[r][c] == 0)
                outtextxy(x, y, " ");
            else
                outtextxy(x, y, a);
        }
    setcolor(15);
    outtextxy(460, getmaxy() - 60, "SOLVER BY:");
    setcolor(15);
    outtextxy(460, getmaxy() - 30, "SHARATH KUMAR");
    return (1);
}
void print_solution(g) //sol with outscreen
{
    static int nsol = 0;
    int k, k1, r, c, l, x, x2, y, yl, s, sp, y2 = getmaxy() / 2, m = getmaxy() / 2, one;
    char a[90], b[10], ones[10];
    clrscr();
    x2 = getmaxx() / 2;
    x = getmaxx() / 2 - 9;
    y = getmaxy() / 2 - 9;
    cleardevice();
    setcolor(4);
    setlinestyle(0, 0, 1);
    setfillpattern( & ww[0][0], 0);
    bar(15, 15, getmaxx() - 10, getmaxy() - 10);
   
    setcolor(15);
    rectangle(15, 15, getmaxx() - 10, getmaxy() - 10);
    rectangle(getmaxx() / 2 - 90, getmaxy() / 2 - 90, getmaxx() / 2 + 90, getmaxy() / 2 + 90);
    sprintf(b, "%d", ++nsol);
    settextstyle(4, 0, 4);
    outtextxy(200, 30, b);
    outtextxy(20, 30, "solution no:");
    setcolor(15);
    for (l = getmaxx() / 2 - 90; l < getmaxx() / 2 + 90; y2 = y2 + 20, l = l + 20) {
        line(l, m - 90, l, m + 90);
        line(x2 - 90, y2 - 90, x2 + 90, y2 - 90);
    }
    setcolor(1);
    setlinestyle(3, 5, 3);
    rectangle(getmaxx() / 2 - 95, getmaxy() / 2 - 95, getmaxx() / 2 + 95, getmaxy() / 2 + 95);
    settextstyle(2, 0, 4);
    setcolor(15);
    outtextxy(460, getmaxy() - 60, "SOLVER BY:");
    setcolor(15);
    outtextxy(460, getmaxy() - 30, "SHARATH KUMAR");
    for (y = getmaxy() / 2 - 85, r = 0; r < 9; r++, y = y + 20)
        for (x = getmaxx() / 2 - 80, c = 0; c < 9; c++, x = x + 20) {
            if (fixed[r][c] == grid[r][c])
                setcolor(4);
            else
                setcolor(GREEN);
            sprintf(a, "%d", grid[r][c]);
            outtextxy(x, y, a);
            delay(5);
        }
    getch();
    if (nsol >= g) {
        nsol = 0;
        getch();
        setcolor(15);

        outtextxy(40, getmaxy() - 50, "enter [1] to continue, other key to exit  :");
        take:
            scanf("%d", & one);
        sprintf(ones, "%d", one);
        outtextxy(350, getmaxy() - 50, ones);
        delay(100);
        if (one == 1) {
            for (k = 0; k < 9; k++)
                for (k1 = 0; k1 < 9; k1++) {
                    grid[k][k1] = fixed[k][k1] = 0;
                }

            clrscr();
            cleardevice();
            setbkcolor(0);
            call();
        } else {
            clrscr();
            cleardevice();
            exit(0);
        }
    }
    getch();
}
int safe(int row, int col, int n) {
    int r, c, br, bc;
    if (grid[row][col] == n) return 1;
    if (grid[row][col] != 0) return 0;
    for (c = 0; c < 9; c++)
        if (grid[row][c] == n) return 0;
    for (r = 0; r < 9; r++)
        if (grid[r][col] == n) return 0;
    br = row / 3;
    bc = col / 3;
    for (r = br * 3; r < (br + 1) * 3; r++)
        for (c = bc * 3; c < (bc + 1) * 3; c++)
            if (grid[r][c] == n) return 0;
    return 1;
}
void solve(int row, int col, int g) {
    int n, t;
    if (row == 9)
        print_solution(g);
    else
        for (n = 1; n <= 9; n++)
            if (safe(row, col, n)) {
                t = grid[row][col];
                grid[row][col] = n;
                if (col == 8)
                    solve(row + 1, 0, g);
                else
                    solve(row, col + 1, g);
                grid[row][col] = t;
            }
}
int main() {
    int gd = DETECT, gm;
    initgraph( & gd, & gm, "c:\\tc\\bgi");
    setbkcolor(0);
    textcolor(15);
    again(4);

    call();
    return (0);
}
int call() {
    int i, p, j, l, ck, m, n, s;
    char l2[81], m2[81], n2[81], g2[81];
    cleardevice();
    again();
    for (i = 0; i < 9; i++)
        for (j = 0; j < 9; j++) {
            grid[i][j] = 0;
        }
    for (s = 81; s > 1; s--) {
        row: if (p == 1) {
            p = 0;
            cleardevice();
            again();
        }
        setcolor(15);
        outtextxy(30, getmaxy() / 2 - 60, "enter row:");
        // printf("");
        scanf("%d", & n);
        sprintf(n2, "%d", n);
        outtextxy(130, getmaxy() / 2 - 60, n2);
        if (n - 1 >= 9) {
            fall: setcolor(15);
            outtextxy(450, getmaxy() / 2, "ENTER 0 - 9 only");
            getch();
            cleardevice();
            again();
            goto row;
        }
        if (n == 0) {
            s = 0;
            goto star;
        }
        setcolor(15);
        outtextxy(30, getmaxy() / 2 - 40, "enter column:");
        scanf("%d", & l);
        sprintf(l2, "%d", l);
        outtextxy(130, getmaxy() / 2 - 40, l2);
        if (l - 1 >= 9) {
            goto fall;
        }
        if (l == 0) {
            s = 0;
            goto star;
        }
        setcolor(15);
        outtextxy(30, getmaxy() / 2 - 20, "enter data:");
        scanf("%d", & m);
        sprintf(m2, "%d", m);
        outtextxy(130, getmaxy() / 2 - 20, m2);
        delay(50);
        if (m - 1 >= 9) {
            goto fall;
        }
        if (m == 0) {
            s = 0;
            goto star;
        }
        ck = check(m, n - 1, l - 1);
        if (ck == 1) {
            setcolor(15);
            outtextxy(getmaxx() / 2, getmaxy() - 70, "INCONSISTANT NUMABER");
            getch();
            cleardevice();
            again();
            goto row;
        } else
            grid[n - 1][l - 1] = m;
        again();
        p = 1;
        star:
    }
    for (i = 0; i < 9; i++)
        for (j = 0; j < 9; j++)
            fixed[i][j] = grid[i][j];
    cleardevice();
    again();
    setcolor(15);
    outtextxy(30, getmaxy() - 40, "enter how many number of sol u want:");
    scanf("%d", & g);
    delay(50);
    solve(0, 0, g);
    return 0;
}
int check(int data, int rown, int coln) {
    int sr = 0, sc = 0, ii = 0, gr = 0, gc = 0, jj = 0, smt = 0;
    smt = checkg(rown, coln);
    for (ii = 0; ii < 9; ii++) {
        if (grid[rown][ii] == data)
            return (1);
        if (grid[ii][coln] == data)
            return (1);
    }
    if (smt == 1) {
        sc = sr = 0;
    } else if (smt == 2) {
        sr = 0;
        sc = 3;
    } else if (smt == 3) {
        sr = 0;
        sc = 6;
    } else if (smt == 4) {
        sr = 3;
        sc = 0;
    } else if (smt == 7) {
        sr = 6;
        sc = 0;
    } else if (smt == 8) {
        sr = 6;
        sc = 3;
    } else if (smt == 6) {
        sr = 3;
        sc = 6;
    } else if (smt == 9) {
        sr = sc = 6;
    } else if (smt == 5) {
        sr = sc = 3;
    }
    gr = sr + 3;
    gc = sc + 3;
    for (ii = sr; ii < gr; ii++)
        for (jj = sc; jj < gc; jj++) {
            if (grid[ii][jj] == data)
                return (1);
        }
    return (0);
}
int checkg(rown, coln) {
    int st;
    if (rown < 9 && rown > 5) {
        if (coln < 9 && coln > 5)
            st = 9;
        else if (coln < 6 && coln > 2)
            st = 8;
        else if (coln < 3 && coln >= 0)
            st = 7;
    } else if (rown < 6 && rown > 2) {
        if (coln < 9 && coln > 5)
            st = 6;
        else if (coln < 6 && coln > 2)
            st = 5;
        else if (coln < 3 && coln >= 0)
            st = 4;
    } else if (rown < 3) {
        if (coln < 9 && coln > 5)
            st = 3;
        else if (coln < 6 && coln > 2)
            st = 2;
        else if (coln < 3 && coln >= 0)
            st = 1;
    }
    return (st);
}
