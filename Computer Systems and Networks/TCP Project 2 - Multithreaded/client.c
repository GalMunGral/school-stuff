#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define RCVBUFSIZE 512
#define SNDBUFSIZE 512
#define INBUFSIZE 512
#define CMSGSIZE 2

int client_sock; 
uint8_t input_buf[INBUFSIZE]; // For user input
uint8_t snd_buf[SNDBUFSIZE];
uint8_t rcv_buf[RCVBUFSIZE];

int send_msg(int sock, char *msg);
void game_start(int sock);

int main(int argc, char *argv[]) {
  char *serv_ip;
  unsigned short serv_port;
  struct sockaddr_in serv_addr;

  /*** Set up TCP ***/
  memset(&snd_buf, 0, SNDBUFSIZE);
  memset(&rcv_buf, 0, RCVBUFSIZE);
  if (argc < 3) {
    printf("Too few arguments.\n"); exit(1);
  }
  if (0 == sscanf(argv[2], "%hu", &serv_port)) {
    printf("Incorrect format: \'%s\' is not a valid port number\n", argv[2]); exit(1);
  }
  serv_ip = argv[1];
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(serv_port);
  client_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (0 == inet_aton(serv_ip, &(serv_addr.sin_addr))) {
    printf("Invalid server IP \'%s\'.\n", serv_ip); exit(1);
  }
  if (-1 == connect(client_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr))) {
    perror("\'connect\' failed"); exit(1);
  }

  /*** Select Game Mode ***/
  printf("Two Player? (y/n) ");
  scanf("%s", input_buf);
  while (strlen(input_buf) != 1 || (input_buf[0] != 'y' && input_buf[0] != 'n')) {
    printf("\nPlease answer y/n: ");
    scanf("%s", input_buf);
  }
  if (input_buf[0] == 'y') {
    send_msg(client_sock, "2"); // Multiplayer - Send '2'
  } else if (input_buf[0] == 'n') {
    send_msg(client_sock, "0"); // Single player - Send '0'
  }

  /*** ENTER GAME ***/
  game_start(client_sock);
}

/**
 * Helper method for sending messages
 * +---------+-----+
 * | Msg Len | Msg |
 * +---------+-----+
 */
int send_msg(int sock, char *msg) {
  uint8_t msg_buf[2];
  memset(&msg_buf, 0, 2);
  msg_buf[0] = (uint8_t) strlen(msg); // Msg Len
  if (strlen(msg) > 0) msg_buf[1] = msg[0]; // Msg
  if (-1 == send(sock, msg_buf, 2, 0)) {
    perror("\'send\' failed"); return -1;
  }
  return 0;
}

void game_start(int sock) {
  /** GAME LOOP **/
  while (1) {
    if (-1 == recv(client_sock, rcv_buf, 1, 0)) {
      perror("\'recv\' failed"); exit(1);
    }
    uint8_t msg_flag = (uint8_t) rcv_buf[0];
    if (msg_flag) {
      // Read and print message
      if (-1 == recv(client_sock, rcv_buf+1, msg_flag, 0)) {
        perror("\'recv\' failed"); exit(1);
      }
      rcv_buf[1 + msg_flag] = '\0';
      printf("%s\n", rcv_buf + 1);
      if (0 == strncmp(rcv_buf+1, "Game Over!", 10)) {
        exit(0);
      }
      if (0 == strncmp(rcv_buf+1, "Server Overloaded!", 10)) {
        exit(1);
      }
    } else {
      // Read metadata of the control packet
      if (-1 == recv(client_sock, rcv_buf+1, 2, 0)) {
        perror("\'recv\' failed"); exit(1);
      }
      uint8_t word_len = (uint8_t) rcv_buf[1];
      uint8_t num_ic = (uint8_t) rcv_buf[2];
      
      // Read and print message
      if (-1 == recv(client_sock, rcv_buf+3, word_len + num_ic, 0)) {
        perror("\'recv\' failed"); exit(1);
      }
      char *masked = malloc(word_len + 1);
      strncpy(masked, rcv_buf+3, word_len);
      masked[word_len] = '\0'; // NULL-terminate it
      char *ic_guesses = malloc(num_ic + 1);
      strncpy(ic_guesses, rcv_buf+3+word_len, num_ic);
      ic_guesses[num_ic] = '\0'; // NULL-terminate it
      printf("%s\n", masked);
      printf("Incorrect Guesses: ");
      int i;
      for (i = 0; i < num_ic; i++) {
        printf("%c ", rcv_buf[3 + word_len + i]);
      }
      printf("\n");

      // Continue to read messages if game is over
      if (strchr(masked, '_') == NULL || num_ic == 6) continue;

      // Otherwise, prompt the user for input
      printf("\n");
      printf("Letter to guess: ");
      scanf("%s", input_buf);

      // Make sure the input is formatted correctly
      while (1) {
        input_buf[0] = tolower(input_buf[0]);
        if (strlen(input_buf) != 1 || !isalpha(input_buf[0])) {
          printf("Error! Please guess one letter\n");
        } else if (
          strchr(masked, input_buf[0]) != NULL
          || strchr(ic_guesses, input_buf[0]) != NULL
        ) {
          printf("Error! Letter %c has been guessed before. Please guess another letter.\n", input_buf[0]);
        } else {
          break; // Input is well-formatted
        }
        // Keep asking for input
        printf("Letter to guess: ");
        scanf("%s", input_buf);
      }
      send_msg(sock, input_buf);
    }
  }
}
