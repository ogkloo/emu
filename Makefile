CC=gcc
SOURCES = emu.c
DEFAULT_FLAGS = -Wall -Werror
DEBUF_FLAGS = -Wall -g
LINK_FLAGS = 
TARGET = emu

all: $(SOURCES)
	$(CC) $(DEFAULT_FLAGS) -o $(TARGET) $(SOURCES)

debug: $(SOURCES)
	$(CC) $(DEBUF_FLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET) *.o
