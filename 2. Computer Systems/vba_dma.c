#include "myLib.h"
#include "student.h"
#include "math.h"
#include "bill1.h"
#include "bill2.h"

u16 *videoBuffer = (u16 *)0x6000000;

// This function takes an image and flips it both horizontally and vertically,
// and then draws it in the top left quadrant of the GBA screen (with DMA).
void rotateImageAndDraw(int width, int height, const unsigned short *image) {  
  for (int i = 0; i < height; i++) {
    DMA[3].src = image + OFFSET(height-1-i, width-1, 120);
    DMA[3].dst = videoBuffer + OFFSET(i, 0 , 240);
    DMA[3].cnt = DMA_ON | DMA_SOURCE_DECREMENT | width;
  }
}

// This function takes an image and flips it horizontally,
// and then draws it in the top right quadrant of the GBA screen (with DMA).
void flipHorizontallyAndDraw(int width, int height, const unsigned short *image) {
  for (int i = 0; i < height; i++) {
    DMA[3].src = image + OFFSET(i, width-1, 120);
    DMA[3].dst = videoBuffer + OFFSET(i, 120 , 240);
    DMA[3].cnt = DMA_ON | DMA_SOURCE_DECREMENT | width;
  }
}

// This function  will draw an arbitrary sized image
// onto the screen (with DMA).
void drawImage3(int row, int col, int width, int height, const unsigned short *image) { 
  for (int i = 0; i < height; i++) {
    DMA[3].src = image + OFFSET(i, 0, width);
    DMA[3].dst = videoBuffer + OFFSET(row+i, col, 240);
    DMA[3].cnt = DMA_ON | width;
  }
}

int main(void) {
  // so that whatever you want to draw actually gets drawn on the screen.
  REG_DISPCNT = BG2_ENABLE | MODE3;    
  waitForVblank();
  rotateImageAndDraw(STUDENT_WIDTH, STUDENT_HEIGHT, student_data);
  flipHorizontallyAndDraw(MATH_WIDTH, MATH_HEIGHT, math_data);
  drawImage3(80, 0, BILL1_WIDTH, BILL1_HEIGHT, bill1_data);
  drawImage3(80, 120, BILL2_WIDTH, BILL2_HEIGHT, bill2_data);
  // Wait after drawing
  while (1);
}

void waitForVblank() {
  while(SCANLINECOUNTER > 160);
  while(SCANLINECOUNTER < 160);
}
