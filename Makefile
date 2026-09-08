# compiler ------------------------------------------------------------------@/
CXX	:= clang++
CC	:= clang

CFLAGS	:= -Wall -Wshadow -Iinclude --std=c23 -g3 -O0

export NIX_HARDENING_ENABLE :=

# output --------------------------------------------------------------------@/
OBJ_DIR := build
SRC_DIR := src
OUTPUT  := bin/program.exe

BIN_DIR := $(dir $(OUTPUT))

SRCS_C   := $(shell find $(SRC_DIR) -name '*.c')
SRCS_CPP := $(shell find $(SRC_DIR) -name '*.cpp')

OBJS := $(subst $(SRC_DIR),$(OBJ_DIR),$(SRCS_C:.c=.o))
OBJS += $(subst $(SRC_DIR),$(OBJ_DIR),$(SRCS_CPP:.cpp=.o))

# building ------------------------------------------------------------------@/
all: $(OUTPUT)

$(OUTPUT): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CFLAGS) -c $< -o $@

$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
