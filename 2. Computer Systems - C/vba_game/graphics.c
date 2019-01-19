#include "myLib.h"
#include "imgs/background.h"

unsigned short *videoBuffer = (unsigned short *)0x6000000;

void drawBackground(const u16* image) {
  DMA[3].src = image;
  DMA[3].dst = videoBuffer;
  DMA[3].cnt = DMA_ON | BACKGROUND_SIZE;
}

void refillBackground(int r, int c, int width, int height, const u16* image) {	
  for (int i = 0; i < height; i++) {
    DMA[3].src = image + (r + i) * 240 + c;
    DMA[3].dst = videoBuffer + (r + i) * 240 + c;
    DMA[3].cnt = DMA_ON | width;
  }
}

void drawRow(int row, int r, int c, int width, const u16* image) {
  DMA[3].src = image + row * width;
  DMA[3].dst = videoBuffer + r * 240 + c;
  DMA[3].cnt = DMA_ON | width;
}

void drawImage3(int r, int c, int width, int height, const u16* image) {
  for (int i = 0; i < height; i++){
    drawRow(i, r + i, c, width, image);
  }
}

void drawString(int row, int col, char* str, unsigned short color) {
  int size = 0;
  char* cur = str;
  while(*cur) {
    size++;
    cur++;
  }
  u16 strData[16*48*size];
  for (int i = 0; i < size; i++) {
    for(int r = 0; r < 8; r++) {
      for(int c = 0; c < 6; c++) {
        if(fontdata_6x8[OFFSET(r, c, 6) + str[i]*48]) {
          strData[OFFSET(r, 6*i+c, 6*size)] = color;
        } else {
          strData[OFFSET(r, 6*i+c, 6*size)] = 0;
        }
      }
    }			
  }
  drawImage3(row, col, 6*size, 8, strData);
}