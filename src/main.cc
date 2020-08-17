#include <cstdlib>
#include <cstdio>
#include <string>
#include <tuple>
#include <utility>

#include "Utils.h"
#include "Instruction.h"
#include "Line.h"

using std::sscanf;
using std::string;
using std::get;
using std::make_pair;

int main(int argc, char *argv[]){

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
    size_t line_count = 0, word_count = 0;

    Line *line;
    vector<pair<Line*, size_t>> lines;
    map<string, size_t> label_table;
    vector<byte> instruction_bytes;

    // Line read and label processing
    
    printf("\nSeparated lines [label|op|body]:\n");

    while(true){
        line_size = getline(&buffer, &buffer_size, infile);
        if(line_size == EOF){
            break;
        }

        line = new Line(buffer, line_count);
        lines.insert(lines.end(), make_pair(line, 0));
        line_count++;
    }

    // Label compute and store

    for(auto it = lines.begin(); it != lines.end(); it++){
        if(it->first->hasLabel()){
            label_table.insert(make_pair(it->first->getLabel(), word_count));
        }
        if(it->first->isValid()){
            it->second = word_count;
            word_count += it->first->numWords();
        }
    }

    // Instruction processing and output writing

    printf("\nReplaced labels:\n");

    for(auto it = lines.begin(); it != lines.end(); it++){
        if(it->first->isValid()){
            it->first->processLine(label_table, it->second);
            
            instruction_bytes = it->first->getWords();
            for(auto jt = instruction_bytes.begin(); jt != instruction_bytes.end(); jt++){
                fwrite(&(*jt), sizeof(byte), 1, outfile);
            }
        }
    }

    printf("\nFinished parsing file, saved to %s\n", outfilename.c_str());
    printf("Total of %lu words\n%.2f%% of program memory used\nUsed %lu out of %lu bytes\n", word_count, (word_count*2.0)/(64.0*1024.0), word_count*2, (size_t) 64*1024);

    // Cleanup

    for(auto it = lines.begin(); it != lines.end(); it++){
        delete it->first;
    }

    fclose(infile);
    fclose(outfile);

    return 0;
}