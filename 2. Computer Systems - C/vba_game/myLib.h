typedef unsigned short u16;
typedef unsigned int u32;

// Structs
typedef struct {
  const volatile void *src;
  volatile void *dst;
  volatile u32 cnt;
} DMA_CONTROLLER;

typedef struct bullet {
  int row;
  int col;
  int d;
  struct bullet* prev;
  struct bullet* next;
} bullet;

typedef struct enemy {
  int row;
  int col;
  int timeLeft;
  int deleted;
  struct enemy* prev;
  struct enemy* next;
} enemy;

enum GBAState {
  TITLE,
  TITLE_NODRAW,
  START,
  START_NODRAW,
  PLAY,
  GAMEOVER,
  GAMEOVER_NODRAW,
  RESTART,
  RESTART_NODRAW
};

// Global variables
extern unsigned short *videoBuffer;
extern const unsigned char fontdata_6x8[12288];

extern enemy* E_HEAD;
extern enemy* E_TAIL;
extern bullet* B_HEAD;
extern bullet* B_TAIL;

extern int row;
extern int col;

extern int clock;
extern int interval;
extern int score;
extern int bestScore;
extern int lives;
extern int isDead;
extern char scoreStr[];
extern char bestScoreStr[];
extern char livesStr[];

// Macros
#define REG_DISPCTL *(unsigned short *)0x4000000
#define MODE3 3
#define BG2_ENABLE (1 << 10)
#define OFFSET(r, c, rowlen) ((c) + (r)*(rowlen))
#define COLOR(r, g, b) ((r) | (g)<<5 | (b)<<10)
#define WHITE COLOR(31,31,31)
#define RED COLOR(31,0,0)
#define GREEN COLOR(0,31,0)
#define BLUE COLOR(0,0,31)
#define MAGENTA COLOR(31, 0, 31)
#define CYAN COLOR(0, 31, 31)
#define YELLOW COLOR(31, 31, 0)
#define BLACK 0
#define SCANLINECOUNTER *(volatile u16*) 0x4000006

#define DMA ((volatile DMA_CONTROLLER*) 0x40000B0)
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3
#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)
#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)
#define DMA_REPEAT (1 << 25)
#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)
#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)
#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)

#define BUTTON_SELECT	(1<<2)
#define BUTTON_START	(1<<3)
#define BUTTON_RIGHT	(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTONS *(volatile unsigned int *)0x4000130
#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)
#define MAX_NUM_BULLETS 50
#define MAX_NUM_ENEMIES 10

// Prototypes
void updateModel();
void createEnemy();
void createBullets();
void createBullet(int row, int col, int d);
void removeBullet(bullet* curBullet);
void removeEnemy(enemy* curEnemy);
void reset();

void updateFrame();
void movePlayer();
void moveEnemy(enemy* curEnemy);
void moveBullet(bullet* curBullet);
void updateEnemies();
void updateBullets();

int crashed(enemy curEnemy);
int enemyHit(bullet curBullet, enemy curEnemy);
int playerHit(bullet curBullet);
void killPlayer();
void killEnemy(enemy* e_ptr);

void drawRow(int row, int r, int c, int width, const u16* image);
void drawImage3(int r, int c, int width, int height, const u16* image);

void drawPlayer();
void erasePlayer();
void drawBullet(bullet b);
void eraseBullet(bullet b);
void drawEnemy(enemy e);
void eraseEnemy(enemy e);
void drawExplosion(int row, int col);
void eraseExplosion(int row, int col);
void drawBackground(const u16* image);
void refillBackground(int r, int c, int width, int height, const u16* image);

void drawString(int row, int col, char* str, unsigned short color);
void printScore();
void printStatus();

void waitForVBlank();
void delay(int i);
