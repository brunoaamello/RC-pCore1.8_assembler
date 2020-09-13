#ifndef ASSEMBLER_INSTRUCTION
#define ASSEMBLER_INSTRUCTION

#include <string>
#include <tuple>
#include <cstddef>
#include <vector>

#include "Utils.h"

using std::tuple;
using std::pair;
using std::vector;
using std::string;
using std::byte;

class Instruction{
public:
    enum OP{
        SMSB,
        NOP,
        SL,
        SR,
        MOV,
        ADD,
        ADDi,
        ADDC,
        ADDCi,
        SUB,
        SUBi,
        NAND,
        NANDi,
        NOR,
        NORi,
        XOR,
        XORi,
        NOT,
        SW,
        SWi,
        SWC,
        LW,
        LWi,
        LWC,
        J,
        JAL,
        RET,
        JC,
        JGZ,
        JEZ,
        JLZ,
        MOVi,
        UNKNOWN
    };
    using OP = enum OP;
    enum FORMAT{
        SMSB_NOP,
        R4_R4_I3,
        R4_R4_R3,
        R3_I8,
        R4_R4,
        I11,
        NO_FORMAT
    };
    using FORMAT = enum FORMAT;
    enum ERROR{
        NO_ERROR = 0x00,
        UNKNOWN_INSTRUCTION = 0x01,
        IMM3_OUT_OF_RANGE = 0x02,
        IMM8_OUT_OF_RANGE = 0x04,
        OFFSET_OUT_OF_RANGE = 0x08,
        REGISTER_OUT_OF_RANGE = 0x16
    };
    using ERROR = enum ERROR;

    static string getError(const ERROR err);
    static vector<ERROR> unpackErrors(const int err);

    static pair<string, string> separateLine(const string s);
    static tuple<OP, byte, ERROR> parseOp(const string s);
    static FORMAT getFormat(const OP op);
    static tuple<byte, byte, int> parseBody(const string s, const FORMAT f, const OP op = UNKNOWN, const bool print_errors = true);

    static bool labelAble(const OP op);

};

#endif