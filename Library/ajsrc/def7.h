/* Source code for Sopwith

   Copyright (c) 1984-2000 David L Clark
   Copyright (c) 1999-2001 Andrew Jenner

   All rights reserved except as specified in the file license.txt.
   Distribution of this file without the license.txt file accompanying is
   prohibited.
*/

#define MAX_X        3000            /*  Maximum X coordinate            */
#define MAX_Y        200             /*  Maximum Y coordinate            */
#define MIN_SPEED    4               /*  Minimum plane speed             */
#define MAX_SPEED    8               /*  Maximum plane speed             */
#define MAX_THROTTLE 4               /*  Maximum acceleration            */

#define MAXCRCOUNT   10              /*  Number of turns as crashed      */
#define FALLCOUNT    10              /*  Moves between falling plane adj */
#define STALLCOUNT   6               /*  Moves between stalling plane adj*/
#define TARGHITCOUNT 10              /*  Target hit count before explod'n*/

#define SCR_WIDTH  320             /*  Screen Width                    */
#define SCR_HEIGHT 200             /*  Screen Height                   */
#define SCR_CENTER 152             /*  Centre column of screen         */
#define SCR_SEG    0xb800          /*  Screen Video segment            */
#define SCR_ROFF   0x2000          /*  Screen odd raster line offset   */
#define SCR_LINW   80              /*  Screen line width in bytes      */
#define SCR_MNSH   16              /*  Minumum line number to shift    */
#define SCR_MXSH   75              /*  Maximum line number to shift    */
#define SCR_LIMIT  180             /*  Screen shift limits             */

#define WRLD_RSX        (MAX_X/SCR_WIDTH*2+1) /*  World display X and  */
#define WRLD_RSY        (MAX_Y/SCR_MNSH+1)     /*  Y divisors           */

#define MINFLCKX        (SCR_WIDTH+50)     /*  Bird flock travel    */
#define MAXFLCKX        (MAX_X-MINFLCKX)  /*    limits             */

#define PLANESGAUGEX    (SCR_CENTER-25) /* Crash, fuel, bomb, shot, missile*/
#define FUELGAUGEX      (SCR_CENTER-22) /*    and starburst guage          */
#define BOMBGAUGEX      (SCR_CENTER-19) /*    X-coordinates                */
#define AMMOGAUGEX      (SCR_CENTER-16)
#define MISSILEGAUGEX   (SCR_CENTER-13)
#define STARBURSTGAUGEX (SCR_CENTER-10)
#define GHOSTX          (SCR_CENTER-21) /* Ghost face display x-coodinate  */

#define HITSYMS         2               /*  Number of hit symbols per plane */
#define ANGLES          16              /*  Number of angle increments      */
#define ORIENTS         2               /*  Number of plane orientations    */
#define SYMBYTES        64              /*  Bytes in a symbol               */
#define WINSIZES        4               /*  Number of winner plane sizes    */
#define WINBYTES        64              /*  Bytes in a winner symbol        */
#define SYM_WIDTH       16              /*  Symbol width in pixels          */
#define SYM_HEIGHT      16              /*  Symbol height in pixels         */
#define BOMBBYTES       16              /*  Bytes in a bomb symbol          */
#define BOMBANGS        8               /*  Number of bomb angles           */
#define TARGBYTES       64              /*  Bytes in a target symbol        */
#define TARGORIENTS     4               /*  Number of target types          */
#define EXPLSYMS        8               /*  Number of explosion symbols     */
#define EXPBYTES        16              /*  Bytes in an explosion symbol    */
#define FLCKSYMS        2               /*  Number of flock symbols         */
#define FLKBYTES        64              /*  Bytes in a flock symbol         */
#define BIRDSYMS        2               /*  Number of bird symbols          */
#define BRDBYTES        2               /*  Bytes in a bird symbol          */
#define OXSYMS          2               /*  Number of ox symbols            */
#define OXBYTES         64              /*  Bytes in an ox symbol           */
#define GHSTBYTES       16              /*  Bytes in a ghost symbol         */
#define SHOTBYTES       64              /*  Bytes in a shot window symbol   */
#define SPLTBYTES       256             /*  Bytes in a splatted bird symbol */
#define MISCBYTES       16              /*  Bytes in a missile symbol       */
#define MISCANGS        16              /*  Number of missile angles        */
#define BRSTBYTES       16              /*  Bytes in a starburst symbol     */
#define BRSTSYMS        2               /*  Number of starburst symbols     */

#define SINGLE          0               /*  Playmodes                       */
#define MULTIPLE        1
#define COMPUTER        2
#define ASYNCH          3
#define NOVICE          4

