CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic -O2

SRC_DIR = src
BUILD_DIR = build
EXEC = programa

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Regla por defecto
all: $(EXEC)

# Crear el ejecutable enlazando los .o
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

# Compilar los .c en .o dentro de build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar los archivos generados
clean:
	rm -rf $(BUILD_DIR) $(EXEC)

.PHONY: all clean
