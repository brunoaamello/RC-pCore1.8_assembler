#include <string>
#include <tuple>
#include <cstddef>

#include "Utils.h"

using std::tuple;
using std::pair;
using std::make_pair;
using std::string;
using std::byte;

class Instruction{
public:
    enum OP{
        SMSB,
        SL,
        SR,
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
        NOP,
        MOV,
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
        UNKNOWN_INSTRUCTION,
        IMM3_OUT_OF_RANGE,
        IMM8_OUT_OF_RANGE,
        OFFSET_OUT_OF_RANGE,
        REGISTER_OUT_OF_RANGE,
        NO_ERROR
    };
    using ERROR = enum ERROR;

    static pair<string, string> separateLine(const string s);
    static tuple<OP, byte, ERROR> parseOp(const string s);
    static FORMAT getFormat(const OP op);
    static tuple<byte, byte, ERROR> parseBody(const string s, const FORMAT f, const OP op = UNKNOWN, bool print_errors = false);

    Instruction(string line);

};