CC:=gcc

CFLAGS:=-Wall -Wextra -Wpedantic -ggdb -O0 -std=c11

LIBS:=  -lm

RAYLIB:= -I$(HOME)/raylib/src/ -L$(HOME)/raylib/src/  -l:libraylib.a 

INPUT:=src/main.c src/TetrisLogic.c src/BorderLogic.c

BUILD_DIR:= build

OUTPUT=$(BUILD_DIR)/TetrisGame

$(OUTPUT): $(INPUT) $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(OUTPUT)  $(INPUT)  $(RAYLIB) $(LIBS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

all: $(OUTPUT)
	$(info [INFO] BUILD GAME SUCCESSFULLY)

run: $(OUTPUT)
	./$(OUTPUT)


clean:
	rm -rv $(BUILD_DIR)

