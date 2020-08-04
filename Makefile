

SRC_FILES = ./src/main.cc ./src/Instruction.cc

all:
	g++ -std=c++17 -Wall -o rcassembler $(SRC_FILES) -I"./include"

clean:
	rm -f rcassembler
