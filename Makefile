CC=gcc
SOURCES = emu.c
DEFAULT_FLAGS = -Wall -Werror
DEBUG_FLAGS = -Wall -g
LINK_FLAGS = 
TARGET = emu

all: $(SOURCES)
	$(CC) $(DEFAULT_FLAGS) -o $(TARGET) $(SOURCES)
	$(CC) $(DEFAULT_FLAGS) -o as_emu assembler.c

debug: $(SOURCES)
	$(CC) $(DEBUG_FLAGS) -o $(TARGET) $(SOURCES)
	$(CC) $(DEBUG_FLAGS) -o as_emu assembler.c

clean:
	rm -f $(TARGET) as_emu *.o
