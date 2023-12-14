CC=gcc
CFLAGS=-Wall -Wextra
SRC=./src/*.c
INCLUDE=./include/
TARGET=./bin/out

compile_and_run: compile run

compile:
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) -I$(INCLUDE)

compile_o1:
	$(CC) $(CFLAGS) -O1 -o $(TARGET) $(SRC) -I$(INCLUDE)

compile_o2:
	$(CC) $(CFLAGS) -O2 -o $(TARGET) $(SRC) -I$(INCLUDE)

compile_o3:
	$(CC) $(CFLAGS) -O3 -o $(TARGET) $(SRC) -I$(INCLUDE)

compile_debugsyms:
	$(CC) $(CFLAGS) -ggdb3 -o $(TARGET) $(SRC) -I$(INCLUDE)

run:
	$(TARGET)

clean:
	rm $(TARGET)
