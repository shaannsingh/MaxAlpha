# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
INCLUDES = -Iinclude

# Directories
SRCDIR = src
STRATDIR = $(SRCDIR)/strategies
OBJDIR = obj

# Source files (automatically finds all .cpp files)
MAIN_SRC = main.cpp
SRC_FILES = $(wildcard $(SRCDIR)/*.cpp)
STRAT_FILES = $(wildcard $(STRATDIR)/*.cpp)
ALL_SOURCES = $(MAIN_SRC) $(SRC_FILES) $(STRAT_FILES)

# Object files (replace .cpp with .o and put in obj directory)
MAIN_OBJ = $(OBJDIR)/main.o
SRC_OBJS = $(SRC_FILES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
STRAT_OBJS = $(STRAT_FILES:$(STRATDIR)/%.cpp=$(OBJDIR)/strategies/%.o)
ALL_OBJECTS = $(MAIN_OBJ) $(SRC_OBJS) $(STRAT_OBJS)

# Target executable
TARGET = maxAlpha

# Default target (runs when you type 'make')
all: $(TARGET)

# Create the executable by linking all object files
$(TARGET): $(ALL_OBJECTS)
	@echo "Linking $(TARGET)..."
	$(CXX) $(ALL_OBJECTS) -o $(TARGET)
	@echo "Build complete! Run with: ./$(TARGET)"

# Compile main.cpp
$(OBJDIR)/main.o: main.cpp | $(OBJDIR)
	@echo "Compiling main.cpp..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Compile source files in src/
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Compile strategy files in src/strategies/
$(OBJDIR)/strategies/%.o: $(STRATDIR)/%.cpp | $(OBJDIR)/strategies
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Create directories if they don't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)/strategies

# Clean up build files
clean:
	@echo "Cleaning build files..."
	rm -rf $(OBJDIR) $(TARGET)
	@echo "Clean complete!"

# Rebuild everything from scratch
rebuild: clean all

# Run the program with test parameters
test:
	./$(TARGET) RSI HOOD 10000 50 100

# Debug build (adds debugging symbols, no optimization)
debug: CXXFLAGS = -std=c++17 -Wall -Wextra -g -O0
debug: clean $(TARGET)

# Show help
help:
	@echo "Available commands:"
	@echo "  make         - Build the project"
	@echo "  make clean   - Remove build files"
	@echo "  make rebuild - Clean and build"
	@echo "  make test    - Build and run with test parameters"
	@echo "  make debug   - Build with debug symbols"
	@echo "  make help    - Show this help"

# Tell make that these targets don't create files
.PHONY: all clean rebuild test debug help