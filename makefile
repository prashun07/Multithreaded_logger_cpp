CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -pthread 
TARGET := main

SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp=.o)
HEADERS := $(wildcard *.h)
LOGFILE := run_log.txt

\
#build target
all: run

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

run: $(TARGET)
	@echo "Running $(TARGET):"
	./$(TARGET)

#clean target
clean:
	rm -f *.o $(TARGET) $(LOGFILE)