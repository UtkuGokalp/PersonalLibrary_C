CC=gcc
CFLAGS=-Wall -Wextra
SRC=./src/*.c
INCLUDE=./include
TARGET=/usr/bin/extractiso

compile:
	sudo $(CC) $(CFLAGS) -o $(TARGET) $(SRC) -I$(INCLUDE) -lm -lpthread

clean:
	sudo rm $(TARGET)
