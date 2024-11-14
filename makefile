CXX = g++-11
CXXFLAGS = -std=c++17 -fpermissive -g
LDFLAGS = -pthread -lstdc++
TARGET = foxScript.out
SRCS = main.cpp interpreter/lexer/lexer.cpp interpreter/nodes/concrete_nodes.cpp interpreter/parser/parser.cpp interpreter/tokens/token.cpp interpreter/visitors/print_visitor.cpp interpreter/runtime/values.cpp
OBJS = $(SRCS:.cpp=.o)

all: clean $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean