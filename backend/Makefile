# Compiler
CC = gcc


# Compiler flags
CFLAGS = -Wall -I/usr/local/mysql/include -I/opt/homebrew/opt/cjson/include -I include
# install_name_tool -add_rpath /usr/local/mysql/lib src/cli_migrate
LDFLAGS =  -L/usr/local/mysql/lib -lmysqlclient  -L/opt/homebrew/opt/cjson/lib -lcjson

# Source files
SRCS = $(wildcard src/**/*.c) $(wildcard src/**/**/*.c) src/main.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = server

# Migration files
MIGRATION_SRCS = src/cli_migrate.c
MIGRATION_OBJS = $(MIGRATION_SRCS:.c=.o) src/db/connect-db.o
MIGRATION_TARGET = src/cli_migrate

# Seed files
SEED_SRCS = src/cli_seed.c
SEED_OBJS = $(SEED_SRCS:.c=.o) src/db/connect-db.o
SEED_TARGET = src/cli_seed

# Default target
all: $(TARGET)
	install_name_tool -add_rpath /usr/local/mysql/lib $(TARGET)
# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile the source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile the migration tool
$(MIGRATION_TARGET): $(MIGRATION_OBJS)
	$(CC) $(MIGRATION_OBJS) -o $(MIGRATION_TARGET) $(LDFLAGS)

# Compile the seed tool
$(SEED_TARGET): $(SEED_OBJS)
	$(CC) $(SEED_OBJS) -o $(SEED_TARGET) $(LDFLAGS)

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

# Run seeds
seed: $(SEED_TARGET)
	@if [ -z "$(wildcard src/seeder/*.sql)" ]; then \
	echo "No seed files found in the seeder directory."; \
	else \
	for file in src/seeder/*.sql; do \
	echo "Running seeder $$file"; \
	./$(SEED_TARGET) $$file; \
	done; \
	fi

# Clean up the build files
clean:
	rm -f $(OBJS) $(TARGET) $(MIGRATION_OBJS) $(MIGRATION_TARGET)

# Run the server
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run