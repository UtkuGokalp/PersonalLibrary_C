CC=gcc
CFLAGS=-Wall -Wextra
SRC=./src/*.c
INCLUDE=./include/
TARGET=./bin/out

compile_and_run: compile run

compile:
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) -I$(INCLUDE)

run:
	$(TARGET)

clean:
	rm $(TARGET)
