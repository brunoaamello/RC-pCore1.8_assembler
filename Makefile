SRC_FILES = ./src/main.cc ./src/Instruction.cc ./src/Utils.cc ./src/Line.cc

all: assembler mif hex

assembler:
	g++ -std=c++17 -Wall -o rcassembler $(SRC_FILES) -I"./include"
mif:
	g++ -std=c++17 -Wall -o bin_to_mif ./src/bin_to_mif.cc
hex:
	g++ -std=c++17 -Wall -o bin_to_hex ./src/bin_to_hex.cc
clean:
	rm -f rcassembler
	rm -f bin_to_mif
	rm -f bin_to_hex
