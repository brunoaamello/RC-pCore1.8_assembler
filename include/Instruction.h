#include <string>
#include <tuple>
#include <algorithm>
#include <cstddef>

using std::pair;
using std::make_pair;
using std::string;
using std::byte;

class Instruction{
private:
    static string tolower(const string s);

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

    static pair<string, string> separateLine(const string s);
    static pair<OP, byte> parseOp(const string s);
    static FORMAT getFormat(const OP op);
    static pair<byte, byte> parseBody(const string s, const FORMAT f, const OP op = UNKNOWN);

    Instruction(string line);

};