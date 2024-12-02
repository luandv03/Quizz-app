# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -I/usr/include/mysql -I/usr/include/cjson -I include

# Linker flags
LDFLAGS = -L/usr/lib -lmysqlclient -lcjson

# Source files
SRCS = src/main.c src/db/connect-db.c src/services/service.c src/controllers/controller.c src/routes/routes.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = server

# Migration files
MIGRATION_SRCS = src/cli_migrate.c
MIGRATION_OBJS = $(MIGRATION_SRCS:.c=.o) src/db/connect-db.o
MIGRATION_TARGET = src/cli_migrate

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile the source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile the migration tool
$(MIGRATION_TARGET): $(MIGRATION_OBJS)
	$(CC) $(MIGRATION_OBJS) -o $(MIGRATION_TARGET) $(LDFLAGS)

# Run the migrations
migrate: $(MIGRATION_TARGET)
	@if [ -z "$(wildcard src/migrations/*.sql)" ]; then \
	echo "No migration files found in the migrations directory."; \
	else \
	for file in src/migrations/*.sql; do \
	echo "Running migration $$file"; \
	./$(MIGRATION_TARGET) $$file; \
	done; \
	fi

# Clean up the build files
clean:
	rm -f $(OBJS) $(TARGET) $(MIGRATION_OBJS) $(MIGRATION_TARGET)

# Run the server
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run