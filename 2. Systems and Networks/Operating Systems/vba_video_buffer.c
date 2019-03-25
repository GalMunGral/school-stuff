typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned char u8;


#define REG_DISPCTL *(u16 *)0x4000000
#define MODE3 3
#define BG2_ENABLE (1<<10)
#define COLOR(r,g,b) ((r) | (g) << 5 | (b) << 10)
#define RED COLOR(31,0,0)
#define WHITE COLOR(31,31,31)
#define GREEN COLOR(0, 31, 0)
#define BLACK 0
#define YELLOW COLOR(31,31,0)
#define BLUE COLOR(0,0,31)
#define OFFSET(r,c) ((r)*240+(c))

unsigned short *videoBuffer = (u16 *)0x6000000;

void setPixel(int row, int col, u16 color);
void drawRectangle(int row, int col, int width, int height, u16 color);
void drawHollowRectangle(int row, int col, int width, int height, u16 color);

int main() {
  REG_DISPCTL = MODE3 | BG2_ENABLE;
  drawRectangle(20,20,175,115,WHITE);
  drawHollowRectangle(50,50,30,30,BLUE);
  drawHollowRectangle(70,70,30,30,YELLOW);
  drawHollowRectangle(50,90,30,30,BLACK);
  drawHollowRectangle(70,110,30,30,GREEN);
  drawHollowRectangle(50,130,30,30,RED);
  while(1);
}

void setPixel(int row, int col, u16 color) {
  videoBuffer[OFFSET(row, col)] = color;
}

void drawRectangle(int row, int col, int width, int height, u16 color) {
  for (int x = col; x < row + width; x++) {
    for (int y = row; y < row + height; y++) {
      setPixel(y, x, color);
    }
  }
}

void drawHollowRectangle(int row, int col, int width, int height, u16 color) {
  for (int x = col; x < col + width; x++) {
    setPixel(row, x, color);
    setPixel(row + height - 1, x, color);
  }
  for (int y = row; y < row + height; y++) {
    setPixel(y, col, color);
    setPixel(y, col + width - 1, color);
  }
}
