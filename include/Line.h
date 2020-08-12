#ifndef ASSEMBLER_LINE
#define ASSEMBLER_LINE

#include <string>
#include <tuple>
#include <cstddef>
#include <vector>
#include <map>

#include "Utils.h"
#include "Instruction.h"

using std::string;
using std::pair;
using std::map;
using std::get;

enum Error{
    NO_ERROR,
    UNKNOWN_INSTRUCTION_ERROR,
    STRUCTURAL_HAZARD_WARNING,
    CONTROL_HAZARD_WARNING,
    DATA_HAZARD_WARNING
};


class Line{
    private:
        string original;
        string lower;
        string post_label;
        string label, instruction, body;
        size_t count;
        Instruction::OP op;
        Instruction::FORMAT format;
        byte opcode;
        bool valid;
        byte line[2];

    public:
        Line(const char *line, const size_t count);
        ~Line();
        
        size_t len();

        static pair<string, string> separateLabel(const string s);
        static string replaceLabel(const string s, const map<string, size_t> label_table, const size_t word_count);

        bool hasLabel();
        string getLabel();
        bool isValid();
        pair<byte, byte> getWord();

        int processLine(const map<string, size_t> label_table, const size_t word_count);
};

#endif