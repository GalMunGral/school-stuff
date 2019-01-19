#include "myLib.h"
#include "imgs/title.h"
#include "imgs/background.h"
#include "imgs/gameover.h"

int lives;
int isDead;
int score;
int bestScore;
int clock;

int main() {

  REG_DISPCTL = MODE3 | BG2_ENABLE;
  lives = 3;
  isDead = 0;
  score = 0;
  bestScore = 0;
  clock = 0;
  int isPressed = 0;
  enum GBAState state = TITLE;

  while(1){

    waitForVBlank();

    switch(state) {
      case TITLE:
        drawBackground(title);
        state = TITLE_NODRAW;
        break;

      case TITLE_NODRAW:
        delay(30);
        state = START;
        break;

      case START:
        drawBackground(background);		
        drawString(75, 60, "Press Start to Play", WHITE);
        bestScore = 0;
        state = START_NODRAW;
        break;

      case START_NODRAW:
        if (!isPressed && KEY_DOWN_NOW(BUTTON_START)) {
          state = PLAY;
          isPressed = 1;
        }
        break;

      case PLAY:
        drawBackground(background);
        state = RESTART;
        while (!isDead) {
          if (KEY_DOWN_NOW(BUTTON_SELECT)) {
            reset();
            lives = 3;
            state = TITLE;
            break;
          }
          waitForVBlank();
          updateModel();
          updateFrame();
          printScore();
          clock++;
        }
        delay(5);
        break;

      case RESTART:
        if (score > bestScore) {
          bestScore = score;
        }
        lives--;
        printStatus();
        if (lives > 0) {
          drawString(75, 90, "Restart?", WHITE);
        } else {
          drawString(75, 100, "YOU DIED", WHITE);

        }
        state = RESTART_NODRAW;
        break;
        

      case RESTART_NODRAW:
        if (!isPressed && KEY_DOWN_NOW(BUTTON_START)) {
          if (lives > 0) {
            reset();
            state = PLAY;
          } else {
            state = GAMEOVER;
          }
          isPressed = 1;
        }
        break;

      case GAMEOVER:
        drawBackground(gameover);
         state = GAMEOVER_NODRAW;
         break;

      case GAMEOVER_NODRAW:
        break;
    }

    if (!KEY_DOWN_NOW(BUTTON_START)) {
      isPressed = 0;
    }
    if (KEY_DOWN_NOW(BUTTON_SELECT)) {
      reset();
      lives = 3;
      state = TITLE;
    }
  }

}

void reset() {
  score = 0;
  isDead = 0;
  B_HEAD = 0;
  B_TAIL = 0;
  E_HEAD = 0;
  E_TAIL = 0;	
  row = 140;
  col = 120;
  clock = 0;
  interval = 100;
}

void delay(int n) {
  int volatile x = 0;
  for(int i =0; i < n*8000; i++) {
    x = x + 1;
  }
}

void waitForVBlank() {
  while(SCANLINECOUNTER > 160);
  while(SCANLINECOUNTER < 160);
}