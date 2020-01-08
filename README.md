# chat_better
a real chat program

## run the server
```
make server
./bin/server [port]
```

## run a client and connect
```
make client
./bin/client [IP address] [port]
```

## Example (same machine)
### Commandline 1
```
make all
./bin/server 4000
```
### Commandline 2
```
./bin/client localhost 4000
```

## Clean build
```
make clean
```
