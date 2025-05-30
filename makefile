#dotandanino@gmail.com
CXX=clang++
CXXFLAGS=-std=c++2a -g -Wall -Wextra
TARGET=Demo
GUI_TARGET=coup_gui
GUI_SRCS=GUI/gui.cpp
GUI_HEADERS=GUI/gui.hpp
GUI_OBJS=$(GUI_SRCS:.cpp=.o)
SRCS=srcs/Baron.cpp srcs/Game.cpp srcs/General.cpp srcs/Governor.cpp srcs/Judge.cpp srcs/Merchant.cpp srcs/Player.cpp srcs/Spy.cpp srcs/playerFactory.cpp
HEADERS=include/Baron.hpp include/Demo.hpp include/Game.hpp include/General.hpp include/Governor.hpp include/Judge.hpp include/Merchant.hpp include/Player.hpp include/Spy.hpp include/playerFactory.hpp
OBJS=$(SRCS:.cpp=.o)

TEST_TARGET=test_run
TEST_SRCS=TEST/test.cpp
TEST_OBJ=TEST/test.o
all: $(TARGET) $(TEST_TARGET) $(GUI_TARGET)

gui: $(GUI_TARGET)

$(TARGET): $(OBJS) srcs/Demo.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) srcs/Demo.o
	./Demo

$(TEST_TARGET): $(OBJS) $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJ) $(OBJS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

valgrind: $(TARGET) $(TEST_TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TEST_TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(GUI_TARGET): $(GUI_OBJS) $(OBJS)
	clang++ $(GUI_OBJS) $(OBJS) -o $(GUI_TARGET) -lsfml-graphics -lsfml-window -lsfml-system
	./$(GUI_TARGET)
clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o $(GUI_TARGET) $(GUI_OBJS) srcs/Demo.o $(OBJS) TEST/test.o

.PHONY: all clean
