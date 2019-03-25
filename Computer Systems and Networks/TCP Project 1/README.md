## Protocol
### Request Types:
```bash
BAL [account-name] #Server should respond with a non-negative decimal number
WITHDRAW [account-name] [amount] # Server should respond with `0` if transaction successful
TRANSFER [from-account] [to-account] [amount] #Server should respond with `0` if successful
```
### Error Codes:
```bash
-1 # Account does not exist
-2 # Insufficient fund
-3 # Too Many withdrawals in a minute
```
## Commands
```bash
./client [ip] [port] [...message] # Run Client
./server [port] # Run Server
```
