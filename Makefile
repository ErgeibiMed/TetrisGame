CC:=gcc

CFLAGS:= -O3 -std=c11

CFLAGS_WITH_DEBUG:=-Wall -Wextra -Wpedantic -ggdb -O0 -std=c11

LIBS:=  -lm

RAYLIB:= -I$(HOME)/raylib/src/ -L$(HOME)/raylib/src/  -l:libraylib.a 

INPUT:= src/main.c src/TetrisLogic.c src/BorderLogic.c

BUILD_DIR:= build

OUTPUT=$(BUILD_DIR)/TetrisGame

DEBUG=$(BUILD_DIR)/TetrisGameUnoptimized

$(DEBUG): $(INPUT) $(BUILD_DIR)
	@printf "\e[1;32mBuilding project unoptimized and with debug symbol...\e[0m\n"
	@printf "\n"
	$(CC) $(CFLAGS_WITH_DEBUG) -o $(DEBUG)  $(INPUT)  $(RAYLIB) $(LIBS)
	@printf "\n"
	@printf "\e[1;32mBuild complete!\e[0m\n"
	@printf "\n"

$(OUTPUT): $(INPUT) $(BUILD_DIR)
	@printf "\e[1;32mBuilding project with optimization enabled...\e[0m\n"
	@printf "\n"
	$(CC) $(CFLAGS) -o $(OUTPUT)  $(INPUT)  $(RAYLIB) $(LIBS)
	@printf "\n"
	@printf "\e[1;32mBuild complete!\e[0m\n"
	@printf "\n"


$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

all:  $(DEBUG) $(OUTPUT) 
	@printf "\e[1;32mTHE GAME HAS BEEN BUILT SUCCESSFULLY!\e[0m\n"
	@printf "\n"
	@printf "\e[1;32mTHE BINARYS ARE LOCATED IN THE build FOLDER!\e[0m\n"

run: $(DEBUG)
	./$(DEBUG)


clean:
	rm -rv $(BUILD_DIR)

