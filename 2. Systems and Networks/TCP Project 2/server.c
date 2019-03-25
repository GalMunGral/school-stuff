#include <stdio.h>	  
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>	  
#include <string.h>	  
#include <pthread.h>
#include <ctype.h>
#define SMSGSIZE 512		
#define CMSGSIZE 2
#define NEXT(X) (X + 1) % 2

// Data structure for managing game states
typedef struct game_ctl_b {
  char *word; // The word to be guessed
  char *masked; // The word with each unguessed letter replaced by '_'
  char ic_guesses[6]; // Incorrect guesses
  uint8_t word_len;
  uint8_t num_ic; // # Incorrect guesses
  uint8_t count; // # Revealed letters. Player wins when count == 6.
} game_ctl_b;

// Pool of words
char *words[15] = {
  "feud\0",
  "fawn\0",
  "lull\0",
  "edify\0",
  "irate\0",
  "agile\0",
  "adorn\0",
  "livid\0",
  "entice\0",
  "caustic\0",
  "anguish\0",
  "appease\0",
  "disrobe\0",
  "pilferer\0",
  "antidote\0"
};

// Counter for # ongoing games. Will not exceed 3.
int session_count = 0; 
// Socket # of the player waiting for others to join (multiplayer mode)
int pending_clnt_sock = -1;

void *select_mode(void * sock);
void send_msg_pkt(int sock, uint8_t *buf, char *msg);
void send_ctl_pkt(int sock, uint8_t *buf, game_ctl_b *gcb);
void *single_player_start(void *sock);
void *multiplayer_start(void *sock);

int main(int argc, char *argv[]) {
  int server_sock;
  int client_sock;
  unsigned short server_port;
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;

  /*** Set up TCP ***/
  if (argc < 2) {
    printf("Too few arguments.\n"); exit(1);
  }
  sscanf(argv[1], "%hu", &server_port);
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(server_port);
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_sock = socket(AF_INET, SOCK_STREAM, 0);
  if(-1 == bind(server_sock, (struct sockaddr *) &server_addr, sizeof(server_addr))) {
    perror("\'bind\' failed"); exit(1);
  }
  if (-1 ==listen(server_sock, 6)) {
    perror("\'listen\' failed"); exit(1);
  }

  /*** Listen for connections ***/
  while(1) {
    client_sock = accept(server_sock, NULL, NULL);
    if (-1 == client_sock) {
      perror("\'accept\' failed"); exit(1);
    }
    // Spawn a new thread to handle mode selection.
    int *cur_clnt_sock = malloc(sizeof(int));
    *cur_clnt_sock = client_sock;
    pthread_t client_thread;
    pthread_create(&client_thread, NULL, select_mode, cur_clnt_sock);
    pthread_detach(client_thread);
  }
}

/**
 * Thread for handling game mode selection
 */
void *select_mode(void *sock) {
  uint8_t snd_buf[SMSGSIZE];
  uint8_t buffer[2]; // For client msg
  int client_sock = *(int *) sock;
  free(sock);
  
  if (-1 == recv(client_sock, buffer, CMSGSIZE, 0)) {
    perror("\'recv\' failed"); exit(1);
  }

  /** REFUSE CONNECTION WHEN OVERLOADED **/
  if (session_count == 3) {
    send_msg_pkt(client_sock, snd_buf, "Server Overloaded!");
    close(client_sock);
    return NULL;
  }
  
  // if (buffer[0] == (uint8_t) 0) {
  if (buffer[1] == '0') {
    // SPAWN A SINGLE-PLAYER GAME
    int *cur_clnt_sock = malloc(sizeof(int));
    *cur_clnt_sock = client_sock;
    pthread_t new_game;
    pthread_create(&new_game, NULL, single_player_start, cur_clnt_sock);
    session_count++;
    pthread_detach(new_game);
  // } else if (buffer[0] == (uint8_t) 1 && buffer[1] == '2') {
  } else if (buffer[1] == '2') {
    // MULTIPLAYER MODE
    if (pending_clnt_sock == -1) {
      // If no one is waiting, let the player wait.
      send_msg_pkt(client_sock, snd_buf, "Waiting for other player!");
      pending_clnt_sock = client_sock;
    } else {
      // If someone is waiting, pair them up and start the game
      int *players = malloc(2 * sizeof(int));
      players[0] = pending_clnt_sock;
      players[1] = client_sock;
      pthread_t new_game;
      pthread_create(&new_game, NULL, multiplayer_start, players);
      session_count++;
      pthread_detach(new_game);
      pending_clnt_sock = -1; // Now no one is waiting
    }
  }
}

/**
 * Helper method for initializing GCB (Game Control Block)
 */
void init_gcb(game_ctl_b *gcb) {
  gcb->word = words[rand() % 15];
  gcb->word_len = strlen(gcb->word);
  gcb->masked = malloc(gcb->word_len);
  memset(gcb->masked, '_', gcb->word_len);
  gcb->num_ic = 0;
  gcb->count = 0;
}

/**
 * Helper method for sending game control packets.
 * +----------+-------------+---------------+------+ 
 * | Msg flag | Word Length | Num Incorrect | Data |
 * +----------+-------------+---------------+------+
 */
