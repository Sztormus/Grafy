CXX=g++
CXXFLAGS+=-g
CXXFLAGS+=-Wall -std=c++11
MAIN=rtv
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
 
all: $(MAIN)
 
$(MAIN): $(OBJ)
	$(CXX) $? -o $@
 
$(OBJ): $(SRC)
	$(CXX) $(CXXFLAGS) -c $*.cpp -o $@
 
.PHONY: clean run backup cB
 
clean:
	rm -f $(MAIN) $(OBJ)

run: $(MAIN)
	./$(MAIN)

graph:
	dot -Tps output.dot -o graph.ps
tree:
	dot -Tps tree.dot -o tree.ps

backup:
	if [ -d "./backup" ]; then rm -r backup; fi
	mkdir backup
	cp $(SRC) backup
	cp *.h backup
 
cB:
	rm -r backup
 
val:
	valgrind --tool=memcheck --leak-check=full ./$(MAIN)
 
class:
	read -p "Enter Class Name:" name; \
	touch $$name.cpp; \
	printf "#include \""$$name.h"\"\n\n#include <iostream>\n\nusing namespace std;\n" > $$name.cpp; \
	touch $$name.h; \
	printf "#pragma once\n\nclass "$$name"{\npublic:\n\nprivate:\n\n};\n" > $$name.h