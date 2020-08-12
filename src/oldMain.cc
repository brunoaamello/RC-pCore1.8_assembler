#include <cstdlib>
#include <cstdio>
#include <string>
#include <tuple>

#include "Utils.h"
#include "Instruction.h"
#include "Line.h"

using std::sscanf;
using std::string;
using std::get;

int main(int argc, char *argv[]){

/*
    string infilename;

    if(argc <= 1){
        printf("File name not provided, will use default of 'program.a'\n");
        infilename = "program.a";
    }else{
        infilename = string(argv[1]);
    }
    if(argc >= 3){
        printf("Too many arguments, at the momment this program only supports assembling 1 file at a time.\n");
    }

    FILE* infile = fopen64(infilename.c_str(), "r");

    if(infile == NULL){
        printf("Failed to open input file %s\n", infilename.c_str());
        exit(-1);
    }
    
    string outfilename = infilename.substr(0, infilename.find_last_of("."));
    outfilename.append(".bin");

    FILE* outfile = fopen64(outfilename.c_str(), "wb+");

    if(outfile == NULL){
        printf("Failed to open output file %s\n", outfilename.c_str());
        exit(-1);
    }

    static size_t buffer_size = 128;
    char* buffer = (char*) calloc(buffer_size, sizeof(char));

    int line_size;
    size_t line_count = 0;

*/


/*
    string line;
    pair<string, string> sep;
    tuple<Instruction::OP, byte, Instruction::ERROR> op;
    Instruction::FORMAT f;
    tuple<byte, byte, int> bytes;

    while(true){
        line_size = getline(&buffer, &buffer_size, infile);
        if(line_size == EOF){
            break;
        }
        
        line = string(buffer);
        sep = Instruction::separateLine(line);
        op = Instruction::parseOp(sep.first);
        f = Instruction::getFormat(get<0>(op));
        bytes = Instruction::parseBody(sep.second, f, get<0>(op));
        get<0>(bytes) |= get<1>(op);
        

        if(get<0>(op)!=Instruction::UNKNOWN && f!=Instruction::NO_FORMAT){
        
            fwrite(&get<0>(bytes), sizeof(byte), 1, outfile);
            fwrite(&get<1>(bytes), sizeof(byte), 1, outfile);
        }
        printf("Line %lu parsed\r", line_count);
        line_count++;
    }
*/

    string line0 = "FIB: NOP";
    line0 = Utils::tolower(line0);
    pair<string, string> label_body = Line::separateLabel(line0);
    string label = label_body.first;
    string body = label_body.second;
    printf("Label: %s\n", label.c_str());
    printf("Body: %s\n", body.c_str());
    
    map<string, size_t> label_map;

    label_map.insert(make_pair(label, 0));

    string og = "j fib";
    string replaced = Line::replaceLabel(og, label_map, 7);
    
    printf("Original: %s\n", og.c_str());
    printf("Replaced: %s\n", replaced.c_str());


/*
    printf("\nFinished parsing file, saved to %s\n", outfilename.c_str());

    fclose(infile);
    fclose(outfile);

*/

    return 0;
}