CC:=gcc

CFLAGS:=-Wall -Wextra -Wpedantic -ggdb -O3 -std=c11

LIBS:= -lraylib -lm

INPUT:=main.c blocks.c

OUTPUT=TetrisGame

$(OUTPUT): $(INPUT)
	$(CC) $(CFLAGS) -o $(OUTPUT)  $(INPUT) $(LIBS)


all: $(OUTPUT)
	$(info INFO: CREATED TETRIS SUCCESSFULLY)

run: $(OUTPUT)
	./$(OUTPUT)


clean:
	rm -v $(OUTPUT)

