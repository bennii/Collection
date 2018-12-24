# Declaration of variables
CC = g++
CC_FLAGS = -Wall -g -lsocket -lnsl -I/usr/include

# File names
EXEC = server
BUILDDIR = build
SOURCEDIR = .
SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
