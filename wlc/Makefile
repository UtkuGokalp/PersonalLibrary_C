CC=gcc
CFLAGS=-Wall -Wextra
SRC=./src/*.c
INCLUDE=./include
TARGET=/usr/bin/wlc

compile_and_run: compile run

compile:
	sudo $(CC) $(CFLAGS) -o $(TARGET) $(SRC) -I$(INCLUDE) -lm -lpthread

run:
	$(TARGET)

clean:
	sudo rm $(TARGET)
