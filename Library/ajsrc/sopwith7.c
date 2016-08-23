/* Source code for Sopwith

   Copyright (c) 1984-2000 David L Clark
   Copyright (c) 1999-2001 Andrew Jenner

   All rights reserved except as specified in the file license.txt.
   Distribution of this file without the license.txt file accompanying is
   prohibited.
*/

#include "def7.h"

typedef struct tonetable {                /*  Continuous tone table entry */
  unsigned int tone;
  unsigned int change;
  struct tonetable *next;
  struct tonetable *prev;
} tonetable;

typedef struct object {
  int state;
  int x,y,xv,yv,angle;
  int subtype;
  bool inverted;
  int speed,accel,flaps;
  bool firing;
  int score,ammo;
  int hitcounter;
  int life;
  struct object* owner;
  int height;
  int width;
  bool bombing;
  int bombs;
  int colour;
  int xfrac,yfrac;
  int xvfrac,yvfrac;
  struct object* next;
  struct object* prev;
  int index;
  int oldx;
  int oldy;
  bool drawflag;
  bool deleteflag;
  char* oldsprite;
  void (*display_func)(struct object* obj);
  bool (*update_func)(struct object* obj);
  struct object* nextx;
  struct object* prevx;
  int crashes;
  char* sprite;
  int bomb_delay;
  bool goinghome;
  int type;
  bool athome;
  tonetable* tonetab;
  int missiles;
  struct object* missile_target;
  int missile_delay;
  struct object* target;
  int starbursts;
  int starburst_firing;
  int starburst_delay;
} object;

typedef struct {                                /*  Communications buffer   */
  unsigned maxplayers;
  unsigned players;
  unsigned lastplayer;
  unsigned keys[MAX_PLYR];
  unsigned states[MAX_PLYR];
  unsigned randv;
} netbuffer;

typedef struct {            /* Old display parameters for each object */
  int ow_xorplot;
  int ow_x,ow_y;
} OLDWDISP;

bool    goinghome;              /*  Going home flag               */
object obs;                     /*  Saved computer object         */
int     courseadj;              /*  Course adjustment             */

object* killed[MAX_OBJS<<1];
object* killer[MAX_OBJS<<1];
int     killptr;

int     collsdx[MAX_PLYR];
int     collsdy[MAX_PLYR];
object* collsno[MAX_PLYR];
int     collptr;
int     collxadj, collyadj;

int     savescore;             /* save players score on restart  */
bool    ghost;                 /* ghost display flag             */

int     playmode;                       /* Mode of play                     */
object* targets[MAX_TARG+MAX_OXEN];    /* Status of targets array          */
int     numtarg[2];                     /* Number of active targets by color*/
int     counttick,countmove;           /* Performance counters             */
int     movetick;              /* Move timing                      */

int     level;                        /* Current game number              */
int     gmaxspeed,gminspeed;           /* Speed range based on game number */
int     targetrange;                       /* Target range based on game number*/

int     multkey;                        /* Keystroke to be passed           */
netbuffer netbuf;

int dispseg,dispoff,disproff;
char    auxdisp[0x2000];
char grndsave[SCR_WIDTH]

int     multtick;                       /* Multiple user tick delay         */
bool    disppos;                        /* Display position flag            */
int     dispdbg;                        /* Debug value to display           */
bool    soundflg=TRUE;                  /* Sound flag                       */
bool    joystick;                       /* Joystick being used              */
bool    ibmkeyboard;                       /* IBM-like keyboard being used     */
bool    inplay;                         /* Game is in play                  */
int     koveride;                       /* Keyboard override index number   */
int     missok;                         /* Missiles supported               */

int     displx,disprx;                 /* Display left and right           */
int     dispdx;                         /* Display shift                    */
bool    dispinit;                       /* Inialized display flag           */

object* drawlist;                      /* Onscreen object list             */
object* nobjects;                      /* Objects list.                    */
object oobjects[MAX_PLYR];             /* Original plane object description*/
object* objbot;
object* objtop;               /* Top and bottom of object list    */
object* objfree;                       /* Free list                        */
object* deltop;
object* delbot;               /* Newly deallocated objects        */
object topobj,botobj;                 /* Top and Bottom of obj. x list    */

object* compnear[MAX_PLYR];            /* Planes near computer planes      */

object* objsmax=NULL;      /* Maximum object allocated         */
int     endsts[MAX_PLYR];               /* End of game status and move count*/
int     endcount=1;
int     playerindex=0;                       /* Pointer to player's object       */
int     currobx;                        /* Current object index             */
bool    planeisplayer;                      /* Current object is player flag    */
bool    compplane;                      /* Current object is a comp plane   */
OLDWDISP wdisp[MAX_OBJS];               /* World display status             */
bool    goingsun;                       /* Going to the sun flag            */
bool    forcdisp;                       /* Force display of ground          */
char* histin;
char* histout;              /* History input and output files   */
long int randv;                      /* random seed for explosion        */

int     keydelay=-1;                    /* Number of displays per keystroke */
int     dispcnt;                        /* Displays to delay keyboard       */
int     endstatus;                        /* End of game status for curr. move*/
int     maxcrash;                       /* Maximum number of crashes        */
int     shothole;                       /* Number of shot holes to display  */
int     splatbird;                      /* Number of slatted bird symbols   */
int     splatox;                        /* Display splatted ox              */
bool     oxsplatted;                     /* An ox has been splatted          */

int sintab[ANGLES]={           /* sine table of pi/8 increments times 0x100 */
  0x000, 0x062, 0x0b5, 0x0ed, 0x100, 0x0ed, 0x0b5, 0x062,
  0x000,-0x062,-0x0b5,-0x0ed,-0x100,-0x0ed,-0x0b5,-0x062};

bool quit;
bool multiplayer,truemultiplayer;

int      soundtype=32767;      /*  Current sound type and          */
int      soundparm=32767;      /*     and priority parameter       */
object* soundobj=NULL;         /*  Object making sound             */
unsigned lastfreq=0;          /*  Last frequency used             */
object* lastobj=NULL;        /*  Previous object making sound    */
void (*toneadj)(void)=NULL;  /*  Tone adjustment on clock tick   */

tonetable tonetab[SNDSIZE];       /*  Continuous tone table           */
tonetable* frsttone;
tonetable* freetone;      /*  Tone list and free list         */
unsigned soundticks;             /*  Ticks since last sound selection*/

int      numexpls;               /*  Number of explosions currently  */
                                 /*  active                          */
int      explplace;              /*  Place in explosion tune;        */
int      explline;               /* Line in explosion tune           */
unsigned expltone;               /*  Current explosion tone          */
int      explticks;              /*  Ticks until note change         */
int      exploctv;               /*  Octave                          */
char     *expltune[]={
  "b4/d8/d2/r16/c8/b8/a8/b4./c4./c+4./d4./",
  "e4/g8/g2/r16/>a8/<g8/e8/d2./",
  "b4/d8/d2/r16/c8/b8/a8/b4./c4./c+4./d4./",
  "e4/>a8/a2/r16/<g8/f+8/e8/d2./",
  "d8/g2/r16/g8/g+2/r16/g+8/>a2/r16/a8/c2/r16/",
  "b8/a8/<g8/>b4/<g8/>b4/<g8/>a4./<g1/",
  ""
};

bool titltflg;
int      titlplace;              /*  Place in title tune;            */
int      titlline;               /* Line in title tune               */
unsigned titltone;               /*  Current title tone              */
int      titlticks;              /*  Ticks until note change         */
int      titloctv;               /*  Octave                          */

char** tune;                  /* Tune player statics              */
int      line;
int      place;
unsigned tunefreq;
int      tunedura;
int      octavefactor;

void opennet(void);
void readnet(void);
void writenet(void);
void closenet(void);

/* Title screen, initialisation and main game loop */
int main(int argc,char* argv[])
{
  int i;
  object* plane;
  int inc;
  bool foundplayerindex;
  bool alldone;

  nobjects=(object*)malloc(100*sizeof(object));

  /* Title screen
     Set:
       playmode:
         NOVICE
         SINGLE
         COMPUTER
         ASYNCH
         (MULTIPLE)
       soundflg
       joystick
       missok
       ibmkeyboard
       network parameters
       netmaxplayers
  */

  randv=inithistory(getlrt());

  inittonetable();
  inittimer(timerint); /* AJ */
  setgmode(BIOS_GRAPHICS);
  multiplayer=(playmode==MULTIPLE || playmode==ASYNCH);
  if (!multiplayer)
    maxcrash=MAXCRASH;
  else {
    maxcrash=MAXCRASH*2;
    if (playmode==MULTIPLE) {
      opennet();
      readnet();
      if (netbuf.players==0) {
        netbuf.maxplayers=netmaxplayers;
        netbuf.randv=randv;
      }
      else
        randv=netbuf.randv;
/*    if (netbuf.players>=netbuf.maxplayers)
        Maximum number of players already playing */
      netbuf.players++;
    }
    else {
      /* Initialise asynch comms. Set "playerindex" and "randv". */
      netbuf.players=netbuf.maxplayers=2;
    }
  }
  truemultiplayer=(multiplayer && netbuf.maxplayers>1);
  if (keydelay==-1)
    keydelay=1;
  inplay=TRUE;
  initkeyboard(keybint); /* AJ */

  do {
    initground();
    initobjs();
    if (!multiplayer) {
      createplayerplane(NULL);
      createcomputerplane(NULL);
      createcomputerplane(NULL);
      createcomputerplane(NULL);
    }
    else {
      if (playmode==MULTIPLE) {
        foundplayerindex=FALSE;
        for (i=0;i<netbuf.maxplayers;i++) {
          if (!foundplayerindex && netbuf.states[i]==WAITING) {
            playerindex=i;
            createplayerplane(NULL);
            netbuf.keys[i]=0;
            netbuf.states[i]=FLYING;
            netbuf.lastplayer=i;
            foundplayerindex=TRUE;
          }
          else
            createremoteplane(netbuf.states[i]);
        }
        if ((netbuf.maxplayers&1)==1)
          createcomputerplane(NULL);
        writenet();
        /* Wait for other players to turn up */
        do {
          readnet();
          for (i=0;i<netbuf.maxplayers;i++)
            if (netbuf.states[i]!=FLYING && netbuf.states[i]!=FINISHED)
              break;
        } while (i!=netbuf.maxplayers);
      }
      else
        if (player==0) {
          createplayerplane(NULL);
          createremoteplane(FLYING);
        }
        else
          createremoteplane(FLYING);
          createplayerplane(NULL);
        }
    createtargets();
    initdisplay(FALSE);
    createflocks();
    createoxen();
    gmaxspeed=MAX_SPEED+level;
    gminspeed=MIN_SPEED+level;
    targetrange=150;
    if (level<6)
      targetrange-=15*(6-level);
    targetrange*=targetrange;
    do {
      while (movetick<15);
      movetick-=15;
      updateobjects();
      updatejoystick();
      updatescreen();
      checkcollisions();
      updatesound();
    } while (endcount>0);
    if (!multiplayer && !quit) {
      if (endstatuses[playerindex]==WINNER) {
        plane=&nobjects[playerindex];
        inc=0;
        while (plane->crashes++<maxcrash) {
          inc+=25;
          plane->score+=inc;
          useonscreenbuf();
          displayplanesgauge(plane);
          dispscore(plane);
          counttick=0;
          while (counttick<5);
        }
        level++;
        savescore=plane->score;
      }
      else {
        level=0;
        savescore=0;
      }
      inittonetable();
    }
  } while (!multiplayer && !quit);
  setgmode(BIOS_TEXT);
  sound(0,0,NULL);
  updatesound();
  if (playmode==MULTIPLE) {
    readnet();
    netbuf.states[playerindex]=FINISHED;
    netbuf.keys[playerindex]=0;
    alldone=TRUE;
    for (i=0;i<netbuf.maxplayers;i++)
      if (netbuf.states[i]!=FINISHED) {
        alldone=FALSE;
        break;
      }
    if (alldone) { /* Last one out shut the doors... */
      netbuf.players=0;
      netbuf.lastplayer=0;
      for (i=0;i<MAX_PLYR;i++)
        netbuf.states[i]=WAITING;
    }
    writenet();
    closenet();
  }
  restoreints(); /* AJ */
  flushhistory();
  flushkeybuf();
  return 0;
}

bool keypressedflag;
bool paused;
bool breakf=FALSE;
int writecharcol=3;
int keysprev,keysnext,keyspressed;
int joykeysprev,joykeysnext,joykeyspressed;

