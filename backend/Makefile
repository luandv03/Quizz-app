# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -I/usr/include/mysql -I/usr/include/cjson

# Linker flags
LDFLAGS = -L/usr/lib -lmysqlclient -lcjson

# Source files
SRCS = src/main.c src/db/connect-db.c src/services/service.c src/controllers/controller.c src/routes/routes.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = server

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile the source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up the build files
clean:
	rm -f $(OBJS) $(TARGET)

# Run the server
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run