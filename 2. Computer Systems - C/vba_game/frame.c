#include "myLib.h"
#include "./imgs/background.h"

void updateFrame() {
  movePlayer();
  updateEnemies();
  updateBullets();
}

void updateEnemies() {
  enemy* curEnemy = E_HEAD;
  while (curEnemy != 0) {
    if (curEnemy->deleted == 1) {
      if (curEnemy->timeLeft >0) {
        curEnemy->timeLeft--;
      } else {
        removeEnemy(curEnemy);
        eraseExplosion(curEnemy->row, curEnemy->col);
      }
    } else if (curEnemy->deleted == 0) {
      if (crashed(*curEnemy)) {
        killPlayer();
        removeEnemy(curEnemy);
      } else {
        moveEnemy(curEnemy);
      }
    }
    curEnemy = curEnemy -> next;			
  }
}

void updateBullets() {
  bullet* curBullet = B_HEAD;
  while (curBullet != 0) {
    if (playerHit(*curBullet)) {
      eraseBullet(*curBullet);
      removeBullet(curBullet);
      killPlayer();
    } else {
      moveBullet(curBullet);
      enemy* curEnemy = E_HEAD;
      while (curEnemy != 0) {
        if (curEnemy->deleted == 0) {
          if (enemyHit(*curBullet, *curEnemy)) {
            eraseBullet(*curBullet);
            removeBullet(curBullet);
            killEnemy(curEnemy);
            score++;
          }
        }
        curEnemy = curEnemy -> next;			
      }
    }
    curBullet = curBullet -> next;
  }
}

void killPlayer() {
  drawExplosion(row, col);
  isDead = 1;
}

void killEnemy(enemy* curEnemy) {
  curEnemy->deleted = 1;
  drawExplosion(curEnemy->row, curEnemy->col);
}