void keybint(void)
{
  int scancode,k;
  keypressedflag=TRUE;
  if (!ibmkeyboard)
    return;
  paused=FALSE;
  scancode=inportb(PORT_KEYB);
  switch (scancode&0x7f) {
    case SC_X:     k=KEY_ACCEL;     break;
    case SC_Z:     k=KEY_BRAKE;     break;
    case SC_COMMA: k=KEY_CLIMB;     break;
    case SC_SLASH: k=KEY_DESCEND;   break;
    case SC_DOT:   k=KEY_FLIP;      break;
    case SC_SPACE: k=KEY_FIRE;      break;
    case SC_B:     k=KEY_BOMB;      break;
    case SC_H:     k=KEY_HOME;      break;
    case SC_S:     k=KEY_SOUND;     break;
    case SC_BREAK: k=KEY_BREAK;     breakf=TRUE; break;
    case SC_V:     k=KEY_MISSILE;   break;
    case SC_C:     k=KEY_STARBURST; break;
    case SC_P:
      if (scancode&0x80) {
        paused=TRUE;
        if (soundflg) {
          sound(0,0,NULL);
          updatesound();
          soundflg=FALSE;
          while(paused);
          soundflg=TRUE;
        }
        else
          while(paused);
      k=KEY_PAUSE;
      break;
    default: k=0;
  }
  if (k!=0)
    if (scancode&0x80) {
      if ((k&keysprev)!=0)
        keysnext&=~k;
      keyspressed&=~k;
    }
    else {
      keyspressed|=k;
      keysnext|=k;
    }
}

int inkeys(void)
{
  int k;
  if (!inplay)
    return history(inkey());
  if (ibmkeyboard) {
    k=keysprev=keysnext;
    keysnext=keyspressed;
    while (kbhit()) getkey();
  }
  else {
    switch(inkey()) {
      case 'X': case 'x': k=KEY_ACCEL;     break;
      case 'Z': case 'z': k=KEY_BRAKE;     break;
      case '<': case ',': k=KEY_CLIMB;     break;
      case '?': case '/': k=KEY_DESCEND;   break;
      case '>': case '.': k=KEY_FLIP;      break;
      case ' ':           k=KEY_FIRE;      break;
      case 'B': case 'b': k=KEY_BOMB;      break;
      case 'H': case 'h': k=KEY_HOME;      break;
      case 'S': case 's': k=KEY_SOUND;     break;
      case 'V': case 'v': k=KEY_MISSILE;   break;
      case 'C': case 'c': k=KEY_STARBURST; break;
      case 'P': case 'p': k=KEY_PAUSE;     break;
      default: k=0;
    }
    if (testbreak())
      k|=KEY_BREAK;
  }
  if (joystick) {
    joykeysprev=joykeysnext;
    joykeysnext=joykeyspressed;
    k|=joykeysprev;
  }
  return history(k);
}

int inkey(void)
{
  if (kbhit())
    return getkey();
  return 0;
}

void updatejoy(void)
{
  staticint joykeys[9]={KEY_FLIP, KEY_DESCEND,KEY_FLIP,
                        KEY_BRAKE,0,          KEY_ACCEL,
                        KEY_FLIP, KEY_CLIMB,  KEY_FLIP};

  int x,y,j,r;
  if (joystick) {
    x=readjoychannel(JOY_X);
    y=readjoychannel(JOY_Y);
    j=joykeys[(x<=JOYLOW ? 0 : (x>=JOYHIGH ? 2 : 1))+
              (y<=JOYLOW ? 0 : (y>=JOYHIGH ? 6 : 3))];
    r=inportb(PORT_JOY);
    if ((r&JOY_BUT1)==0)
      j|=KEY_FIRE;
    if ((r&JOY_BUT2)==0)
      j|=KEY_BOMB;
    joykeyspressed=j;
    joykeysnext|=j;
    joykeysnext&=j|~joykeysprev;
  }
}

int readjoychannel(int channel)
{
  int t;
  if ((inportb(PORT_JOY)&(1<<channel))!=0)
    return JOYMAX;
  keypressedflag=FALSE;
  outportb(PORT_TIMERC,0);
  t=getwordfromport(PORT_TIMER0);
  outportb(PORT_JOY,0);
  while ((inportb(PORT_JOY)&(1<<channel))!=0);
  if (keypressedflag)
    return (JOYHIGH+JOYLOW)/2; /* Was (JOYHIGH-JOYLOW)/2 */
  return t-getwordfromport(PORT_TIMER0);
}

void flushkeybuf(void)
{
/*  if (!inplay || !ibmkeyboard) */
    while (kbhit())
      getkey();
}

void setcolour(int c)
{
  writecharcol=c;
}

void swsetblk(char far* p,int n,char c)
{
  /* Set p[0]...p[n-1]=c; */
}

void updatescreen(void)
{
  object *obj;
  useonscreenbuf();
  for (obj=objtop;obj!=NULL;obj=obj->next)
    if (obj->deleteflag && obj->drawflag && obj->height!=1 &&
        obj->oldsprite==obj->sprite && obj->y==obj->oldy &&
        obj->oldx+displx==obj->x) {
      if (obj->display_func!=NULL)
        obj->display_func(obj);
    }
    else {
      if (obj->deleteflag)
        putimage(obj->oldx,obj->oldy,obj->oldsprite,obj);
      if (obj->drawflag) {
        if (obj->x>=displx && obj->x<=disprx &&
            (!oxsplatted || (obj->x-displx)/(SCR_WIDTH/3)==1)) { /* Think this is what DLC meant, not ((x/106)&1)==1 */
          obj->oldx=obj->x-displx;
          obj->oldy=obj->y;
          putimage(obj->oldx,obj->oldy,obj->sprite,obj);
          if (obj->display_func!=NULL)
            obj->display_func(obj);
        }
        else
          obj->drawflag=FALSE;
      }
    }
  for (obj=deltop;obj!=NULL;obj=obj->next)
    if (obj->deleteflag)
      putimage(obj->oldx,obj->oldy,obj->oldsprite,obj);
  if (!oxsplatted) {
    updateground();
    if (splatox)
      dispoxsplat();
  }
  dispinit=0;
  forcdisp=0;
}

void updateground(void)
{
  if (!dispinit) {
    if (dispdx==0 && forcdisp==0)
      return;
    drawground(grndsave);
  }
  memcpy(grndsave,ground+displx,SCR_WIDTH);
  drawground(grndsave);
}

void drawground(unsigned char *scrground)
{
  int y=*scrground,y2;
  int x;
  for (x=0;x<320;x++) {
    y2=*(scrground++);
    if (y2==y)
      putpixel(x,y,WHITE_R);
    else
      if (y2>y)
        do
          putpixel(x,y++,WHITE_R);
        while (y!=y2);
      else
        do
          putpixel(x,y--,WHITE_R);
        while (y!=y2);
  }
}

/* Update all objects */
void updateobjects(void)
{
  object* current;
  object* next;
  if (deltop!=NULL) {
    delbot->next=objfree;
    objfree=deltop;
    deltop=delbot=NULL;
  }
  dispcnt++;
  if (dispcnt>=keydelay)
    dispcnt=0;
  for (current=objtop;current!=NULL;current=next) {
    next=current->next;
    current->deleteflag=current->drawflag;
    current->oldsprite=current->sprite;
    current->drawflag=(*current->update_func)(current);
    if (multiplayer && current->index==netbuf.maxplayers && dispcnt==0)
      if (playmode==MULTIPLE)
        multput();
      else
        asynput();
  }
  countmove++;
}

void asynput(void)
{
  static bool first=TRUE;
  if (first)
    first=FALSE;
  else
    lastkey=inkeys();
  flushkeybuf();
  /* Output "lastkey" to port */
}

void multput(void)
{
  object* plane;
  int count,dkerr;
  int tickwait;
  static bool first=TRUE;

  plane=&nobjects[playerindex];
  updated(0,playerindex);
  if (first)
    first=FALSE;
  else
    netbuf.keys[playerindex]=inkeys();
  netbuf.states[playerindex]=plane->state;
  netbuf.lastplayer=playerindex;
  flushkeybuf();
  writenet();
  updated(playerindex+1,netbuf.maxplayers);
}

void updated(int n1,int n2)
{
  int n,count;
  object* ob;
  bool done;
  int last;

  for (;;) {
    last=netbuf.lastplayer;
    done=TRUE;
    for (n=n1;n<n2;n++)
      if (netbuf.states[n]!=FINISHED)
        break;
    if (n<n2)
      if (playerindex==last)
        done=FALSE;
      else
        if (last>=n)
          for (;n<n2;n++)
            if (netbuf.states[n]!=FINISHED)
              done=(n==last);
    if (done)
      return;
    readnet();
  }
}

/* Update user controlled plane */
bool updateplayerplane(object* plane)
{
  bool rc;
  int oldx;
  compplane=FALSE;
  planeisplayer=TRUE;
  currobx=plane->index;
  endstatus=endstatuses[playerindex];
  if (endstatus!=0 && endcount>0)
    endcount--;
  if (!dispcnt) {
    if (playmode==MULTIPLE)
      multkey=multget(plane);
    else
      if (playmode==ASYNCH)
        multkey=asynget(plane);
    else {
      multkey=inkeys();
      flushkeybuf();
    }
    interpretkeys(plane,multkey);
  }
  else {
    plane->flaps=0;
    plane->starburst_firing=FALSE;
    plane->bombing=FALSE;
    plane->missile_target=NULL;
  }
  if ((plane->state==CRASHED || plane->state==GHOSTCRASHED) && plane->hitcounter<=0) {
    plane->crashes++;
    if (endstatus!=WINNER && (plane->life<=QUIT || (!multiplayer && plane->crashes>=MAXCRASH))) {
      if (endstatus==0)
        loser(plane);
    }
    else {
      createplayerplane(plane);
      initdisplay(TRUE);
      if (endstatus==WINNER)
        winner(plane);
    }
  }
  oldx=plane->x;
  rc=updateplane(plane);
  if (oldx<=SCR_LIMIT || oldx>=MAX_X-SCR_LIMIT)
    dispdx=0;
  else {
    dispdx=plane->x-oldx;
    displx+=dispdx;
    disprx+=dispdx;
  }
  if (!plane->athome) {
    useonscreenbuf();
    if (plane->firing)
      displayammogauge(plane);
    if (plane->bombing)
      displaybombgauge(plane);
    if (plane->missile_target!=NULL)
      displaymissilegauge(plane);
    if (plane->starburst_firing)
      displaystarburstgauge(plane);
  }
  return rc;
}

/* Interpret user's commands */
void interpretkeys(object* plane,int key)
{
  int state=plane->state;
  plane->flaps=0;
  plane->bombing=FALSE;
  plane->starburst_firing=FALSE;
  plane->missile_target=NULL;
  plane->firing=FALSE;
  if (state!=FLYING && state!=STALLED && state!=FALLING && state!=WOUNDED &&
      state!=WOUNDSTALL && state!=GHOST && state!=GHOSTSTALLED)
    return;
  if (state!=FALLING) {
    if (endstatus!=0) {
      if (endstatus==LOSER && planeisplayer)
        gohome(plane);
      return;
    }
    if ((key&K_BREAK)!=0) {
      plane->life=QUIT;
      plane->goinghome=FALSE;
      if (plane->athome) {
        plane->state=state=((state>=FINISHED) ? GHOSTCRASHED : CRASHED);
        plane->hitcounter=0;
      }
      if (planeisplayer)
        quit=TRUE;
    }
    if ((key&K_HOME)!=0)
      if (state==FLYING || state==GHOST || state==WOUNDED)
        plane->goinghome=TRUE;
  }
  if ((countmove&1)==1 || (state!=WOUNDED && state!=WOUNDSTALL)) {
    if ((key&K_FLAPU)!=0) {
      plane->flaps++;
      plane->goinghome=FALSE;
    }
    if ((key&K_FLAPD)!=0) {
      plane->flaps--;
      plane->goinghome=FALSE;
    }
    if ((key&K_FLIP)!=0) {
      plane->inverted=!plane->inverted;
      plane->goinghome=FALSE;
    }
    if ((key&K_DEACC)!=0) {
      if (plane->accel)
        plane->accel--;
      plane->goinghome=FALSE;
    }
    if ((key&K_ACCEL)!=0) {
      if (plane->accel<MAX_THROTTLE)
        plane->accel++;
      plane->goinghome=FALSE;
    }
  }
  if ((key&K_SHOT)!=0 && state<FINISHED)
    plane->firing=TRUE;
  if ((key&K_MISSILE)!=0 && state<FINISHED)
    plane->missile_target=plane;
  if ((key&K_BOMB)!=0 && state<FINISHED)
    plane->bombing=TRUE;
  if ((key&K_STARBURST)!=0 && state<FINISHED)
    plane->starburst_firing=TRUE;
  if ((key&K_SOUND)!=0 && planeisplayer) {
    if (soundflg) {
      sound(0,0,NULL);
      updatesound();
    }
    soundflg=!soundflg;
  }
  if (plane->goinghome)
    gohome(plane);
}

/* Update computer controlled plane */
bool updatecomputerplane(object* plane)
{
  compplane=TRUE;
  planeisplayer=FALSE;
  plane->flaps=0;
  plane->starburst_firing=FALSE;
  plane->bombing=FALSE;
  plane->missile_target=NULL;
  currobx=plane->index;
  endstatus=endstatuses[currobx];
  if (!dispcnt)
    plane->firing=FALSE;
  switch (plane->state) {
    case WOUNDED:
    case WOUNDSTALL:
      if ((countmove&1)==1)
        break;
    case FLYING:
    case STALLED:
      if (endstatus!=0) {
        gohome(plane);
        break;
      }
      if (!dispcnt)
        computerpilot(plane);
      break;
    case CRASHED:
      plane->firing=FALSE;
      if (plane->hitcounter<=0 && endstatus==0)
        createcomputerplane(plane);
      break;
    default:
      plane->firing=FALSE;
      break;
  }
  return updateplane(plane);
}

/* Update a plane */
bool updateplane(object* plane)
{
  static char gravity[]={0,-1,-2,-3,-4,-3,-2,-1,0,1,2,3,4,3,2,1};

  int nangle,nspeed,state,limit;
  bool update;
  int x,y,newstate,stalled,grv;
  state=plane->state;
  switch (state) {
    case FINISHED:
    case WAITING:
      return FALSE;
    case CRASHED:
    case GHOSTCRASHED:
      plane->hitcounter--;
      break;
    case FALLING:
      plane->hitcounter-=2;
      if (plane->yv<0 && plane->xv!=0)
        if (((plane->inverted ? 1 : 0)^(plane->xv<0 ? 1 : 0))==1)
          plane->hitcounter-=plane->flaps;
        else
          plane->hitcounter+=plane->flaps;
      if (plane->hitcounter<=0) {
        if (plane->yv<0)
          if (plane->xv<0)
            plane->xv++;
          else
            if (plane->xv>0)
              plane->xv--;
            else
              plane->inverted=!plane->inverted;
        if (plane->yv>-10)
          plane->yv--;
        plane->hitcounter=FALLCOUNT;
      }
      plane->angle=(direction(plane)<<1);
      if (plane->yv<=0)
        initsound(plane,SOUND_FALLING);
      break;
    case STALLED:
    case GHOSTSTALLED:
    case WOUNDSTALL:
    case FLYING:
    case WOUNDED:
    case GHOST:
      if (state==STALLED)
        newstate=FLYING;
      if (state==GHOSTSTALLED)
        newstate=GHOST;
      if (state==WOUNDSTALL)
        newstate=WOUNDED;
      if (state==STALLED || state==GHOSTSTALLED || state==WOUNDSTALL) {
        stalled=(plane->angle!=(3*ANGLES/4));
        if (!(stalled || plane->speed<gminspeed))
          plane->state=state=newstate;
      }
      else {
        stalled=(plane->y>=MAX_Y);
        if (stalled)
          if (playmode==NOVICE) {
            plane->angle=(3*ANGLES/4);
            stalled=FALSE;
          }
          else {
            stallplane(plane);
            state=plane->state;
          }
      }
      if (goingsun && planeisplayer)
        break;
      if (plane->life<=0 && !plane->athome && (state==FLYING || state==STALLED || state==WOUNDED || state==WOUNDSTALL)) {
        hitplane(plane);
        scorepln(plane);
        return updateplane(plane);
      }
      if (plane->firing)
        createbullet(plane,NULL);
      if (plane->bombing)
        createbomb(plane);
      if (plane->missile_target!=NULL)
        createmissile(plane);
      if (plane->starburst_firing)
        createstarburst(plane);
      nangle=plane->angle;
      nspeed=plane->speed;
      update=FALSE;
      if (plane->flaps!=0) {
        if (plane->inverted)
          nangle-=plane->flaps;
        else
          nangle+=plane->flaps;
        nangle=(nangle+ANGLES)%ANGLES;
        update=TRUE;
      }
      if ((countmove&3)==0) {
        if (!stalled && nspeed<gminspeed && playmode!=NOVICE) {
          nspeed--;
          update=TRUE;
        }
        else {
          limit=gminspeed+plane->accel+gravity[nangle];
          if (nspeed<limit) {
            nspeed++;
            update=TRUE;
          }
          else
            if (nspeed>limit) {
              nspeed--;
              update=TRUE;
            }
        }
      }
      if (update) {
        if (plane->athome)
          if (plane->accel || plane->flaps)
            nspeed=gminspeed;
          else
            nspeed=0;
        else
          if (nspeed<=0 && !stalled) {
            if (playmode==NOVICE)
              nspeed=1;
            else {
              stallplane(plane);
              return updateplane(plane);
            }
          }
        plane->speed=nspeed;
        plane->angle=nangle;
        if (stalled) {
          plane->xv=plane->xvfrac=plane->yvfrac=0;
          plane->yv=-nspeed;
        }
        else
          setvel(plane,nspeed,nangle);
      }
      if (stalled) {
        plane->hitcounter--;
        if (plane->hitcounter==0) {
          plane->inverted=!plane->inverted;
          plane->angle=((3*ANGLES/2)-plane->angle)%ANGLES;
          plane->hitcounter=STALLCOUNT;
        }
      }
      if (!compplane) {
        if (planeisplayer && plane->speed>(plane->life%(MAX_FUEL/10))) {
          useonscreenbuf();
          displayfuelgauge(plane);
        }
        plane->life-=plane->speed;
      }
      if (plane->speed)
        plane->athome=FALSE;
      break;
  }
  if (endstatus==WINNER && planeisplayer && goingsun)
    plane->sprite=swwinsym[endcount/18];
  else
    plane->sprite=(plane->state==FINISHED) ? NULL : ((plane->state==FALLING && !plane->xv && plane->yv<0) ? swhitsym[plane->inverted ? 1 : 0] : swplnsym[plane->inverted ? 1 : 0][plane->angle]);
  moveobject(plane,&x,&y);
  if (x<0)
    x=plane->x=0;
  else
    if (x>=MAX_X-16)
      x=plane->x=MAX_X-16;
  if (!compplane && (plane->state==FLYING || plane->state==STALLED || plane->state==WOUNDED || plane->state==WOUNDSTALL) && endstatuses[playerindex]==0)
    nearpln(plane);
  deletex(plane);
  insertx(plane,plane->nextx);
  if (plane->bomb_delay!=0)
    plane->bomb_delay--;
  if (plane->missile_delay!=0)
    plane->missile_delay--;
  if (plane->starburst_delay!=0)
    plane->starburst_delay--;
  if (!compplane && plane->athome && plane->state==FLYING)
    refuel(plane);
  if (y<MAX_Y && y>=0) {
    if (plane->state==FALLING || plane->state==WOUNDED || plane->state==WOUNDSTALL)
      createsmoke(plane);
    useonscreenbuf();
    dispwobj(plane);
    return (planeisplayer || plane->state<FINISHED);
  }
  return FALSE;
}

void nearpln(object* ob)
{
  static int lcompter[MAX_PLYR]={0,1155,0,2089};
  static int rcompter[MAX_PLYR]={0,2088,1154,10000};

  object* obt;
  object* obc;
  int i,obx,r,obclr;
  obt=objtop+1;
  obx=ob->x;
  obclr=ob->owner->colour;
  for (i=1;obt->type==PLANE;i++,obt++) {
    if (obclr==obt->owner->colour)
      continue;
    if (equal(obt->display_func,displaycomputerplane))
      if (playmode!=COMPUTER || (obx>=lcompter[i] && obx<=rcompter[i])) {
        obc=compnear[i];
        if (!obc || abs(obx-obt->x)<abs(obc->x-obt->x))
          compnear[i]=ob;
      }
  }
}

void refuel(object* plane)
{
  useonscreenbuf();
  if (topup(&plane->life,MAX_FUEL))
    displayfuelgauge(plane);
  if (topup(&plane->ammo,MAX_AMMO))
    displayammogauge(plane);
  if (topup(&plane->bombs,MAX_BOMBS))
    displaybombgauge(plane);
  if (topup(&plane->missiles,MAX_MISSILES))
    displaymissilegauge(plane);
  if (topup(&plane->starbursts,MAX_STARBURSTS))
    displaystarburstgauge(plane);
}

bool topup(int* counter,int max)
{
  bool rc=FALSE;
  if ((*counter)==max)
    return rc;
  if (max<20) {
    if (countmove%20==0) {
      (*counter)++;
      rc=planeisplayer;
    }
  }
  else {
    (*counter)+=max/100;
    rc=planeisplayer;
  }
  if ((*counter)>max)
    (*counter)=max;
  return rc;
}

bool updatebullet(object* bullet)
{
  int x,y;
  deletex(bullet);
  bullet->life--;
  if (bullet->life==0) {
    deallobj(bullet);
    return FALSE;
  }
  moveobject(bullet,&x,&y);
  if (y>=MAX_Y || y<=(int)ground[x] || x<0 || x>=MAX_X) {
    deallobj(bullet);
    return FALSE;
  }
  insertx(bullet,bullet->nextx);
  bullet->sprite=(char *)WHITE_R;
  return TRUE;
}

bool updatebomb(object* bomb)
{
  int x,y;
  deletex(bomb);
  if (bomb->life<0) {
    deallobj(bomb);
    bomb->state=FINISHED;
    useonscreenbuf();
    dispwobj(bomb);
    return FALSE;
  }
  adjustfall(bomb);
  if (bomb->yv<=0)
    initsound(bomb,SOUND_BOMB);
  moveobject(bomb,&x,&y);
  if (y<0 || x<0 || x>=MAX_X) {
    deallobj(bomb);
    stopsound(bomb);
    bomb->state=FINISHED;
    useonscreenbuf();
    dispwobj(bomb);
    return FALSE;
  }
  bomb->sprite=swbmbsym[direction(bomb)];
  insertx(bomb,bomb->nextx);
  if (y>=MAX_Y)
    return FALSE;
  useonscreenbuf();
  dispwobj(bomb);
  return TRUE;
}

void adjustfall(object* ob)
{
  ob->life--;
  if (ob->life==0) {
    if (ob->yv<0)
      if (ob->xv<0)
        ob->xv++;
      else
        if (ob->xv>0)
          ob->xv--;
    if (ob->yv>-10)
      ob->yv--;
    ob->life=BOMBLIFE;
  }
}

int direction(object* ob)
{
  int dx=ob->xv,dy=ob->yv;
  if (yv>0)  { if (xv<0) return 3; if (xv==0) return 2; return 1; }
  if (yv==0) { if (xv<0) return 4; if (xv==0) return 6; return 0; }
               if (xv<0) return 5; if (xv==0) return 6; return 7;
}

bool updatemissile(object* missile)
{
  int x,y,angle;
  object* target;
  deletex(missile);
  if (missile->life<0) {
    deallobj(missile);
    missile->state=FINISHED;
    useonscreenbuf();
    dispwobj(missile);
    return FALSE;
  }
  if (missile->state==FLYING) {
    target=missile->target;
    if (target!=missile->owner && (missile->life&1)==1) {
      if (target->target!=NULL)
        target=target->target;
      aim(missile,target->x,target->y,NULL,FALSE);
      angle=missile->angle=(missile->angle+missile->flaps+ANGLES)%ANGLES;
      setvel(missile,missile->speed,angle);
    }
    moveobject(missile,&x,&y);
    missile->life--;
    if (missile->life==0 || y>=(MAX_Y*3)/2) {
      missile->state=FALLING;
      missile->life++;
    }
  }
  else {
    adjustfall(missile);
    missile->angle=(missile->angle+1)%ANGLES;
    moveobject(missile,&x,&y);
  }
  if (y<0 || x<0 || x>=MAX_X) {
    deallobj(missile);
    missile->state=FINISHED;
    useonscreenbuf();
    dispwobj(missile);
    return FALSE;
  }
  missile->sprite=swmscsym[missile->angle];
  insertx(missile,missile->nextx);
  if (y>=MAX_Y)
    return FALSE;
  useonscreenbuf();
  dispwobj(missile);
  return TRUE;
}

bool updatestarburst(object* starburst)
{
  int x,y;
  deletex(starburst);
  if (starburst->life<0) {
    starburst->owner->target=NULL;
    deallobj(starburst);
    return FALSE;
  }
  adjustfall(starburst);
  moveobject(starburst,&x,&y);
  if (y<=(int)ground[x] || x<0 || x>=MAX_X) {
    starburst->owner->target=NULL;
    deallobj(starburst);
    return FALSE;
  }
  starburst->owner->target=starburst;
  starburst->sprite=swbstsym[starburst->life&1];
  insertx(starburst,starburst->nextx);
  return (y<MAX_Y);
}

bool updatetarget(object* target)
{
  int r;
  object* obp=objtop;
  target->firing=FALSE;
  if (level!=0 && target->state==STANDING &&
      (obp->state==FLYING || obp->state==STALLED || obp->state==WOUNDED || obp->state==WOUNDSTALL) &&
      target->colour!=obp->colour && (level>1 || (countmove&1)==1)) {
    r=range(target->x,target->y,obp->x,obp->y);
    if (r>0 && r<targetrange) {
      target->firing=TRUE; /* Was obp. Is obp!=NULL always? */
      createbullet(target,obp);
    }
  }
  target->hitcounter--;
  if (target->hitcounter<0)
    target->hitcounter=0;
  target->sprite=(target->state==STANDING) ? swtrgsym[target->inverted ? 1 : 0] : swhtrsym;
  return TRUE;
}

bool updatefrag(object* frag)
{
  int x,y;
  int subtype=frag->subtype;
  deletex(frag);
  if (frag->life<0) {
    if (subtype!=0)
      stopsound(frag);
    deallobj(frag);
    return FALSE;
  }
  frag->life--;
  if (frag->life==0) {
    if (frag->yv<0)
      if (frag->xv<0)
        frag->xv++;
      else
        if (frag->xv>0)
          frag->xv--;
    if ((frag->subtype!=0 && frag->yv>-10) || (frag->subtype==0 && frag->yv>-gminspeed))
      frag->yv--;
    frag->life=EXPLLIFE;
  }
  moveobject(frag,&x,&y);
  if (y<=(int)ground[x] || x<0 || x>=MAX_X) {
    if (subtype!=0)
      stopsound(frag);
    deallobj(frag);
    return FALSE;
  }
  frag->hitcounter++;
  insertx(frag,frag->nextx);
  frag->sprite=swexpsym[frag->subtype];
  return (y<MAX_Y);
}

bool updatesmoke(object* smoke)
{
  int state=smoke->owner->state;
  smoke->life--;
  if (smoke->life==0 || (state!=FALLING && state!=WOUNDED && state!=WOUNDSTALL && state!=CRASHED)) {
    deallobj(smoke);
    return FALSE;
  }
  smoke->sprite=(char *)(BLACK_R+smoke->colour);
  return TRUE;
}

bool updateflock(object* flock)
{
  int x,y;
  deletex(flock);
  if (flock->life==-1) {
    useonscreenbuf();
    dispwobj(flock);
    deallobj(flock);
    return FALSE;
  }
  flock->life--;
  if (flock->life==0) {
    flock->inverted=!flock->inverted;
    flock->life=FLOCKLIFE;
  }
  if (flock->x<MINFLCKX || flock->x>MAXFLCKX)
    flock->xv=-flock->xv;
  moveobject(flock,&x,&y);
  insertx(flock,flock->nextx);
  flock->sprite=swflksym[flock->inverted ? 1 : 0];
  useonscreenbuf();
  dispwobj(flock);
  return TRUE;
}

bool updatebird(object* bird)
{
  int x,y;
  deletex(bird);
  if (bird->life==-1) {
    deallobj(bird);
    return FALSE;
  }
  else
    if (bird->life==-2) {
      bird->yv=-bird->yv;
      bird->xv=(countmove&7)-4;
      bird->life=BIRDLIFE;
    }
    else {
      bird->life--;
      if (bird->life==0) {
        bird->inverted=!bird->inverted;
        bird->life=BIRDLIFE;
      }
    }
  moveobject(bird,&x,&y);
  insertx(bird,bird->nextx);
  bird->sprite=swbrdsym[bird->inverted ? 1 : 0];
  if (y>=MAX_Y || y<=(int)ground[x] || x<0 || x>=MAX_X) {
    bird->y-=bird->yv;
    bird->life=-2;
    return FALSE;
  }
  return TRUE;
}

bool updateox(object* ox)
{
  ox->sprite=swoxsym[ox->state==STANDING ? 0 : 1];
  return TRUE;
}

void endgame(int targclr)
{
  int winclr;
  object* ob;
  if (!truemultiplayer)
    winclr=1;
  else
    if ((objtop+1)->score==objtop->score)
      winclr=3-targclr;
    else
      winclr=((objtop+1)->score>objtop->score) ? 2 : 1;
  ob=objtop;
  while (ob->type==PLANE) {
    if (endstatuses[ob->index]==0)
      if (ob->colour==winclr &&
          (ob->crashes<MAXCRASH-1 ||
           (ob->crashes<MAXCRASH &&
            (ob->state==FLYING || ob->state==STALLED || ob->state==WOUNDED || ob->state==WOUNDSTALL))))
        winner(ob);
      else
        loser(ob);
    ob=ob->next;
  }
}

void winner(object* plane)
{
  int i=plane->index;
  endstatuses[i]=WINNER;
  if (i==playerindex) {
    endcount=72;
    goingsun=TRUE;
    plane->xv=plane->yv=plane->xvfrac=plane->yvfrac=0;
    plane->state=FLYING;
    plane->life=MAX_FUEL;
    plane->speed=MIN_SPEED;
  }
}

void loser(object* plane)
{
  int i=plane->index;
  endstatuses[i]=LOSER;
  if (i==playerindex) {
    setcolour(MAGENTA_R);
    swposcur(16,12);
    puts("THE END");
    endcount=20;
  }
}

void computerpilot(object* plane)
{
  object* target=compnear[currobx];
  goinghome=FALSE;
  if (target!=NULL)
    attack(plane,target);
  else
    if (!plane->athome)
      cruise(plane);
  compnear[currobx]=NULL;
}

void attack(object* plane,object* target)
{
  courseadj=((countmove&0x1f)<16 ? 16 : 0);
  if (target->speed!=0)
    aim(plane,target->x-(fcos(CLOSE,target->angle)>>8),
              target->y-(fsin(CLOSE,target->angle)>>8),target,FALSE);
  else
    aim(plane,target->x,target->y+4,target,FALSE);
}

void cruise(object* plane)
{
  int orgx;
  courseadj=((countmove&0x1f)<16 ? 16 : 0);
  orgx=oobjects[currobx].x;
  aim(plane,(orgx<MAX_X/3 ? MAX_X/3 : (orgx>2*MAX_X/3 ? 2*MAX_X/3 : orgx))+courseadj,MAX_Y-50-(courseadj>>1),NULL,FALSE);
}

void gohome(object* plane)
{
  object* base;
  if (plane->athome)
    return;
  base=&oobjects[currobx];
  courseadj=((countmove&0x1f)<16 ? 16 : 0);
  if (abs(plane->x-base->x)<HOME && abs(plane->y-base->y)<HOME) {
    if (planeisplayer) {
      createplayerplane(plane);
      initdisplay(TRUE);
    }
    else
      if (compplane)
        createcomputerplane(plane);
      else
        createplane(plane);
    return;
  }
  goinghome=TRUE;
  aim(plane,base->x,base->y,NULL,FALSE);
}

int shoot(object* target)
{
  static object obsp,obtsp;

  int obx,oby,obtx,obty;
  int nspeed,nangle;
  int rprev;
  int r,i;
  movmem(&obs,&obsp,sizeof(object));
  movmem(target,&obtsp,sizeof(object));
  nspeed=obsp.speed+BULSPEED;
  setvel(&obsp,nspeed,obsp.angle);
  obsp.x+=SYM_WIDTH/2;
  obsp.y-=SYM_HEIGHT/2;
  nangle=obtsp.angle;
  nspeed=obtsp.speed;
  rprev=NEAR;
  for (i=0;i<BULLIFE;i++) {
    moveobject(&obsp,&obx,&oby);
    r=obtsp.flaps;
    if ((obtsp.state==FLYING || obtsp.state==WOUNDED) && r!=0) {
      if (obtsp.inverted)
        nangle-=r;
      else
        nangle+=r;
      nangle=(nangle+ANGLES)%ANGLES;
      setvel(&obtsp,nspeed,nangle);
    }
    moveobject(&obtsp,&obtx,&obty);
    r=range(obx,oby,obtx,obty);
    if (r<0 || r>rprev)
      return 0;
    if (obx>=obtx && obx<=obtx+SYM_WIDTH-1 && oby<=obty && oby>=obty-SYM_HEIGHT+1)
      return (i>BULLIFE/3 ? 2 : 1);
  }
  return 0;
}

int tl,tr;

void cleartargs(void)
{
  tl=-2;
}

void testtargs(int x,int y)
{
  int i,xl,xr;
  xl=x-32-gmaxspeed;
  xr=x+32+gmaxspeed;
  tl=-1;
  tr=0;
  for (i=0;i<MAX_TARG+MAX_OXEN;i++)
    if (targets[i] && targets[i]->x>=xl) {
      tl=i;
      break;
    }
  if (tl==-1)
    return;
  for (;i<MAX_TARG+MAX_OXEN && targets[i] && targets[i]->x<xr;i++);
  tr=i-1;
}

bool tstcrash(object* ob,int x,int y,int alt)
{
  int i,xl,xr,xt,yt;
  if (alt>50)
    return FALSE;
  if (alt<22)
    return TRUE;
  if (tl==-2)
    testtargs(ob->x,ob->y);
  xl=x-32;
  xr=x+32;
  for (i=tl;i<=tr;i++) {
    ob=targets[i];
    xt=ob->x;
    if (xt<xl)
      continue;
    if (xt>xr)
      return FALSE;
    yt=ob->y+(ob->state==STANDING ? 16 : 8);
    if (y<=yt)
      return TRUE;
  }
  return FALSE;
}

int range(int x,int y,int ax,int ay)
{
  int dx=abs(x-ax),dy=abs(y-ay);
  int t;
  dy+=(dy>>1);
  if (dx<125 && dy<125)
    return dx*dx+dy*dy;
  if (dx<dy) {
    t=dx;
    dx=dy;
    dy=t;
  }
  return -((dx*7+(dy<<2))>>3);
}

void aim(object* plane,int ax,int ay,object* target,bool longway)
{
  static int cflaps[3]={0,-1,1};
  static int crange[3],ccrash[3],calt[3];

  object* obp;
  int r,rmin,i,n;
  int x,y,dx,dy,nx,ny;
  int nangle,nspeed;
  if ((plane->state==STALLED || plane->state==WOUNDSTALL) && plane->angle!=3*ANGLES/4) {
    plane->flaps=-1;
    plane->accel=MAX_THROTTLE;
    return;
  }
  x=plane->x;
  y=plane->y;
  dx=x-ax;
  if (abs(dx)>160) {
    if (plane->xv!=0 && (dx<0)==(plane->xv<0)) {
      if (plane->hitcounter==0)
        plane->hitcounter=((y>MAX_Y-50) ? 2 : 1);
      aim(plane,x,plane->hitcounter==1 ? y+25 : y-25,NULL,TRUE);
      return;
    }
    plane->hitcounter=0;
    y+=100;
    aim(plane,x+(dx<0 ? 150 : -150),y>(MAX_Y-50-courseadj) ? MAX_Y-50-courseadj : y,NULL,TRUE);
    return;
  }
  else
    if (!longway)
      plane->hitcounter=0;
  if (plane->speed) {
    dy=y-ay;
    if (dy!=0 && abs(dy)<6)
      plane->y=(dy<0) ? (++y) : (--y);
    else
      if (dx!=0 && abs(dx)<6)
        plane->x=(dx<0) ? (++x) : (--x);
  }
  movmem(plane,&obs,sizeof(object));
  nspeed=obj.speed+1;
  if (nspeed>gmaxspeed && obs.type==PLANE)
    nspeed=gmaxspeed;
  else
    if (nspeed<gminspeed)
      nspeed=gminspeed;
  cleartargs();
  for (i=0;i<3;i++) {
    nangle=(obs.angle+(obs.inverted ? -cflaps[i] : cflaps[i])+ANGLES)%ANGLES;
    setvel(&obs,nspeed,nangle);
    moveobject(&obs,&nx,&ny);
    crange[i]=range(nx,ny,ax,ay);
    calt[i]=ny-orground[nx+8];
    ccrash[i]=tstcrash(plane,nx,ny,calt[i]);
    movmem(plane,&obs,sizeof(object));
  }
  if (target!=NULL) {
    i=shoot(target);
    if (i!=0)
      if (plane->missiles!=0 && i==2)
        plane->missile_target=(target->athome ? plane : target);
      else
        plane->firing=TRUE; /* Was target */
  }
  rmin=32767;
  for (i=0;i<3;i++) {
    r=crange[i];
    if (r>=0 && r<rmin && !ccrash[i]) {
      rmin=r;
      n=i;
    }
  }
  if (rmin==32767) {
    rmin=-32767;
    for (i=0;i<3;i++) {
      r=crange[i];
      if (r<0 && r>rmin && !ccrash[i]) {
        rmin=r;
        n=i;
      }
    }
  }
  if (plane->speed<gminspeed)
    plane->accel=MAX_THROTTLE;
  if (rmin!=-32767) {
    if (plane->accel<MAX_THROTTLE)
      plane->accel++;
  }
  else {
    if (plane->accel!=0)
      plane->accel--;
    n=0;
    dy=calt[0];
    if (calt[1]>dy) {
      dy=calt[1];
      n=1;
    }
    if (calt[2]>dy)
      n=2;
  }
  plane->flaps=cflaps[n];
  if (plane->type==PLANE && !plane->flaps)
    if (plane->speed)
      plane->inverted=(plane->xv<0);
}

void crashplane(object* plane)
{
  object* obo;
  if (plane->xv<0)
    plane->angle=(plane->angle+2)%ANGLES;
  else
    plane->angle=(plane->angle+ANGLES-2)%ANGLES;
  plane->state=(plane->state>=GHOST) ? GHOSTCRASHED : CRASHED;
  plane->athome=FALSE;
  plane->xv=plane->yv=plane->xvfrac=plane->yvfrac=plane->speed=0;
  obo=&oobjects[plane->index];
  plane->hitcounter=((abs(obo->x-plane->x)<SAFERESET) && (abs(obo->y-plane->y)<SAFERESET)) ? (MAXCRCOUNT<<1) : MAXCRCOUNT;
}

void hitplane(object* plane)
{
  plane->xvfrac=0;
  plane->yvfrac=0;
  plane->hitcounter=FALLCOUNT;
  plane->state=FALLING;
  plane->athome=FALSE;
}

void stallplane(object* plane)
{
  plane->xvfrac=0;
  plane->yvfrac=0;
  plane->xv=0;
  plane->inverted=FALSE;
  plane->angle=7*ANGLES/8;
  plane->speed=0;
  plane->yv=0;
  plane->hitcounter=STALLCOUNT;
  plane->state=(plane->state>=GHOST) ? GHOSTSTALLED : ((plane->state==WOUNDED) ? WOUNDSTALL : STALLED);
  plane->athome=FALSE;
}

void insertx(object* ob,object* obs)
{
  int obx=ob->x;
  if (obx<obs->x)
    do {
      obs=obs->prevx;
    } while (obx<obs->x);
  else {
    while (obx>=obs->x)
      obs=obs->nextx;
    obs=obs->prevx;
  }
  ob->nextx=obs->nextx;
  ob->prevx=obs;
  obs->nextx->prevx=ob;
  obs->nextx=ob;
}

void deletex(object* ob)
{
  ob->nextx->prevx=ob->prevx;
  ob->prevx->nextx=ob->nextx;
}

void inittonetable(void)
{
  tonetable* tt;
  int i;
  for (i=0,tt=tonetab;i<SNDSIZE-1;i++,tt++)
    tt->next=tt+1;
  tt->next=NULL;
  frsttone=NULL;
  freetone=tonetab;
}

void sound(inr type,inr parm,object* ob)
{
  if (type<soundtype) {
    soundtype=type;
    soundparm=parm;
    soundobj=ob;
  }
  else
    if (type==soundtype && parm<soundparm) {
      soundparm=parm;
      soundobj=ob;
    }
}

void updatesound(void)
{
  tonetable* tt;
  intsoff();
  tt=frsttone;
  while(tt) {
    tt->tone+=tt->change*soundticks;
    tt=tt->next;
  }
  soundticks=0;
  titltflg=FALSE;
  switch(soundtype) {
    case 0:
    case 32767:
    default:
      soundoff();
      lastobj=NULL;
      toneadj=NULL;
      break;
    case SOUND_PLANE:
      if (soundparm==0)
        tone(0xf000);
      else
        tone(0xd000+soundparm*0x1000);
      lastobj=NULL;
      toneadj=NULL;
      break;
    case SOUND_BOMB:
      if (soundobj==lastobj)
        break;
      toneadj=adjcont;
      lastobj=soundobj;
      adjcont();
      break;
    case SOUND_FALLING:
      if (soundobj==lastobj)
        break;
      toneadj=adjcont;
      lastobj=soundobj;
      adjcont();
      break;
    case SOUND_HIT:
      tone(rand(2) ? 0x9000 : 0xf000);
      lastobj=NULL;
      toneadj=NULL;
      break;
    case SOUND_EXPLOSION:
      tone(expltone);
      toneadj=NULL;
      lastobj=NULL;
      break;
    case SOUND_SHOT:
      tone(0x1000);
      toneadj=adjshot;
      lastobj=NULL;
      break;
    case SOUND_TITLE:
      titlline=0;
      titlplace=0;
      titlnote();
      toneadj=NULL;
      lastobj=NULL;
      titltflg=TRUE;
      break;
  }
  intson();
  soundtype=soundparm=32767;
}

void soundadj(void)
{
  soundticks++;
  if (lastfreq && toneadj!=NULL)
    toneadj();
  if (numexpls!=0)
    adjexpl();
  if (titltflg)
    adjtitl();
}

void adjcont(void)
{
  tonetable* tt=lastobj->tonetab;
  if (tt!=NULL)
    tone(tt->tone+tt->change*soundticks);
}

void adjshot(void)
{
  static unsigned int savefreq;
  if (lastfreq==0xf000)
    tone(savefreq);
  else {
    savefreq=lastfreq;
    tone(0xf000);
  }
}

void adjexpl(void)
{
  explticks--;
  if (explticks>=0)
    return;
  explnote();
}

void explnote(void)
{
  line=explline;
  place=explplace;
  tune=expltune;
  octavefactor=exploctv;
  playnote();
  explline=line;
  explplace=place;
  expltone=tunefreq;
  intsoff();
  explticks+=tunedura;
  intson();
  exploctv=octavefactor;
}

void adjtitl(void)
{
  titlticks--;
  if (titlticks>=0)
    return;
  titlnote();
}

void titlnote(void)
{
  line=titlline;
  place=titlplace;
  tune=expltune;
  octavefactor=titloctv;
  playnote();
  titlline=line;
  titlplace=place;
  titltone=tunefreq;
  intsoff();
  titlticks+=tunedura;
  intson();
  titloctv=octavefactor;
  soundoff();
  tone(titltone);
}

void initsound(object* ob,int type)
{
  tonetable* tt;
  if (ob->tonetab)
    return;
  if (ob->type==EXPLOSION) {
    intsoff();
    if (++numexpls==1) {
      explline=0;
      explplace=0;
      explnote();
    }
    ob->tonetab=(struct tt *)1;
    intson();
    return;
  }
  tt=allocton();
  if (tt!=NULL) {
    intsoff();
    switch (type) {
      case SOUND_BOMB:
        tt->tone=0x0300;
        tt->change=8;
        break;
      case SOUND_FALLING:
        tt->tone=0x1200;
        tt->change=-8;
        break;
      default:
        break;
    }
    ob->tonetab=tt;
    intson();
    return;
  }
}

tonetable* allocton(void)
{
  tonetable* tt;
  if (!freetone)
    return NULL;
  tt=freetone;
  freetone=tt->next;
  tt->next=frsttone;
  tt->prev=NULL;
  if (frsttone)
    frsttone->prev=tt;
  frsttone=tt;
  return frsttone;
}

void deallton(tonetable* tt)
{
  tonetable* ttb;
  if (ttb=tt->prev)
    ttb->next=tt->next;
  else
    frsttone=tt->next;
  if (ttb=tt->next)
    ttb->prev=tt->prev;
  tt->next=freetone;
  freetone=tt;
}

void stopsound(object* ob)
{
  tonetable* tt=ob->tonetab;
  if (tt==NULL)
    return;
  intsoff();
  if (ob->type==EXPLOSION)
    numexpls--;
  else
    deallton(tt);
  ob->tonetab=NULL;
  intson();
}

void tone(unsigned freq)
{
  if (!soundflg)
    return;
  if (lastfreq==freq)
    return;
  if (lastfreq==0)
    outportb(PORT_TIMERC,0xb6);
  outportb(PORT_TIMER2,freq&0xff);
  outportb(PORT_TIMER2,freq>>8);
  if (lastfreq==0)
    outportb(PORT_SPKR,inportb(PORT_SPKR)|3);
  lastfreq=freq;
  dispdbg=freq;
}

void soundoff(void)
{
  if (lastfreq!=0) {
    outportb(PORT_SPKR,inportb(PORT_SPKR)&0xfc);
    lastfreq=0;
    dispdbg=0;
  }
}

unsigned rand(unsigned modulo)
{
  static int seed[50] = {
    0x90b9,0xbcfb,0x6564,0x3313,0x3190,0xa980,0xbcf0,0x6f97,0x37f4,0x064b,
    0x9fd8,0x595b,0x1eee,0x820c,0x4201,0x651e,0x848e,0x15d5,0x1de7,0x1585,
    0xa850,0x213b,0x3953,0x1eb0,0x97a7,0x35dd,0xaf2f,0x1629,0xbe9b,0x243f,
    0x847d,0x313a,0x3295,0xbc11,0x6e6d,0x3398,0xad43,0x51ce,0x8f95,0x507e,
    0x499e,0x3bc1,0x5243,0x2017,0x9510,0x9865,0x65f6,0x6b56,0x36b9,0x5026};
  static i=0;
  if (i>=50)
    i=0;
  return seed[i++]%modulo;
}

#define NOTEEND     '/'
#define UPOCTAVE    '>'
#define DOWNOCTAVE  '<'
#define SHARP       '+'
#define FLAT        '-'
#define DOT         '.'
#define REST        'R'

void playnote(void)
{
  static int noteindex[]={0,2,3,5,7,8,10};
  static int notefreq[]={440,466,494,523,554,587,622,659,698,740,784,831};
  static int durplace,test,freq,duration;
  static int index;
  static int indexadj;
  static char durstring[5];
  static char charatplace,noteletter;
  static int noteoctavefactor;
  static int dottednote;

  bool firstplace=TRUE;
  indexadj=0;
  durplace=0;
  dottednote=2;
  noteoctavefactor=256;
  for (;;) {
    if (!line && !place)
      octavefactor=256;
    charatplace=toupper(tune[line][place++]);
    if (!charatplace) {
      place=0;
      line++;
      charatplace=tune[line][place];
      if (!charatplace)
        line=0;
      if (firstplace)
        continue;
      break;
    }
    firstplace=FALSE;
    if (charatplace==NOTEEND)
      break;
    test=isalpha(charatplace);
    if (test) {
      index=*(noteindex+(charatplace-'A'));
      noteletter=charatplace;
    }
    else
      switch(charatplace) {
        case UPOCTAVE:
          octavefactor<<=1;
          break;
        case DOWNOCTAVE:
          octavefactor>>=1;
          break;
        case SHARP:
          indexadj++;
          break;
        case FLAT:
          indexadj--;
          break;
        case DOT:
          dottednote=3;
          break;
        default:
          test=isdigit(charatplace);
          if (test)
            *(durstring+(durplace++))=charatplace;
          break;
      }
  }
  *(durstring+durplace)='\0';
  duration=atoi(durstring);
  if (duration<=0)
    duration=4;
  duration=(1440*dottednote/(60*duration))>>1;
  if (noteletter==REST)
    freq=32000;
  else {
    index+=indexadj;
    while (index<0) {
      index+=12;
      noteoctavefactor>>=1;
    }
    while (index>=12) {
      index-=12;
      noteoctavefactor<<=1;
    }
    freq=soundmul(notefreq[index],octavefactor,noteoctavefactor);
  }
  tunefreq=sounddiv(1331000L,freq);
  tunedura=duration;
}

bool testbreak(void)
{
  return breakf;
}

void initground(void)
{
  movmem(orground,ground,sizeof(ground_t)*MAX_X);
}

void initdisplay(bool reset)
{
  object* player;
  object ghostob;
  splatox=0;
  oxsplatted=FALSE;
  if (!reset) {
    clrdispa();
    useoffscreenbuf();
    dispworld();
    ghost=FALSE;
  }
  movedisp();
  useonscreenbuf();
  initwobj();
  initscore();
  player=&nobjects[playerindex];
  if (ghost) {
    ghostob.type=DUMMYTYPE;
    ghostob.height=ghostob.width=8;
    ghostob.colour=player->colour;
    ghostob.sprite=swghtsym;
    drawobject(GHOSTX,12,&ghostob);
  }
  else {
    displayfuelgauge(player);
    displaybombgauge(player);
    displaymissilegauge(player);
    displaystarburstgauge(player);
    displayammogauge(player);
    displayplanesgauge(player);
  }
  dispinit=TRUE;
}

void initscore(void)
{
  if (savescore) {
    nobjects[0].score=savescore;
    savescore=0;
  }
  dispscore(&nobjects[0]);
  if (truemultiplayer)
    dispscore(&nobjects[1]);
}

void displayplanesgauge(object* player)
{
  displaygauge(PLANESGAUGEX,maxcrash-player->crashes,maxcrash,player->colour);
}

void displayfuelgauge(object* player)
{
  displaygauge(FUELGAUGEX,player->life>>4,MAX_FUEL>>4,player->colour);
}

void displaybombgauge(object* player)
{
  displaygauge(BOMBGAUGEX,player->bombs,MAX_BOMBS,3-player->colour);
}

void displayammogauge(object* player)
{
  displaygauge(AMMOGAUGEX,player->ammo,MAX_AMMO,WHITE);
}

void displaymissilegauge(object* player)
{
  displaygauge(MISSILEGAUGEX,player->missiles,MAX_MISSILES,player->colour);
}

void displaystarburstgauge(object* player)
{
  displaygauge(STARBURSTGAUGEX,player->starbursts,MAX_STARBURSTS,player->colour==CYAN ? MAGNETA : CYAN);
}

void displaygauge(int x,int cury,int maxy,int colour)
{
  int y;
  if (!ghost) {
    cury=cury*10/maxy-1;
    if (cury>9)
      cury=9;
    for (y=0;y<=cury;y++)
      putpixel(x,y,colour);
    for (;y<=9;y++)
      putpixel(x,y,BLACK);
  }
}

void dispworld(void)
{
  int x,y,dx,maxh,sx;
  dx=0;
  sx=SCR_CENTER;
  maxh=0;
  y=0;
  for (x=0;x<MAX_X;x++) {
    if (ground[x]>maxh)
      maxh=ground[x];
    dx++;
    if (dx==WRLD_RSX) {
      maxh/=WRLD_RSY;
      if (maxh==y)
        putpixel(sx,maxh,GREEN);
      else
        if (maxh>y)
          for (y++;y<=maxh;y++)
            putpixel(sx,y,GREEN);
        else
          for (y--;y>=maxh;y--)
            putpixel(sx,y,GREEN);
      y=maxh;
      putpixel(sx,0,BROWN);
      sx++;
      dx=maxh=0;
    }
  }
  maxh=MAX_Y/WRLD_RSY;
  for (y=0;y<=maxh;y++) {
    putpixel(SCR_CENTER,y,BROWN);
    putpixel(sx,y,BROWN);
  }
  for (x=0;x<SCR_WIDTH;x++)
    putpixel(x,(SCR_MNSH+2),GREEN);
}

void initwobj(void)
{
  int x;
  object* ob;
  OLDWDISP* ow;
  ow=wdisp;
  ob=nobjects;
  for (x=0;x<MAX_OBJS;x++,ow++,ob++) {
    ow->ow_xorplot=0;
    ob->drawflag=FALSE;
    ob->deleteflag=FALSE;
  }
  for (x=0;x<MAX_TARG;x++) {
    ob=targets[x];
    if (ob!=NULL && ob->state!=FINISHED)
      dispwobj(ob);
}

void useoffscreenbuf(void)
{
  dispseg=_DS;
  dispoff=auxdisp-0x1000;
  disproff=0x1000;
}

void useonscreenbuf(void)
{
  dispseg=SCR_SEG;
  dispoff=0;
  disproff=SCR_ROFF;
}

void movedisp(void)
{
  swsetblk(0,SCR_SEG,0x1000,0);
  swsetblk(SCR_ROFF,SCR_SEG,0x1000,0);
  movblock(auxdisp,_DS,0x1000,SCR_SEG,0x1000);
  movblock(auxdisp+0x1000,_DS,0x3000,SCR_SEG,0x1000);
}

void clrdispa(void)
{
  setmem(auxdisp,0x2000,0);
}

void initobjs(void)
{
  object* ob;
  int o;
  topobj.nextx=topobj.next=&botobj;
  botobj.prevx=botobj.prev=&topobj;
  topobj.x=-32767;
  botobj.x=32767;
  objbot=objtop=deltop=delbot=NULL;
  objfree=ob=nobjects;
  for (o=0;o<MAX_OBJS;o++) {
    ob->next=ob+1;
    (ob++)->index=o;
  }
  ob--;
  ob->next=NULL;
}

void createremoteplane(int state)
{
  object* plane=createplane(NULL);
  plane->display_func=displayremoteplane;
  plane->update_func=updateremoteplane;
  plane->colour=((plane->index&1)==0 ? CYAN : MAGENTA);
  plane->owner=plane;
  plane->state=state;
  movmem(plane,&oobjects[plane->index],sizeof(object));
}

void createcomputerplane(object* pl)
{
  object* plane=createplane(pl);
  if (pl==NULL) {
    plane->display_func=displaycomputerplane;
    plane->update_func=updatecomputerplane;
    plane->colour=MAGENTA;
    if (!multiplayer)
      plane->owner=&nobjects[1];
    else
      if (plane->index==1)
        plane->owner=plane;
      else
        plane->owner=plane-2;
    movmem(plane,&oobjects[plane->index],sizeof(object));
  }
  if (playmode==SINGLE || playmode==NOVICE) {
    plane->state=FINISHED;
    deletex(plane);
  }
}

void createplayerplane(object* player)
{
  object* plane=createplane(player);
  if (player==NULL) {
    plane->display_func=displayplayerplane;
    plane->update_func=updateplayerplane;
    plane->colour=plane->index%2+1;
    plane->owner=plane;
    movmem(plane,&oobjects[plane->index],sizeof(object));
    goingsun=FALSE;
    endcount=1;
  }
  displx=plane->x-SCR_CENTER;
  disprx=displx+SCR_WIDTH-1;
  flushkeybuf();
}

object* createplane(object* pl)
{
  static int runwayx[MAX_PLYR]={1270,588,1330,1360,1630,1660,2456,1720};
  static bool runwayleft[MAX_PLYR]={FALSE,FALSE,FALSE,FALSE,TRUE,TRUE,TRUE,TRUE};
  static int singlerunways[2]={0,7};
  static int computerrunways[4]={0,7,1,6};
  static int multiplerunways[8]={0,7,3,4,2,5,1,6};

  object* plane;
  int x,height,minx,maxx,runway;
  if (pl==NULL)
    plane=allocobj();
  else
    plane=pl;
  switch (playmode) {
    case SINGLE:
    case NOVICE:
      runway=singlerunways[plane->index];
      break;
    case MULTIPLE:
    case ASYNCH:
      runway=multiplerunways[plane->index];
      break;
    case COMPUTER:
      runway=computerrunways[plane->index];
      break;
  }
  plane->type=PLANE;
  plane->x=runwayx[runway];
  minx=plane->x;
  maxx=plane->x+20;
  height=0;
  for (x=minx;x<=maxx;x++)
    if (ground[x]>height)
      height=ground[x];
  plane->y=height+13;
  plane->xfrac=0;
  plane->yfrac=0;
  plane->speed=0;
  plane->flaps=0;
  plane->accel=0;
  plane->hitcounter=0;
  plane->bomb_delay=0;
  plane->missile_delay=0;
  plane->starburst_delay=0;
  setvel(plane,0,0);
  plane->inverted=runwayleft[runway];
  plane->angle=(plane->inverted ? (ANGLES/2) : 0);
  plane->target=NULL;
  plane->firing=FALSE;
  plane->missile_target=NULL;
  plane->bombing=FALSE;
  plane->starburst_firing=FALSE;
  plane->goinghome=FALSE;
  plane->height=SYM_HEIGHT;
  plane->width=SYM_WIDTH;
  plane->athome=TRUE;
  if (pl==NULL || plane->state==CRASHED || plane->state==GHOSTCRASHED) {
    plane->ammo=MAX_AMMO;
    plane->bombs=MAX_BOMBS;
    plane->missiles=MAX_MISSILES;
    plane->starbursts=MAX_STARBURSTS;
    plane->life=MAX_FUEL;
  }
  if (pl==NULL) {
    plane->score=0;
    plane->crashes=0;
    endstatuses[plane->index]=0;
    compnear[plane->index]=NULL;
    insertx(plane,&topobj);
  }
  else {
    deletex(plane);
    insertx(plane,plane->nextx);
  }
  if (multiplayer && plane->crashes>=maxcrash) {
    plane->state=GHOST;
    if (plane->index==playerindex)
      ghost=TRUE;
  }
  else
    plane->state=FLYING;
  return plane;
}

void createbullet(object* obo,object* targ)
{
  object* bullet;
  int nangle,nspeed,dx,dy,r,bspeed,x,y;
  if (targ==NULL && !compplane && !obo->ammo)
    return;
  bullet=allocobj();
  if (bullet==NULL)
    return;
  obo=obop;
  if (playmode!=NOVICE)
    obo->ammo--;
  bspeed=BULSPEED+level;
  if (targ!=NULL) {
    x=targ->x+(targ->xv<<2);
    y=targ->y+(targ->yv<<2);
    dx=x-obo->x;
    dy=y-obo->y;
    r=isrange(x,y,obo->x,obo->y);
    if (r<1) {
      deallobj(bullet);
      return;
    }
    bullet->xv=(dx*bspeed)/r;
    bullet->yv=(dy*bspeed)/r;
    bullet->xvfrac=bullet->yvfrac=0;
  }
  else {
    nspeed=obo->speed+bspeed;
    nangle=obo->angle;
    setvel(bullet,nspeed,nangle);
  }
  bullet->type=SHOT;
  bullet->x=obo->x+SYM_WIDTH/2;
  bullet->y=obo->y-SYM_HEIGHT/2;
  bullet->xfrac=obo->xfrac;
  bullet->yfrac=obo->yfrac;
  bullet->life=BULLIFE;
  bullet->owner=obo;
  bullet->colour=obo->colour;
  bullet->height=bullet->width=1;
  bullet->display_func=NULL;
  bullet->update_func=updatebullet;
  bullet->speed=0;
  insertx(bullet,obo);
}

int isrange(int x,int y,int ax,int ay)
{
  int dx,dy,t;
  dy=abs(y-ay);
  dy+=(dy>>1);
  dx=abs(x-ax);
  if (dx>100 || dy>100)
    return -1;
  if (dx<dy) {
    t=dx;
    dx=dy;
    dy=t;
  }
  return ((7*dx)+(dy<<2))>>3;
}

void createbomb(object* plane)
{
  object* bomb; /* Someone set us up the bomb! Sorry. */
  int angle;
  plane=obop;
  if ((!compplane && !plane->bombs) || plane->bomb_delay!=0)
    return;
  bomb=allocobj();
  if (bomb==NULL)
    return;
  if (playmode!=NOVICE)
    plane->bombs--;
  plane->bomb_delay=10;
  bomb->type=BOMB;
  bomb->state=FALLING;
  bomb->xv=plane->xv;
  bomb->yv=plane->yv;
  if (plane->inverted)
    angle=(plane->angle+(ANGLES/4))%ANGLES;
  else
    angle=(plane->angle+(3*ANGLES/4))%ANGLES;
  bomb->x=plane->x+(fcos(10,angle)>>8)+4;
  bomb->y=plane->y+(fsin(10,angle)>>8)-4;
  bomb->xfrac=bomb->yfrac=bomb->xvfrac=bomb->yvfrac=0;
  bomb->life=BOMBLIFE;
  bomb->owner=plane;
  bomb->colour=plane->colour;
  bomb->height=bomb->width=8;
  bomb->display_func=displaybomb;
  bomb->update_func=updatebomb;
  insertx(bomb,plane);
}

void createmissile(object* plane)
{
  object* missile;
  int angle, nspeed;
  if (plane->missile_delay!=0 || plane->missiles==0 || !missok)
    return;
  missile=allocobj();
  if (missile==NULL)
    return;
  if (playmode!=NOVICE)
    plane->missiles--;
  plane->missile_delay=5;
  missile->type=MISSILE;
  missile->state=FLYING;
  angle=missile->angle=plane->angle;
  missile->x=plane->x+(fcos(1,angle)>>4)+4;
  missile->y=plane->y+(fsin(1,angle)>>4)-4;
  missile->xfrac=missile->yfrac=0;
  missile->speed=nspeed=gmaxspeed+(gmaxspeed>>1);
  setvel(missile,nspeed,angle);
  missile->life=MISSLIFE;
  missile->owner=plane;
  missile->colour=plane->colour;
  missile->height=missile->width=8;
  missile->display_func=displaymissile;
  missile->update_func=updatemissile;
  missile->target=plane->missile_target;
  missile->inverted=FALSE;
  missile->accel=missile->flaps=0;
  insertx(missile,plane);
}

void createstarburst(object* obo)
{
  object* ob;
  int angle;
  if (obo->starburst_delay || !obo->starbursts || !missok)
    return;
  ob=allocobj();
  if (ob==NULL)
    return;
  ob->starburst_delay=5;
  if (playmode!=NOVICE)
    obo->starbursts--;
  ob->type=STARBURST;
  ob->state=FALLING;
  if (obo->inverted)
    angle=(obo->angle+(3*ANGLES/8))%ANGLES;
  else
    angle=(obo->angle+(5*ANGLES/8))%ANGLES;
  setvel(ob,gminspeed,angle);
  ob->xv+=obo->xv;
  ob->yv+=obo->yv;
  ob->x=obo->x+(fcos(10,angle)>>10)+4;
  ob->y=obo->y+(fsin(10,angle)>>10)-4;
  ob->xfrac=ob->yfrac=0;
  ob->life=BURSTLIFE;
  ob->owner=obo;
  ob->colour=obo->colour;
  ob->height=ob->width=8;
  ob->display_func=displaystarburst;
  ob->update_func=updatestarburst;
  insertx(ob,obo);
}

void createtargets(void)
{
  static int targetx[MAX_TARG]={
     191, 284, 409, 539, 685, 807, 934,1210,1240,1440,
    1550,1750,1780,2024,2159,2279,2390,2549,2678,2763};
  static int targettype[MAX_TARG]={
    TARGET_CHIMNEY,TARGET_TANK,TARGET_CHIMNEY,TARGET_CHINMEY,TARGET_TANK,
    TARGET_FLAG,TARGET_CHIMNEY,TARGET_FUEL,TARGET_FLAG,TARGET_CHIMNEY,
    TARGET_TANK,TARGET_FLAG,TARGET_FUEL,TARGET_CHIMNEY,TARGET_CHIMNEY,
    TARGET_TANK,TARGET_TANK,TARGET_FLAG,TARGET_FLAG,TARGET_CHIMNEY};

  object* target;
  int x,i;
  int minh,maxh,aveh,minx,maxx;
  if (!truemultiplayer) {
    numtarg[0]=0;
    numtarg[1]=MAX_TARG-3;
  }
  else
    numtarg[0]=numtarg[1]=MAX_TARG/2;
  for (i=0;i<MAX_TARG;i++) {
    targets[i]=target=allocobj();
    minx=target->x=targetx[i];
    maxx=target->x+15;
    minh=999;
    maxh=0;
    for (x=minx;x<=maxx;x++) {
      if (ground[x]>maxh)
        maxh=ground[x];
      if (ground[x]<minh)
        minh=ground[x];
    }
    aveh=(minh+maxh)>>1;
    while ((target->y=aveh+16)>=MAX_Y)
      aveh--;
    for (x=minx;x<=maxx;x++)
      ground[x]=aveh;
    target->xv=0;
    target->yv=0;
    target->xfrac=0;
    target->yfrac=0;
    target->xvfrac=0;
    target->yvfrac=0;
    target->angle=0;
    target->hitcounter=0;
    target->type=TARGET;
    target->state=STANDING;
    target->subtype=targettype[i];
    target->life=i;
    if (!truemultiplayer)
      target->owner=&nobjects[(i<MAX_TARG/2 && i>MAX_TARG/2-4) ? 0 : 1];
    else
      target->owner=&nobjects[i>=MAX_TARG/2 ? 0 : 1];
    target->colour=target->owner->colour;
    target->height=target->width=16;
    target->display_func=displaytarget;
    target->update_func=updatetarget;
    insertx(target,&topobj);
  }
}

void createexplosion(object* obo,int small)
{
  object* frag;
  int i,ic,life,speed;
  int obox,oboy,obodx,obody,oboclr,obotype;
  bool mansym;
  int subtype;
  obox=obo->x+(obo->width>>1);
  oboy=obo->y+(obo->height>>1);
  obodx=obo->xv>>2;
  obody=obo->yv>>2;
  oboclr=obo->colour;
  obotype=obo->type;
  if (obotype==TARGET && obo->subtype==TARGET_FUEL) {
    ic=1;
    speed=gminspeed;
  }
  else {
    ic=small ? 6 : 2;
    speed=gminspeed>>((explseed&7)!=7 ? 1 : 0);
  }
  mansym=(obotype==PLANE && (obo->state==FLYING || obo->state==WOUNDED));
  for (i=1;i<=15;i+=ic) {
    frag=allocobj();
    if (frag==NULL)
      return;
    frag->type=EXPLOSION;
    setvel(frag,speed,i);
    frag->xv+=obodx;
    frag->yv+=obody;
    frag->x=obox+frag->xv;
    frag->y=oboy+frag->yv;
    explseed=(frag->x)*(frag->y)*explseed+7491;
    if (explseed==0)
      explseed=74917777;
    frag->life=EXPLLIFE;
    subtype=frag->subtype=(explseed&0x1c0)>>6;
    if (mansym && (subtype==0 || subtype==7)) {
      mansym=subtype=frag->subtype=0;
      frag->xv=obodx;
      frag->yv=-gminspeed;
    }
    frag->xfrac=frag->yfrac=frag->hitcounter=frag->speed=0;
    frag->owner=obo;
    frag->colour=oboclr;
    frag->height=frag->width=8;
    frag->display_func=displayfrag;
    frag->update_func=updatefrag;
    if (subtype!=0)
      initsound(frag,SOUND_EXPLOSION);
    insertx(frag,obo);
  }
}

void createsmoke(object* obo)
{
  object* smoke=allocobj();
  if (smoke==NULL)
    return;
  smoke->type=SMOKE;
  smoke->x=obo->x+8;
  smoke->y=obo->y-8;
  smoke->xv=obo->xv;
  smoke->yv=obo->yv;
  smoke->xfrac=smoke->yfrac=smoke->xvfrac=smoke->yvfrac=0;
  smoke->life=SMOKELIFE;
  smoke->owner=obo;
  smoke->height=smoke->width=1;
  smoke->display_func=NULL;
  smoke->update_func=updatesmoke;
  smoke->colour=obo->colour;
}


void createflocks(void)
{
  static int ifx[]={MINFLCKX,MINFLCKX+1000,MAXFLCKX-1000,MAXFLCKX};
  static int ify[]={MAX_Y-1,MAX_Y-1,MAX_Y-1,MAX_Y-1};
  static int ifdx[]={2,2,-2,-2};

  object* flock;
  int i,j;
  if (playmode==NOVICE)
    return;
  for (i=0;i<MAX_FLCK;i++) {
    flock=allocobj();
    if (flock==NULL)
      return;
    flock->type=FLOCK;
    flock->state=FLYING;
    flock->x=ifx[i];
    flock->y=ify[i];
    flock->xv=ifdx[i];
    flock->yv=flock->xfrac=flock->yfrac=flock->xvfrac=flock->yvfrac=0;
    flock->inverted=FALSE;
    flock->life=FLOCKLIFE;
    flock->owner=flock;
    flock->height=flock->width=16;
    flock->display_func=displayflock;
    flock->update_func=updateflock;
    flock->colour=9;
    insertx(flock,&topobj);
    for (j=0;j<MAX_BIRD;j++)
      createbird(flock,1);
  }
}

void createbird(object* obo,int i)
{
  object* bird;
  static ibx[]={8,3,0,6,7,14,10,12};
  static iby[]={16,1,8,3,12,10,7,14};
  static ibxv[]={-2,2,-3,3,-1,1,0,0};
  static ibyv[]={-1,-2,-1,-2,-1,-2,-1,-2};
  bird=allocobj();
  if (bird==NULL)
    return;
  bird->type=BIRD;
  bird->x=obo->x+ibx[i];
  bird->y=obo->y-iby[i];
  bird->xv=ibxv[i];
  bird->yv=ibyv[i];
  bird->subtype=FALSE;
  bird->xfrac=bird->yfrac=bird->xvfrac=bird->yvfrac=0;
  bird->life=BIRDLIFE;
  bird->owner=obo;
  bird->height=2;
  bird->width=4;
  bird->display_func=displaybird;
  bird->update_func=updatebird;
  bird->colour=obo->colour;
  insertx(bird,obo);
}

void createoxen(void)
{
  static iox[]={1376,1608};
  static ioy[]={80,91};

  object* ox;
  int i;
  if (playmode==NOVICE) {
    for (i=0;i<MAX_OXEN;i++)
      targets[MAX_TARG+i]=NULL;
    return;
  }
  for (i=0;i<MAX_OXEN;i++) {
    targets[MAX_TARG+i]=ox=allocobj();
    if (ox==NULL)
      return;
    ox->type=OX;
    ox->state=STANDING;
    ox->x=iox[i];
    ox->y=ioy[i];
    ox->inverted=FALSE;
    ox->xfrac=ox->yfrac=ox->xvfrac=ox->yvfrac=ox->xv=ox->yv=0;
    ox->owner=ox;
    ox->height=16;
    ox->width=16;
    ox->display_func=NULL;
    ox->update_func=updateox;
    ox->colour=1;
    insertx(ox,&topobj);
  }
}

void checkcollisions(void)
{
  object* ob;
  object* obp;
  object** obkd;
  object** obkr;
  int xmax,ymin,ymax,otype,i;
  int prevx1,prevx2;

  collptr=killptr=0;
  collxadj=2;
  collyadj=1;
  if ((countmove&1)==1) {
    collxadj=-collxadj;
    collyadj=-collyadj;
  }
  useoffscreenbuf();
  prevx1=topobj.x;
  for (ob=topobj.nextx;ob!=&botobj;ob=ob->nextx) {
    prevx2=prevx1=ob->x;
    xmax=ob->x+ob->width-1;
    ymax=ob->y;
    ymin=ymax-ob->height+1;
    for (obp=ob->nextx;obp!=&botobj && obp->x<=xmax;obp=obp->nextx) {
      prevx2=obp->x;
      if (obp->y>=ymin && obp->y-obp->height+1<=ymax)
        colltest(ob,obp);
    }
    otype=ob->type;
    if ((otype==PLANE && ob->state!=FINISHED && ob->state!=WAITING && ob->y<ground[ob->x+8]+24) ||
        ((otype==BOMB || otype==MISSILE) && ob->y<ground[ob->x+4]+12))
      tstcrash(ob);
  }
  obkd=killed;
  obkr=killer;
  for (i=0;i<killptr;i++,obkd++,obkr++)
    kill(*obkd,*obkr);
  obkd=collsno;
  for (i=0;i<collptr;i++,obkd++) {
    ob=*obkd;
    ob->xv=collsdx[i];
    ob->yv=collsdy[i];
  }
}

void colltest(object* ob,object* obp)
{
  object* obp;
  int otype, ttype;
  otype=ob->type;
  ttype=obp->type;
  if ((otype==PLANE && ob->state>=FINISHED) ||
      (ttype==PLANE && obp->state>=FINISHED) ||
      (otype==EXPLOSION && ttype==EXPLOSION))
    return;
  if (ob->y<obp->y) {
    obt=ob;
    ob=obp;
    obp=obt;
  }
  drawobject(15,15,ob);
  if (bitblt(obp->x-ob->x+15,obp->y-ob->y+15,obp))
    if (killptr<(MAX_OBJS<<1)-1) {
      killed[killptr]=ob;
      killer[killptr++]=obp;
      killed[killptr]=obp;
      killer[killptr++]=ob;
    }
  clearscorearea();
}

void tstcrash(object* ob)
{
  int x,xmax,y;
  bool hit=FALSE;
  drawobject(15,15,ob);
  xmax=ob->x+ob->width-1;
  for (x=ob->x;x<=xmax;x++) {
    y=(int)ground[x]-ob->y+15;
    if (y>15) {
      hit=TRUE;
      break;
    }
    if (y<0)
      continue;
    hit=pixel(x-ob->x+15,y,BLACK_R);
    if (hit)
      break;
  }
  clearscorearea();
  if (hit && killptr<(MAX_OBJS<<1)) {
    killed[killptr]=ob;
    killer[killptr++]=NULL;
  }
}

void kill(object* ob,object* obt)
{
  int state,ttype,i;
  ttype=(obt ? obt->type : GROUND);
  if ((ttype==BIRD || ttype==FLOCK) && ob->type!=PLANE)
    return;
  switch (ob->type) {
    case BOMB:
    case MISSILE:
      createexplosion(ob,0);
      ob->life=-1;
      if (!obt)
        crater(ob);
      stopsound(ob);
      return;
    case SHOT:
      ob->life=1;
      return;
    case STARBURST:
      if (ttype==MISSILE || ttype==BOMB || !obt)
        ob->life=1;
      return;
    case EXPLOSION:
      if (!obt) {
        ob->life=1;
        stopsound(ob);
      }
      return;
    case TARGET:
      if (ob->state!=STANDING)
        return;
      if (ttype==EXPLOSION || ttype==STARBURST)
        return;
      if (ttype==SHOT) {
        ob->hitcounter+=TARGHITCOUNT;
        if (ob->hitcounter<=TARGHITCOUNT*(level+1))
          return;
      }
      ob->state=FINISHED;
      createexplosion(ob,0);
      useonscreenbuf();
      dispwobj(ob);
      useoffscreenbuf();
      scoretarg(ob,ob->subtype==TARGET_FUEL ? 200 : 100);
      numtarg[ob->colour-1]--;
      if (numtarg[ob->colour-1]==0)
        endgame(ob->colour);
      return;
    case PLANE:
      state=ob->state;
      if (state==CRASHED || state==GHOSTCRASHED)
        return;
      if (endstatuses[ob->index]==WINNER)
        return;
      if (ttype==STARBURST || (ttype==BIRD && ob->athome))
        return;
      if (!obt) {
        if (state==FALLING) {
          stopsound(ob);
          createexplosion(ob,1);
          crater(ob);
        }
        else
          if (state<FINISHED) {
            scorepln(ob);
            createexplosion(ob,1);
            crater(ob);
          }
        crashplane(ob);
        return;
      }
      if (state>=FINISHED)
        return;
      if (state==FALLING) {
        if (ob->index==playerindex)
          if (ttype==SHOT)
            shothole++;
          else
            if (ttype==BIRD || ttype==FLOCK)
              splatbird++;
        return;
      }
      if (ttype==SHOT || ttype==BIRD || ttype==OX || ttype==FLOCK) {
        if (ob->index==playerindex)
          if (ttype==SHOT)
            shothole++;
          else
            if (ttype==OX)
              splatox++;
            else
              splatbird++;
        if (state==FLYING) {
          ob->state=WOUNDED;
          return;
        }
        if (state==STALLED) {
          ob->state=WOUNDSTALL;
          return;
        }
      }
      else {
        createexplosion(ob,1);
        if (ttype==PLANE) {
          collxadj=-collxadj;
          collsdx[collptr]=((ob->xv+obt->xv)>>1)+collxadj;
          collyadj=-collyadj;
          collsdy[collptr]=((ob->yv+obt->yv)>>1)+collyadj;
          collsno[collptr++]=ob;
        }
      }
      hitplane(ob);
      scorepln(ob);
      return;
    case BIRD:
      ob->life=(scorepenalty(ttype,obt,25) ? -1 : -2);
      return;
    case FLOCK:
      if (ttype!=FLOCK && ttype!=BIRD && ob->state==FLYING) {
        for (i=0;i<8;i++)
          createbird(ob,i);
        ob->life=-1;
        ob->state=FINISHED;
      }
      return;
    case OX:
      if (ob->state!=STANDING)
        return;
      if (ttype==EXPLOSION || ttype==STARBURST)
        return;
      scorepenalty(ttype,obt,200);
      ob->state=FINISHED;
      return;
  }
}

void crater(object* ob)
{
  static int crtdepth[8]={1,2,2,3,3,2,2,1};
  int i,x,y,ymin,ymax;
  int xmin=ob->x+(ob->width-8)/2;
  int xmax=xmin+7;
  for (i=0,x=xmin;x<=xmax;i++,x++) {
    ymax=ground[x];
    if ((y=orground[x]-20)<20)
      y=20;
    ymin=ymax-crtdepth[i]+1;
    if (ymin<=y)
      ymin=y+1;
    ground[x]=ymin-1;
  }
  forcdisp=TRUE;
}

bool scorepenalty(int ttype,object* obt,int score)
{
  if (ttype==SHOT || ttype==BOMB || ttype==MISSILE ||
      (ttype==PLANE && (obt->state==FLYING || obt->state==WOUNDED || (obt->state==FALLING && obt->hitcounter==FALLCOUNT))
       && !obt->athome)) {
    scoretarg(obt,score);
    return TRUE;
  }
  return FALSE;
}

void scoretarg(object* ob,int score)
{
  if (!truemultiplayer) {
    if (ob->colour==1)
      nobjects[0].score-=score;
    else
      nobjects[0].score+=score;
    dispscore(&nobjects[0]);
  }
  else {
    nobjects[ob->colour==CYAN ? 1 : 0].score+=score;
    dispscore(&nobjects[ob->colour==CYAN ? 1 : 0]);
  }
}

void scorepln(object* ob)
{
  scoretarg(ob,50);
}

void dispscore(object* ob)
{
  swposcur((ob->colour-1)*7+2,24);
  setcolour(ob->colour);
  dispd(ob->score,6);
}

void timerint(void)
{
  counttick++;
  movetick+=10;
  soundadj();
}

void displayplayerplane(object* plane)
{
  if (shothole)
    dispwindshot();
  if (splatbird)
    dispsplatbird();
  plnsound(plane);
}

void displaybomb(object* bomb)
{
  if (bomb->yv<=0)
    sound(SOUND_BOMB,-bomb->y,bomb);
}

void displaymissile(object* missile)
{
}

void displaystarburst(object* starburst)
{
}

void displayfrag(object* ob)
{
  if (ob->subtype!=0)
    sound(SOUND_EXPLOSION,ob->hitcounter,ob);
}

void displaycomputerplane(object* plane)
{
  plnsound(plane);
}

void displayremoteplane(object* plane)
{
  plnsound(plane);
}

void displaytarget(object* target)
{
  if (target->firing)
    sound(SOUND_SHOT,0,target);
}

void displayflock(object* flock)
{
}

void displaybird(object* bird)
{
}

void plnsound(object* plane)
{
  if (plane->firing)
    sound(SOUND_SHOT,0,plane);
  else
    switch (plane->state) {
      case FALLING:
        if (plane->yv>=0)
          sound(SOUND_HIT,0,plane);
        else
          sound(SOUND_FALLING,plane->y,plane);
        break;
      case FLYING:
        sound(SOUND_PLANE,-plane->speed,plane);
        break;
      case STALLED:
      case WOUNDED:
      case WOUNDSTALL:
        sound(SOUND_HIT,0,plane);
        break;
      default:
        break;
    }
}

void dispwobj(object* ob)
{
  OLDWDISP *ow=&wdisp[ob->index];
  int ox,oy,oldplot;
  if (ow->ow_xorplot)
    putpixel(ow->ow_x,ow->ow_y,ow->ow_xorplot-1);
  if (ob->state>=FINISHED)
    ow->ow_xorplot=0;
  else {
    ow->ow_x=SCR_CENTER+(ob->x+ob->width/2)/WRLD_RSX;
    ow->ow_y=(ob->y-ob->height/2)/WRLD_RSY;
    oldplot=pixel(ow->ow_x,ow->ow_y,ob->owner->colour);
    if (oldplot==0 || (oldplot&3)==3) {
      ow->ow_xorplot=oldplot+1;
      return;
    }
    putpixel(ow->ow_x,ow->ow_y,oldplot);
    ow->ow_xorplot=0;
  }
}

bool updateremoteplane(object* plane)
{
  planeisplayer=compplane=FALSE;
  currobx=plane->index;
  endstatus=endstatuses[currobx];
  if (!dispcnt)
    interpret(plane,playmode==MULTIPLE ? multget(plane) : asynget(plane));
  else {
    plane->flaps=0;
    plane->bombing=FALSE;
  }
  if ((plane->state==CRASHED || plane->state==GHOSTCRASHED) && plane->hitcount<=0)
    if (plane->life>QUIT) {
      plane->crashes++;
      createplane(plane);
    }
  return updateplane(plane);
}

int asynget(object* ob)
{
  int keys,c;
  if (ob->index==playerindex) {
    keys=lastkey;
    lastkey=0;
  }
  else {
    /* get "keys" from port */
    return histmult(ob->index,keys);
  }
}


int multget(object* plane)
{
  int i=plane->index;
  if (i!=playerindex)
    updstate(plane,netbuf.states[i]);
  return histmult(i,netbuf.keys[i]);
}

void updstate(object* plane,int state)
{
  if (plane->state!=state && (state==FINISHED || state==WAITING || plane->state==FINISHED || plane->state==WAITING)) {
    plane->state=state;
    useonscreenbuf();
    dispwobj(plane);
  }
}

int histmult(int p,int keys)
{
  /* Dummy */
  return keys;
}

int inithistory(int randno)
{
  long historybufsize;
  FILE *inputfile;
  if (playbackfilename!=NULL || recordfilename!=NULL) {
    historybufsize=farcoreleft()
    historybuf=(int huge *)farmalloc(historybufsize);
    if (historybuf==0)
      freeandexit("Unable to allocate history memory");
    historyp=(int huge *)historybuf;
  }
  if (playbackfilename!=NULL) {
    inputfile=fopen(playbackfilename,"rb");
    if (inputfile==NULL)
      freeandexit("Unable to open history input file");
    fseek(inputfile,0,2);
    historyfilelen=ftell(inputfile);
    if (historybufsize<historyfilelen)
      freeandexit("Insufficient memory to load history file");
    historyspace=historybufsize-historyfilelen;
    fseek(inputfile,0,0);
    ffread(inputfile,(char huge *)historybuf,(int)historyfilelen);
    fclose(inputfile);
    randno=historyp[0];
    historyp+=2;
    historyfilelen-=4;
  }
  if (recordfilename!=NULL) {
    outputfile=fopen(recordfilename,"wb");
    if (outputfile==NULL)
      freeandexit("Unable to open history output file");
    if (playbackfilename==NULL) {
      historyfilelen=historybufsize;
      historyp[0]=randno;
      historyp[1]=(int)(historybufsize>>4);
      historyp+=2;
      historyfilelen-=4;
    }
  }
  return randno;
}

void freehistorybuf(void)
{
  if (historybuf!=NULL)
    farfree((void far *)historybuf);
}

void freeandexit(char *errmsg)
{
  puts(errmsg);
  freehistorybuf();
  exit(0);
}

int history(int keys)
{
  if (playbackfilename!=NULL)
    if (keys!=0)
      playbackfilename=NULL;
    else {
      if (historyp[0]==frametick) {
        keys=historykeys=historyp[1];
        historyp+=2;
        historyfilelen-=4;
        if (historyfilelen==0) {
          playbackfilename=NULL;
          historyfilelen=historyspace;
        }
      }
      return historykeys;
    }
  if (recordfilename!=NULL && keys!=historykeys) {
    historyp[0]=frametick;
    historyp[1]=keys;
    recording=TRUE;
    historykeys=keys;
    historyp+=2;
    historyfilelen-=4;
    if (historyfilelen==0)
      recordfilename=NULL;
    return historykeys;
  }
  return keys;
}

/* This function saves a far block to a file */
void ffwrite(FILE *fp,char huge *d,unsigned long l)
{
  char buf[1024];
  unsigned long a;
  for (a=0;a<(l|1023)-1023;a+=1024) {
    movedata(FP_SEG((unsigned long)d+a),FP_OFF((unsigned long)d+a),_DS,
             (unsigned int)buf,1024);
    fwrite(buf,1024,1,fp);
  }
  if ((l&1023)!=0) {
    movedata(FP_SEG((unsigned long)d+a),FP_OFF((unsigned long)d+a),_DS,
             (unsigned int)buf,(int)l&1023);
    fwrite(buf,(unsigned int)(l&1023),1,fp);
  }
} /* ffwrite */

void flushhistory(void)
{
  if (recording)
    ffwrite(outputfile,(char huge *)historybuf,(int)(historyp-historybuf)*sizeof(int));
  if (outputfile!=NULL) {
    fclose(outputfile);
    freehistorybuf();
  }
}

void setvel(object *obj,int v,int dir)
{
  int xv=fcos(v,dir),yv=fsin(v,dir);
  obj->xv=xv>>8;
  obj->xvfrac=xv<<8;
  obj->yv=yv>>8;
  obj->yvfrac=yv<<8;
}

void puts(char *str)
{
  while (*str!=0)
    swputc(*(str++));
}

void moveobject(object *obj,int *x,int *y)
{
  long pos,vel;
  pos=(((long)(obj->x))<<16)+obj->xfrac;
  vel=(((long)(obj->xv))<<16)+obj->xvfrac;
  pos+=vel;
  obj->x=(short)(pos>>16);
  obj->xfrac=(short)pos;
  *x=obj->x;
  pos=(((long)(obj->y))<<16)+obj->yfrac;
  vel=(((long)(obj->yv))<<16)+obj->yvfrac;
  pos+=vel;
  obj->y=(short)(pos>>16);
  obj->yfrac=(short)pos;
  *y=obj->y;
}

void dispd(int n,int size)
{
  int i=0;
  int d,t;
  bool first=TRUE;
  if (n<0) {
    n=-n;
    swputc('-');
    i++;
  }
  for (t=10000;t>1;n%=t,t/=10) {
    d=n/t;
    if (d!=0 || !first) {
      first=FALSE;
      swputc(d+'0');
      i++;
    }
  }
  swputc(n+'0');
  i++;
  while(++i<=size)
    swputc(' ');
}

object* allocobj(void)
{
  object* ob;
  if (objfree==NULL)
    return NULL;
  ob=objfree;
  objfree=ob->next;
  ob->next=NULL;
  ob->prev=objbot;
  if (objbot)
    objbot->next=ob;
  else
    objtop=ob;
  ob->tonetab=NULL;
  ob->drawflag=FALSE;
  ob->deleteflag=FALSE;
  if (ob>objsmax)
    objsmax=ob;
  objbot=ob;
  return ob;
}

void deallobj(object* ob)
{
  object* obb=ob->prev;
  if (obb!=NULL)
    obb->next=ob->next;
  else
    objtop=ob->next;
  obb=ob->next;
  if (obb!=NULL)
    obb->prev=ob->prev;
  else
    objbot=ob->prev;
  ob->next=NULL;
  if (delbot)
    delbot->next=ob;
  else
    deltop=ob;
  delbot=ob;
}

unsigned long int seed=74917777ul;

void randsd(void)
{
  seed=seed*countmove+7491;
  if (seed==0)
    seed=74917777;
}

void dispwindshot(void)
{
  object hole;
  hole.type=DUMMYTYPE;
  hole.height=hole.width=16;
  hole.colour=1;
  hole.sprite=swshtsym;
  do {
    randsd();
    drawobject((unsigned)(seed%(SCR_WIDTH-16)),(unsigned)(seed%(SCR_HEIGHT-50))+50,&hole);
    shothole--;
  } while (shothole!=0);
}

void dispsplatbird(void)
{
  object bird;
  bird.type=DUMMYTYPE;
  bird.height=bird.width=32;
  bird.colour=2;
  bird.sprite=swsplsym;
  do {
    randsd();
    drawobject((unsigned)(seed%(SCR_WIDTH-32)),(unsigned)(seed%(SCR_HEIGHT-60))+60,&bird);
    splatbird--;
  } while (splatbird!=0);
}

void dispoxsplat(void)
{
  object* ob;
  int i;
  swsetblk(0,SCR_SEG,((SCR_HEIGHT-SCR_MNSH-2)>>1)*SCR_LINW,0xaa);
  swsetblk(SCR_ROFF,SCR_SEG,((SCR_HEIGHT-SCR_MNSH-3)>>1)*SCR_LINW,0xaa);
  splatox=0;
  oxsplatted=TRUE;
  ob=nobjects;
  for (i=0;i<MAX_OBJS;i++,ob++) {
    ob->drawflag=FALSE;
    ob->deleteflag=FALSE;
  }
}

void clearscorearea(void)
{
  cgafbar(0,184,48,16,0);
}

void drawobject(int x,int y,object *obj)
{
  putimage(x,y,obj->sprite,obj);
}

unsigned char blut[256]={
0x00,0x03,0x03,0x03,0x0c,0x0f,0x0f,0x0f,0x0c,0x0f,0x0f,0x0f,0x0c,0x0f,0x0f,0x0f,
0x30,0x33,0x33,0x33,0x3c,0x3f,0x3f,0x3f,0x3c,0x3f,0x3f,0x3f,0x3c,0x3f,0x3f,0x3f,
0x30,0x33,0x33,0x33,0x3c,0x3f,0x3f,0x3f,0x3c,0x3f,0x3f,0x3f,0x3c,0x3f,0x3f,0x3f,
0x30,0x33,0x33,0x33,0x3c,0x3f,0x3f,0x3f,0x3c,0x3f,0x3f,0x3f,0x3c,0x3f,0x3f,0x3f,
0xc0,0xc3,0xc3,0xc3,0xcc,0xcf,0xcf,0xcf,0xcc,0xcf,0xcf,0xcf,0xcc,0xcf,0xcf,0xcf,
0xf0,0xf3,0xf3,0xf3,0xfc,0xff,0xff,0xff,0xfc,0xff,0xff,0xff,0xfc,0xff,0xff,0xff,
0xf0,0xf3,0xf3,0xf3,0xfc,0xff,0xff,0xff,0xfc,0xff,0xff,0xff,0xfc,0xff,0xff,0xff,
0xf0,0xf3,0xf3,0xf3,0xfc,0xff,0xff,0xff,0xfc,0xff,0xff,0xff,0xfc,0xff,0xff,0xff,
0xc0,0xc3,0xc3,0xc3,0xcc,0xcf,0xcf,0xcf,0xcc,0xcf,0xcf,0xcf,0xcc,0xcf,0xcf,0xcf,
0xf0,0xf3,0xf3,0xf3,0xfc,0xff,0xff,0xff,0xfc,0xff,0xff,0xff,0xfc,0xff,0xff,0xff,
0xf0,0xf3,0xf3,0xf3,0xfc,0xff,0xff,0xff,0xfc,0xff,0xff,0xff,0xfc,0xff,0xff,0xff,
0xf0,0xf3,0xf3,0xf3,0xfc,0xff,0xff,0xff,0xfc,0xff,0xff,0xff,0xfc,0xff,0xff,0xff,
0xc0,0xc3,0xc3,0xc3,0xcc,0xcf,0xcf,0xcf,0xcc,0xcf,0xcf,0xcf,0xcc,0xcf,0xcf,0xcf,
0xf0,0xf3,0xf3,0xf3,0xfc,0xff,0xff,0xff,0xfc,0xff,0xff,0xff,0xfc,0xff,0xff,0xff,
0xf0,0xf3,0xf3,0xf3,0xfc,0xff,0xff,0xff,0xfc,0xff,0xff,0xff,0xfc,0xff,0xff,0xff,
0xf0,0xf3,0xf3,0xf3,0xfc,0xff,0xff,0xff,0xfc,0xff,0xff,0xff,0xfc,0xff,0xff,0xff
};

int bitblt(int x,int y,object *obj)
{
  unsigned int linediff,bltreg;
  unsigned char far *scp;
  int width,height,border;
  unsigned char retval=0,shift,bltleft;
  unsigned char *p=obj->sprite;
  if (obj->height==1 && obj->width==1)
    return pixel(x,y,(int)p);
  shift=8-((x&3)<<1);
  width=(obj->width)>>2;
  border=width-(80-(x>>2));
  if (border>0)
    width=80-(x>>2);
  height=(obj->height>y+1 ? y+1 : obj->height);
  scp=(unsigned char far *)MK_FP(dispseg,dispoff+((199-y)>>1)*80+(x>>2));
  linediff=disproff;
  if ((y&1)==0) {
    scp+=linediff;
    linediff=80-linediff;
  }
  do {
    bltleft=0;
    for (x=0;x<width;x++) {
      bltreg=((*p++)<<shift)|(bltleft<<8);
      retval|=(*scp)&blut[bltreg>>8];
      *(scp++)^=(bltreg>>8);
      bltleft=bltreg;
    }
    if (border>=0)
      p+=border;
    else
      if (bltleft!=0) {
        retval|=(*scp)&blut[bltleft];
        (*scp)^=bltleft;
      }
    scp+=linediff-width;
    linediff=80-linediff;
    height--;
  } while (height!=0);
  return retval;
}

void putimage(int x,int y,unsigned char *p,object *obj)
{
  unsigned int linediff,bltreg;
  unsigned char far *scp;
  int width,height,border;
  unsigned char shift,bltleft,col;
  if (obj->height==1 && obj->width==1) {
    putpixel(x,y,(int)p);
    return;
  }
  col=(obj->colour==1 ? 0 : 0xff);
  shift=8-((x&3)<<1);
  width=(obj->width)>>2;
  border=width-(80-(x>>2));
  if (border>0)
    width=80-(x>>2);
  height=(obj->height>y+1 ? y+1 : obj->height);
  scp=(unsigned char far *)MK_FP(dispseg,dispoff+((199-y)>>1)*80+(x>>2));
  linediff=disproff;
  if ((y&1)==0) {
    scp+=linediff;
    linediff=80-linediff;
  }
  do {
    bltleft=0;
    for (x=0;x<width;x++) {
      bltreg=((*p++)<<shift)|(bltleft<<8);
      *(scp++)^=(bltreg>>8)^(blut[bltreg>>8]&col);
      bltleft=bltreg;
    }
    if (border>=0)
      p+=border;
    else
      if (bltleft!=0)
        (*scp)^=bltleft^(blut[bltleft]&col);
    scp+=linediff-width;
    linediff=80-linediff;
    height--;
  } while (height!=0);
}

void putpixel(int x,int y,int c)
{
  int shift=(3-(x&3))<<1;
  unsigned char far *scp=(unsigned char far *)MK_FP(dispseg,dispoff+((199-y)>>1)*80+(x>>2)+((y&1)==0 ? disproff : 0));
  if ((c&0x80)==0)
    *scp=((*scp)&(~(3<<shift)))|(c<<shift);
  else
    *scp^=((c&0x7f)<<shift);
}

int pixel(int x,int y,int c)
{
  int shift=(3-(x&3))<<1;
  unsigned char far *scp=(unsigned char far *)MK_FP(dispseg,dispoff+((199-y)>>1)*80+(x>>2)+((y&1)==0 ? disproff : 0));
  unsigned char o=(3<<shift)&(*scp);
  if ((c&0x80)==0) {
    *scp^=o;
    *scp|=(c<<shift);
  }
  else
    *scp^=(c&0x7f)<<shift;
  return o>>shift;
}
