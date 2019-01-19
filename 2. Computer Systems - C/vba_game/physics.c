#include "myLib.h"
#include "./imgs/enemyjet.h"
#include "./imgs/playerjet.h"
#include "./imgs/fire.h"

int row = 140;
int col = 120;

void movePlayer() {
  if(KEY_DOWN_NOW(BUTTON_UP)) {
    erasePlayer();
    row-=2;
    if(row < 0) {
      row = 0;
    }
  }
  if(KEY_DOWN_NOW(BUTTON_DOWN)) {
    erasePlayer();
    row+=2;
    if(row > 145) {
      row = 145;
    }
  }
  if(KEY_DOWN_NOW(BUTTON_LEFT)) {
    erasePlayer();
    col-=2;
    if(col < 0) {
      col = 0;
    }
  }
  if(KEY_DOWN_NOW(BUTTON_RIGHT)) {
    erasePlayer();
    col+=2;
    if(col > 225) {
      col = 225;
    }
  }
  drawPlayer();
}

void moveEnemy(enemy* curEnemy) {
  eraseEnemy(*curEnemy);		
    curEnemy->row++;
    if (curEnemy->col - col > PLAYERJET_WIDTH/2 + 1) {
      curEnemy->col -= clock % 3;
    } else if (
      ((col + PLAYERJET_WIDTH) - (curEnemy->col + ENEMYJET_WIDTH))
      > (PLAYERJET_WIDTH / 2)
    ) {
      curEnemy->col++;
    }
    if (curEnemy->col < 0) {
      curEnemy->col += 2;
    } else if (curEnemy->col + ENEMYJET_WIDTH > 239) {
      curEnemy->col -= 2;
    }
    if (curEnemy->row > 160) {
      removeEnemy(curEnemy);
    } else {
      drawEnemy(*curEnemy);
    }
}

void moveBullet(bullet* curBullet) {
  eraseBullet(*curBullet);
  curBullet->row += curBullet->d;
  if (curBullet->row < 0 || curBullet->row > 160) {
    removeBullet(curBullet);
  } else {
    drawBullet(*curBullet);
  }
}	

int enemyHit(bullet curBullet, enemy curEnemy) {
  if (
    curBullet.row > curEnemy.row
    && curBullet.row < curEnemy.row + PLAYERJET_HEIGHT
    && curBullet.col > curEnemy.col
    && curBullet.col < curEnemy.col + PLAYERJET_WIDTH
  ) {
    return 1;
  } else {
    return 0;
  }
}

int playerHit(bullet curBullet) {
  if (
    curBullet.row > row
    && curBullet.row < row + PLAYERJET_HEIGHT
    && curBullet.col > col
    && curBullet.col < col + PLAYERJET_WIDTH
  ) {
    return 1;
  } else {
    return 0;
  }
}

int crashed(enemy curEnemy) {
  if (
    row + PLAYERJET_HEIGHT > curEnemy.row
    && row < curEnemy.row + ENEMYJET_HEIGHT
    && col + PLAYERJET_WIDTH > curEnemy.col
    && col < curEnemy.col + ENEMYJET_WIDTH
  ) {
    return 1;
  } else {
    return 0;
  }
}