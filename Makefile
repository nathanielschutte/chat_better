CC = g++
CFLAGS = -Wall -g

CTARGET = client
STARGET = server

SDIR = src

all: $(CTARGET).cpp $(STARGET).cpp
	mkdir bin
	mv $(CTARGET) bin
	mv $(STARGET) bin

$(CTARGET): $(CTARGET).cpp
	mkdir bin
	mv $(CTARGET) bin

$(STARGET): $(STARGET).cpp
	mkdir bin
	mv $(STARGET) bin

$(CTARGET).cpp:
	$(CC) $(CFLAGS) -o $(CTARGET) $(SDIR)/$(CTARGET).cpp

$(STARGET).cpp:
	$(CC) $(CFLAGS) -o $(STARGET) $(SDIR)/$(STARGET).cpp

clean:
	rm -r bin
