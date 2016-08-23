/* Source code for Sopwith
   Reverse-engineered by Andrew Jenner

   Copyright (c) 1984-2000 David L Clark
   Copyright (c) 1999-2001 Andrew Jenner

   All rights reserved except as specified in the file license.txt.
   Distribution of this file without the license.txt file accompanying is
   prohibited.
*/

void farmemmove(void far *src,void far *dest,int length);
void farmemset(void far *p,int length,char fill);
void writechar(char c);
void clearline(void);
void poscurs(int x,int y);
void setgmode(int m);
void inittimer(void (*f)(void));
void initkeyboard(void (*f)(void));
void restoreints(void);
unsigned int getwordfromport(int port);
int cgafbar(int x0,int y0,int w,int h,int c);
int getkey(void);
bool kbhit(void);
