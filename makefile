#dotandanino@gmail.com
CXX=clang++
CXXFLAGS=-std=c++2a -g -Wall -Wextra
TARGET=Demo
GUI_TARGET=coup_gui
GUI_SRCS=gui.cpp
GUI_HEADERS=gui.hpp
GUI_OBJS=$(GUI_SRCS:.cpp=.o)
SRCS=Baron.cpp Game.cpp General.cpp Governor.cpp Judge.cpp Merchant.cpp Player.cpp Spy.cpp playerFactory.cpp
HEADERS=Baron.hpp Demo.hpp Game.hpp General.hpp Governor.hpp Judge.hpp Merchant.hpp Player.hpp Spy.hpp playerFactory.hpp
OBJS=$(SRCS:.cpp=.o)

# TEST_TARGET=test_run
# TEST_SRC=test.cpp
# TEST_OBJ=$(TEST_SRC:.cpp=.o)

all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(OBJS) Demo.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) Demo.o

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

GUI: $(GUI_OBJS) $(OBJS)
	clang++ $(GUI_OBJS) $(OBJS) -o $(GUI_TARGET) -lsfml-graphics -lsfml-window -lsfml-system
	./$(GUI_TARGET)
clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o $(GUI_TARGET)

.PHONY: all clean