#define MAX_AMMO        200             /* Maximum number of rounds of shot */
#define MAX_BOMBS       5               /* Maximum number of bombs available*/
#define MAX_MISSILES    5               /* Maximum number of missiles       */
#define MAX_STARBURSTS  5               /* Maximum nuber of starbursts      */
#define MAX_FUEL        (3*MAX_X) /* Maximum Number of turns between refuellings */
#define MAXCRASH        5              /* Maximum number of crashes allowed */

#define MAX_PLYR        4               /* Maximum number of players        */
#define MAX_TARG        20              /* Maximum number of targets        */
#define MAX_OBJS        100             /* Maximum number of objects        */
#define MAX_FLCK        4               /* Maximum number of flocks         */
#define MAX_BIRD        1         /* Maximum number of stray birds per flock */
#define MAX_GAME        7               /* Maximum number of games          */
#define MAX_OXEN        2               /* Maximum number of oxen           */

#define BULSPEED        10              /* Bullet speed    */
#define BULLIFE         10              /* Bullet life     */
#define BOMBLIFE        5               /* Moves between bomb course adj   */
#define MISSLIFE        50              /* Missile life                    */
#define BURSTLIFE       20              /* Starburst life                  */
#define EXPLLIFE        3               /* Moves between explosion "  "    */
#define SMOKELIFE       10              /* Smoke life                      */
#define BIRDLIFE        4               /* Moves between bird flaps        */
#define FLOCKLIFE       5               /* Moves between flop flaps        */

#define WAITING         0               /*  Player states  */
#define FLYING          1
#define HIT             2
#define CRASHED         4
#define FALLING         5
#define STANDING        6
#define STALLED         7
#define REBUILDING      8
#define WOUNDED         9
#define WOUNDSTALL      10
#define FINISHED        91
#define GHOST           92
#define GHOSTCRASHED    93
#define GHOSTSTALLED    94

#define TARGET_FLAG    0
#define TARGET_CHIMNEY 1
#define TARGET_FUEL    2
#define TARGET_TANK    3

#define WINNER          1               /*  End of game status             */
#define LOSER           2

#define GROUND          0               /*  Object types                   */
#define PLANE           1
#define BOMB            2
#define SHOT            3
#define TARGET          4
#define EXPLOSION       5
#define SMOKE           6
#define FLOCK           7
#define BIRD            8
#define OX              9
#define MISSILE         10
#define STARBURST       11
#define DUMMYTYPE       99

#define NEAR            (150*150)   /* Computer control distances        */
#define NEARAPPROACH    200
#define CLOSE           32
#define DEADON          (4*4)
#define HOME            16
#define SAFERESET       32

#define QUIT            (-5000)      /* Plane life value when quitting    */

#define SOUND_TITLE     05
#define SOUND_EXPLOSION 10              /*  Sound priorities                */
#define SOUND_BOMB      20
#define SOUND_SHOT      30
#define SOUND_FALLING   40
#define SOUND_HIT       50
#define SOUND_PLANE     60

#define SC_P     0x19
#define SC_S     0x1f
#define SC_H     0x23
#define SC_Z     0x2c
#define SC_X     0x2d
#define SC_C     0x2e
#define SC_V     0x2f
#define SC_B     0x30
#define SC_COMMA 0x33
#define SC_DOT   0x34
#define SC_SLASH 0x35
#define SC_SPACE 0x39
#define SC_BREAK 0x46

#define KEY_ACCEL         0x0001          /* Keyboard word masks               */
#define KEY_BRAKE         0x0002
#define KEY_CLIMB         0x0004
#define KEY_DESCEND       0x0008
#define KEY_FLIP          0x0010
#define KEY_FIRE          0x0020
#define KEY_BOMB          0x0100
#define KEY_HOME          0x0200
#define KEY_SOUND         0x0400
#define KEY_BREAK         0x0800
#define KEY_MISSILE       0x1000
#define KEY_STARBURST     0x2000

#define BLACK     0
#define CYAN      1
#define MAGENTA   2
#define WHITE     3
#define GREEN     3 /* Was 7 */
#define BROWN     3 /* Was 11 */
#define BLACK_R   0x80
#define CYAN_R    0x81
#define MAGENTA_R 0x82
#define WHITE_R   0x83

#define fcos(r,a) ((r)*sintab[(a+(ANGLES/4))%ANGLES])
#define fsin(r,a) ((r)*sintab[a%ANGLES])

typedef int bool;
typedef int ground_t;

#define PORT_TIMER0 0x40
#define PORT_TIMER2 0x42
#define PORT_TIMERC 0x43
#define PORT_KEYB   0x60
#define PORT_SPKR   0x61
#define PORT_JOY    0x201

#define JOY_BUT1    0x10
#define JOY_BUT2    0x20

#define SNDSIZE     100

#define BIOS_GRAPHICS 4
#define BIOS_TEXT     3

#define JOYMAX  0xa00
#define JOYHIGH 0x780
#define JOYLOW  0x280

#define JOY_X 0
#define JOY_Y 1
