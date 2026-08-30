# compiler ------------------------------------------------------------------@/
CXX	:= clang++
CC	:= clang

# -g3 emits DWARF (required by lldb-dap for breakpoints), -O0 keeps
# line numbers and locals from being optimised away while stepping.
CFLAGS	:= -Wall -Wshadow -Iinclude --std=c23 -g3 -O0

# The nix cc-wrapper appends -D_FORTIFY_SOURCE=2 after our own flags (so
# -U_FORTIFY_SOURCE can't win), and fortify warns on every translation unit
# at -O0. Turning the hardening off is the wrapper's supported escape hatch.
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

# bin/ and build/ are gitignored, so they must be recreated on a fresh
# clone. Order-only prerequisites (after the |) so a new object file
# landing in build/ doesn't relink everything.
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
