CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

TARGET = biblioteca

SRC = $(wildcard src/*.cpp)

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)