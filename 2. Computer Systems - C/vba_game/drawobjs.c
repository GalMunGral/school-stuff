#include "myLib.h"
#include "imgs/background.h"
#include "imgs/playerjet.h"
#include "imgs/enemyjet.h"
#include "imgs/explosion.h"
#include "imgs/fire.h"

char curScore[4] = "   \0";
char scoreStr[11] = "Score:    \0";
char bestScoreStr[11] = "Best:    \0";
char livesStr[2] = " \0";

void drawPlayer() {
  drawImage3(row, col,
    PLAYERJET_WIDTH, PLAYERJET_HEIGHT, playerjet);
}

void erasePlayer() {
  refillBackground(row, col,
    PLAYERJET_WIDTH, PLAYERJET_HEIGHT, background);
}

void drawEnemy(enemy e) {
  drawImage3(e.row, e.col,
    ENEMYJET_WIDTH, ENEMYJET_HEIGHT, enemyjet);
}
void eraseEnemy(enemy e) {
  refillBackground(e.row, e.col,
    ENEMYJET_HEIGHT, ENEMYJET_WIDTH, background);
}

void drawBullet(bullet b) {
  drawImage3(b.row, b.col,
    FIRE_WIDTH, FIRE_HEIGHT, fire);
}

void eraseBullet(bullet b) {
  refillBackground(b.row, b.col, 
    FIRE_WIDTH, FIRE_HEIGHT, background);
}

void drawExplosion(int row, int col) {
  int r = row + ENEMYJET_HEIGHT/2 - EXPLOSION_HEIGHT/2;
  int c = col + ENEMYJET_WIDTH/2 - EXPLOSION_WIDTH/2;
  drawImage3(r, c, EXPLOSION_WIDTH, EXPLOSION_HEIGHT, explosion);}

void eraseExplosion(int row, int col) {
  int r = row + ENEMYJET_HEIGHT/2 - EXPLOSION_HEIGHT/2;
  int c = col + ENEMYJET_WIDTH/2 - EXPLOSION_WIDTH/2;
  drawImage3(r, c, EXPLOSION_WIDTH, EXPLOSION_HEIGHT, background);
}

void printScore() {
  curScore[2] = score - score/10 * 10 + '0';
  curScore[1] = score/10 - score/100 * 10  + '0';
  curScore[0] = score/100 - score/1000 * 10  + '0';
  drawString(5, 5, curScore, YELLOW);
}

void printStatus() {
  scoreStr[9] = score - score/10 * 10 + '0';
  scoreStr[8] = score/10 - score/100 * 10  + '0';
  scoreStr[7] = score/100 - score/1000 * 10  + '0';
  drawString(5, 5, scoreStr, YELLOW);
  bestScoreStr[8] = bestScore - bestScore/10 * 10 + '0';
  bestScoreStr[7] = bestScore/10 - bestScore/100 * 10  + '0';
  bestScoreStr[6] = bestScore/100 - bestScore/1000 * 10  + '0';
  drawString(15, 5, bestScoreStr, YELLOW);
  livesStr[0] = lives + '0';
  drawString(5, 228, livesStr, YELLOW);
}