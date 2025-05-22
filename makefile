CXX=clang++
CXXFLAGS=-std=c++2a -g -Wall -Wextra
TARGET=Demo
SRCS=Baron.cpp Demo.cpp Game.cpp General.cpp Governor.cpp Judge.cpp Merchant.cpp Player.cpp Spy.cpp
HEADERS=Baron.hpp Demo.hpp Game.hpp General.hpp Governor.hpp Judge.hpp Merchant.hpp Player.hpp Spy.hpp
OBJS=$(SRCS:.cpp=.o)

# TEST_TARGET=test_run
# TEST_SRC=test.cpp
# TEST_OBJ=$(TEST_SRC:.cpp=.o)

all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# $(TEST_TARGET): $(OBJS) $(TEST_OBJ)
# 	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJ) $(OBJS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

# valgrind: $(TARGET) $(TEST_TARGET)
# 	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TEST_TARGET)
# 	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

# test: $(TEST_TARGET)
# 	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o

.PHONY: all clean
