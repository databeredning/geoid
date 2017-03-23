PROJECT_NAME = geoid-hm
LIB_PATH = /usr/local/lib
SOURCE_FILES = $(PROJECT_NAME).c 

################################################################

CFLAGS += -I .
CFLAGS += -I /usr/local/include
CFLAGS += -DDEBUG

CC = gcc

OBJECT_FILES = $(PROJECT_NAME).o

LINKER_OPTIONS = -g

C_OPTIONS = -c -g -O3

all: $(PROJECT_NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(C_OPTIONS) $< -o $@

$(PROJECT_NAME): $(OBJECT_FILES)
	$(CC) $(LINKER_OPTIONS) -o $@ $(OBJECT_FILES) -L$(LIB_PATH) -lGeographic

clean:
	rm *.o
