# Project name
PROJ_NAME=zyra

# Project folders
SRC=./src
BUILD=./build

# .c files
C_SRC=$(wildcard $(SRC)/*.c)

# .h files
H_SRC=$(wildcard $(SRC)/*.h)

# Object files
OBJ=$(subst .c,.o,$(subst $(SRC),$(BUILD),$(C_SRC)))

# Compiler
CC=gcc

# Compiler flags
CC_FLAGS=-c      \
		-W       \
		-Wall    \
		-ansi    \
		-pedantic \
		-std=c99

#
# Compilation and linking
#
all: buildFolder $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	@ echo 'Building binary: $^'
	$(CC) $^ -o $@
	@ echo 'Finished building binary: $@'
	@ echo ' '

$(BUILD)/%.o: $(SRC)/%.c $(SRC)/%.h
	@ echo 'Building target: $<' 
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

$(BUILD)/main.o: $(SRC)/main.c $(H_SRC)
	@ echo 'Building main target: $<' 
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

buildFolder:
	@ mkdir $(BUILD) -p

clean:
	@ rm -rf $(BUILD)/*.o $(PROJ_NAME) ~*
	@ rmdir $(BUILD)

run: all
	./$(PROJ_NAME)

.PHONY: all buildFolder clean run