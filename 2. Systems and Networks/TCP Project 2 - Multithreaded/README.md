## Protocol Specification
### Server Message
```
+-------------------+----------------------+------------------------+------+
| Msg flag (1 byte) | Word length (1 byte) | Num Incorrect (1 byte) | Data |
+-------------------+----------------------+------------------------+------+
```
If the message flag is unset, the data section is the word chosen (with the letters yet to be guessed replaced by underscores) concatenated with a list of incorrectedly guessed letters. If the message flag is set to a positive number, then the rest of the message is a message string that the client should print out.
### Client Message
```
+---------------------+---------------+
| Msg length (1 byte) | Data (1 byte) |
+---------------------+---------------+
```

## Implementation Idea

The cores of both client and server are implemented in a similar way: Each thread/process, whether it belongs to the client or server, consists of a main loop that listens to incoming messages and reacts/responds to them. For the client, I use the same routine for both single-player and multiplayer modes, because there is essentially no difference in the client behavior. As for the server, I use two seperate routines for two game modes.

Since each individual game must be independent of others, the server is implemented as multithreaded. A counter is used to make sure the number of active game threads does not exceed 3. For each game I use a structure ("game control block") containing several arrays and counters to manage game states. The same structure is used in both game modes, because even though different number of players are involved, the rules for updating game states are mostly the same. In addition to each game being handled by a seperate thread, the game mode selection stage for each client is also handled by a separate thread, because an indecisive player shouldn't block the server from responding to other clients.

## How to Run

`make` to compile,  `./server [port]` to start a server (The optional parameter for filename is not implemented)  and `./client [ip] [port]` to start a client.
