SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

SERIAL_FILE = mandelbrot-serial
SERIAL_BIN := $(BIN_DIR)/$(SERIAL_FILE)

OMP_FILE = mandelbrot-omp
OMP_BIN := $(BIN_DIR)/$(OMP_FILE)

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CPPFLAGS := -Iinclude -MMD -MP # -I is a preprocessor flag, not a compiler flag
CFLAGS := -Wall              # some warnings about bad code
LDFLAGS := -Llib              # -L is a linker flag
LDLIBS := -lm                # Left empty if no libs are needed

DEPS := $(OBJS:.o=.d)

.PHONY: all serial omp clean

all: $(SERIAL_BIN) $(OMP_BIN)

serial: $(SERIAL_BIN)

omp: $(OMP_BIN)

$(SERIAL_BIN): $(filter-out $(OBJ_DIR)/$(OMP_FILE).o, $(OBJS)) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OMP_BIN): $(filter-out $(OBJ_DIR)/$(SERIAL_FILE).o, $(OBJS)) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@ -fopenmp

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@

clean: 
	$(RM) -r $(OBJ_DIR) $(BIN_DIR)

-include $(DEPS)