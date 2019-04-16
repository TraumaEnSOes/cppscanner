CXX=g++
CPPFLAGS=
CXXFLAGS=-std=c++11 -Wall -Wextra -pedantic -g3 -ggdb3

%.o: %.cpp
	@echo Compilando $<
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<

all: main

tokenizer.o: tokenizer.cpp tokenizer.hpp
main.o: main.cpp tokenizer.hpp

main: main.o tokenizer.o
	@echo Generando $@
	@$(CXX) -o $@ $^

.PHONY: clean
clean:
	@echo Limpiando
	@rm -f *.o
	@rm -f main
