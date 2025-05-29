#dotandanino@gmail.com
CXX=clang++
CXXFLAGS=-std=c++2a -g -Wall -Wextra
TARGET=Demo
GUI_TARGET=coup_gui
GUI_SRCS=GUI/gui.cpp
GUI_HEADERS=GUI/gui.hpp
GUI_OBJS=$(GUI_SRCS:.cpp=.o)
SRCS=cppFiles/Baron.cpp cppFiles/Game.cpp cppFiles/General.cpp cppFiles/Governor.cpp cppFiles/Judge.cpp cppFiles/Merchant.cpp cppFiles/Player.cpp cppFiles/Spy.cpp cppFiles/playerFactory.cpp
HEADERS=hppFiles/Baron.hpp hppFiles/Demo.hpp hppFiles/Game.hpp hppFiles/General.hpp hppFiles/Governor.hpp hppFiles/Judge.hpp hppFiles/Merchant.hpp hppFiles/Player.hpp hppFiles/Spy.hpp hppFiles/playerFactory.hpp
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

gui: $(GUI_OBJS) $(OBJS)
	clang++ $(GUI_OBJS) $(OBJS) -o $(GUI_TARGET) -lsfml-graphics -lsfml-window -lsfml-system
	./$(GUI_TARGET)
clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o $(GUI_TARGET) $(GUI_OBJS) Demo.o $(OBJS)

.PHONY: all clean
