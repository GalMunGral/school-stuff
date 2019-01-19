#include <stdlib.h>
#include "myLib.h"
#include "imgs/fire.h"
#include "imgs/playerjet.h"
#include "imgs/enemyjet.h"

bullet* B_HEAD = 0;
bullet* B_TAIL = 0;
enemy* E_HEAD = 0;
enemy* E_TAIL = 0;

int interval = 100;

void updateModel() {
  createEnemy();
  createBullets();
  if (interval > 60 && clock % interval == 0) {
    interval--;
  }
}

void createEnemy() {
  if (clock % interval == 0) {		
    enemy* new_enemy = malloc(sizeof(enemy));
    new_enemy->row = 0;
    new_enemy->col = rand() % (240 - ENEMYJET_WIDTH);
    new_enemy->deleted = 0;
    new_enemy->timeLeft = 5;
    new_enemy->next = 0;
    new_enemy->prev =0;
    if (E_HEAD == 0) {
      E_HEAD = new_enemy;
      E_TAIL = new_enemy;
    } else {
      new_enemy-> prev = E_TAIL;
      E_TAIL->next = new_enemy;
      E_TAIL = new_enemy;
    }
  }
}

void createBullet(int row, int col, int d) {
  bullet* new_bullet = malloc(sizeof(bullet));
  new_bullet->row = row;
  new_bullet->col = col;
  new_bullet->d = d;
  new_bullet->next = 0;
  new_bullet->prev = 0;
  if (B_HEAD == 0) {
    B_HEAD = new_bullet;
    B_TAIL = new_bullet;
  } else {
    new_bullet->prev = B_TAIL;
    B_TAIL->next = new_bullet;
    B_TAIL = new_bullet;
  }
}

void createBullets(){
  if (clock % 3 == 0) {	
    createBullet(row - FIRE_HEIGHT,
      col + PLAYERJET_WIDTH/2, -5);
  }
  if (clock % (interval - 50) == 0) {
    enemy* curEnemy = E_HEAD;
    while (curEnemy != 0) {
      createBullet(curEnemy->row + ENEMYJET_HEIGHT,
        curEnemy->col + ENEMYJET_WIDTH/2, 2);
      curEnemy = curEnemy -> next;			
    }		
  }	
}

void removeBullet(bullet* curBullet) {
  if (curBullet == B_HEAD && curBullet == B_TAIL) {
    B_HEAD = 0;
    B_TAIL = 0;
  } else if (curBullet == B_HEAD) {
    B_HEAD = B_HEAD->next;
    B_HEAD->prev = 0;
  } else if (curBullet == B_TAIL) {
    B_TAIL = B_TAIL->prev;
    B_TAIL->next = 0;
  } else {
    (curBullet->prev)->next = curBullet->next;
    (curBullet->next)->prev = curBullet->prev;
  }
}

void removeEnemy(enemy* curEnemy) {
  if (curEnemy == E_HEAD && curEnemy == E_TAIL) {
    E_HEAD = 0;
    E_TAIL = 0;
  } else if (curEnemy == E_HEAD) {
    E_HEAD = E_HEAD->next;
    E_HEAD->prev = 0;
  } else if (curEnemy == E_TAIL) {
    E_TAIL = E_TAIL->prev;
    E_TAIL->next = 0;
  } else {
    (curEnemy->prev)->next = curEnemy->next;
    (curEnemy->next)->prev = curEnemy->prev;
  }
}