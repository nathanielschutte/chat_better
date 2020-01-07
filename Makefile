CC = g++
CFLAGS = -Wall -g

CTARGET = client
STARGET = server

SDIR = src


all: $(CTARGET) $(STARGET)

client: $(CTARGET)

server: $(STARGET)

$(CTARGET): $(CTARGET).c
	$(CC) $(CFLAGS) -o $(CTARGET) $(CTARGET).c

$(STARGET): $(SDIR)/$(STARGET).c
	$(CC) $(CFLAGS) -o $(STARGET) $(STARGET).c
