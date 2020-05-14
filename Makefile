CC=gcc
SOURCE_DIR = src
DEFAULT_FLAGS = -Wall -Werror
DEBUG_FLAGS = -Wall -g
LINK_FLAGS = 
TARGET = emu

all: $(SOURCES)
	$(CC) $(DEFAULT_FLAGS) -o $(TARGET) $(SOURCE_DIR)/emu.c
	$(CC) $(DEFAULT_FLAGS) -o as_emu $(SOURCE_DIR)/assembler.c

debug: $(SOURCES)
	$(CC) $(DEBUG_FLAGS) -o $(TARGET) $(SOURCE_DIR)/emu.c
	$(CC) $(DEBUG_FLAGS) -o as_emu $(SOURCE_DIR)/assembler.c

clean:
	rm -f $(TARGET) as_emu *.o