void send_ctl_pkt(int sock, uint8_t *buf, game_ctl_b *gcb) {
  buf[0] = (uint8_t) 0; // Unset Msg flag
  buf[1] = (uint8_t) gcb->word_len;
  buf[2] = (uint8_t) gcb->num_ic;
  strncpy(buf + 3, gcb->masked, gcb->word_len);
  strncpy(buf + 3 + gcb->word_len, gcb->ic_guesses, gcb->num_ic);
  int msg_size = 3 + buf[1] + buf[2];
  if (-1 == send(sock, buf, msg_size, 0)) {
    perror("\'send\' failed"); exit(1);
  }
}


/**
 * Helper method for sending message packets
 * +---------+-----+ 
 * | Msg Len | Msg |
 * +---------+-----+ 
 */
void send_msg_pkt(int sock, uint8_t *buf, char *msg) {
  buf[0] = (uint8_t) strlen(msg); // Msg Len
  strncpy(buf + 1, msg, buf[0]); // Msg
  if (-1 == send(sock, buf, buf[0] + 1, 0)) {
    perror("\'send\' failed"); exit(1);
  }
}

/**
 * Thread for a single-player game
 */
void *single_player_start(void *args) {
  game_ctl_b gcb;
  uint8_t rcv_buf[CMSGSIZE];
  uint8_t snd_buf[SMSGSIZE];
  int client_sock = *(int *)args;
  init_gcb(&gcb);
  send_ctl_pkt(client_sock ,snd_buf, &gcb); // Initial control packet

  /** GAME LOOP **/
  while(1) {
    if (-1 == recv(client_sock, rcv_buf, 2, 0)) {
      perror("\'recv\' failed"); exit(1);
    }
    // Check for matches and update game state
    char guess = rcv_buf[1];
    int match = 0;
    int i;
    for (i = 0; i < gcb.word_len; i++) {
      if (gcb.word[i] == guess) {
        match++;
        if (gcb.masked[i] == '_') {
          gcb.masked[i] = gcb.word[i];
          gcb.count++;
        }
      }
    }
    if (!match) gcb.ic_guesses[gcb.num_ic++] = guess;

    // SEND RESPONSES
    send_ctl_pkt(client_sock, snd_buf, &gcb);
    if (gcb.count == gcb.word_len) {
      send_msg_pkt(client_sock, snd_buf, "You Win!");
      send_msg_pkt(client_sock, snd_buf, "Game Over!");
      close(client_sock);
      session_count--;
      break;
    }
    if (gcb.num_ic == 6) {
      send_msg_pkt(client_sock, snd_buf, "You Lose :(");
      send_msg_pkt(client_sock, snd_buf, "Game Over!");
      close(client_sock);
      session_count--;
      break;
    }
  }
}

void *multiplayer_start(void *args) {
  game_ctl_b gcb;
  uint8_t rcv_buf[CMSGSIZE];
  uint8_t snd_buf[SMSGSIZE];
  int *players = (int *) args;
  init_gcb(&gcb);
  int curr = 0; // Index used to keep track of the active player

  // Initial messages
  send_msg_pkt(players[0], snd_buf, "Game Starting!");
  send_msg_pkt(players[0], snd_buf, "Your Turn!");
  send_ctl_pkt(players[0] ,snd_buf, &gcb);
  send_msg_pkt(players[1], snd_buf, "Game Starting!");
  send_msg_pkt(players[1], snd_buf, "Waiting on player 1...");

  /** GAME LOOP **/
  while(1) {
    // Read message from the ACTIVE player
    if (-1 == recv(players[curr], rcv_buf, 2, 0)) {
      perror("\'recv\' failed"); exit(1);
    }
    // Check for matches and update game states
    char guess = rcv_buf[1];
    int match = 0;
    int i;
    for (i = 0; i < gcb.word_len; i++) {
      if (gcb.word[i] == guess) {
        match++;
        if (gcb.masked[i] == '_') {
          gcb.masked[i] = gcb.word[i];
          gcb.count++;
        }
      }
    }
    // SEND RESPONSES
    if (!match) {
      gcb.ic_guesses[gcb.num_ic++] = guess;
      send_msg_pkt(players[curr], snd_buf, "Incorrect!");
    } else {
      send_msg_pkt(players[curr], snd_buf, "Correct!");
    }
    if (gcb.count == gcb.word_len) {
      send_ctl_pkt(players[0] ,snd_buf, &gcb);
      send_ctl_pkt(players[1] ,snd_buf, &gcb);
      send_msg_pkt(players[0], snd_buf, "You Win!");
      send_msg_pkt(players[0], snd_buf, "Game Over!");
      send_msg_pkt(players[1], snd_buf, "You Win!");
      send_msg_pkt(players[1], snd_buf, "Game Over!");
      close(players[1]);
      close(players[0]);
      session_count--;
      break;
    }
    if (gcb.num_ic == 6) {
      send_ctl_pkt(players[0] ,snd_buf, &gcb);
      send_ctl_pkt(players[1] ,snd_buf, &gcb);
      send_msg_pkt(players[0], snd_buf, "You Lose :(");
      send_msg_pkt(players[0], snd_buf, "Game Over!");
      send_msg_pkt(players[1], snd_buf, "You Lose :(");
      send_msg_pkt(players[1], snd_buf, "Game Over!");
      close(players[0]);
      close(players[1]);
      session_count--;
      break;
    }

    // Next player's turn
    uint8_t temp_buf[25];
    sprintf(temp_buf, "Waiting on Player %d...\n", NEXT(curr) + 1);
    send_msg_pkt(players[curr], snd_buf, temp_buf);
    curr = NEXT(curr);
    send_msg_pkt(players[curr], snd_buf, "Your Turn!");
    send_ctl_pkt(players[curr] ,snd_buf, &gcb);
  }
}
