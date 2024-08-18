CXX = g++
CXXFLAGS = -std=c++17 -fpermissive -g
TARGET = foxScript
SRCS = main.cpp interpreter/lexer/lexer.cpp interpreter/nodes/concrete_nodes.cpp interpreter/parser/parser.cpp interpreter/tokens/token_type.cpp interpreter/tokens/token.cpp interpreter/visitors/eval_visitor.cpp interpreter/visitors/print_visitor.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean