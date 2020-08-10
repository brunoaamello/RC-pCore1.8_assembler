#include "Instruction.h"

using OP = Instruction::OP;
using FORMAT = Instruction::FORMAT;
using ERROR = Instruction::ERROR;

pair<string, string> Instruction::separateLine(const string s){
    char op_chars[10];
    sscanf(s.c_str(), "%s", op_chars);
    string op(op_chars);
    string body(s);
    body.erase(0, body.find(op)+op.length()+1);
    return make_pair(op, body);
}

string Instruction::getError(const ERROR err){
    string err_msg = "";
    switch(err){
        case IMM3_OUT_OF_RANGE:
            err_msg = "Immediate(3-bits) out of range [0, 7]";
        case IMM8_OUT_OF_RANGE:
            err_msg = "Immediate(8-bits) out of range [0, 255]";
        case OFFSET_OUT_OF_RANGE:
            err_msg = "Offset(11-bits) out of range [-1024, 1023]";
        case REGISTER_OUT_OF_RANGE:
            err_msg = "Register out of range [0, 15]";
        case UNKNOWN_INSTRUCTION:
            err_msg = "Unknown Instruction";
        case NO_ERROR:
            err_msg = "No Error";
    }
    return err_msg;
}

vector<ERROR> Instruction::unpackErrors(const int err){
    int local_err;
    vector<ERROR> errors;

    if(err){
        local_err = err & IMM3_OUT_OF_RANGE;
        if (local_err){
            errors.insert(errors.end(), IMM3_OUT_OF_RANGE);
        }
        local_err = err & IMM8_OUT_OF_RANGE;
        if (local_err){
            errors.insert(errors.end(), IMM3_OUT_OF_RANGE);
        }
        local_err = err & OFFSET_OUT_OF_RANGE;
        if (local_err){
            errors.insert(errors.end(), IMM3_OUT_OF_RANGE);
        }
        local_err = err & REGISTER_OUT_OF_RANGE;
        if (local_err){
            errors.insert(errors.end(), IMM3_OUT_OF_RANGE);
        }
    } else{
        errors.insert(errors.end(), NO_ERROR);
    }
    return errors;
}

tuple<OP, byte, ERROR> Instruction::parseOp(const string s){
    OP local_op = UNKNOWN;
    byte opcode = byte(0x00);
    ERROR err = NO_ERROR;
    if(s == "smsb"){
        local_op = SMSB;
        opcode = byte(0x00);
    }else if(s == "nop"){
        local_op = NOP;
        opcode = byte(0x00);
    }else if(s == "sl"){
        local_op = SL;
        opcode = byte(0x08);
    }else if(s == "mov"){
        local_op = MOV;
        opcode = byte(0x08);
    }else if(s == "sr"){
        local_op = SR;
        opcode = byte(0x10);
    }else if(s == "add"){
        local_op = ADD;
        opcode = byte(0x18);
    }else if(s == "addi"){
        local_op = ADDi;
        opcode = byte(0x20);
    }else if(s == "addc"){
        local_op = ADDC;
        opcode = byte(0x28);
    }else if(s == "addci"){
        local_op = ADDCi;
        opcode = byte(0x30);
    }else if(s == "sub"){
        local_op = SUB;
        opcode = byte(0x38);
    }else if(s == "subi"){
        local_op = SUBi;
        opcode = byte(0x40);
    }else if(s == "nand"){
        local_op = NAND;
        opcode = byte(0x48);
    }else if(s == "nandi"){
        local_op = NANDi;
        opcode = byte(0x50);
    }else if(s == "nor"){
        local_op = NOR;
        opcode = byte(0x58);
    }else if(s == "nori"){
        local_op = NORi;
        opcode = byte(0x60);
    }else if(s == "xor"){
        local_op = XOR;
        opcode = byte(0x68);
    }else if(s == "xori"){
        local_op = XORi;
        opcode = byte(0x70);
    }else if(s == "not"){
        local_op = NOT;
        opcode = byte(0x78);
    }else if(s == "sw"){
        local_op = SW;
        opcode = byte(0x80);
    }else if(s == "swi"){
        local_op = SWi;
        opcode = byte(0x88);
    }else if(s == "swc"){
        local_op = SWC;
        opcode = byte(0x90);
    }else if(s == "lw"){
        local_op = LW;
        opcode = byte(0x98);
    }else if(s == "lwi"){
        local_op = LWi;
        opcode = byte(0xA0);
    }else if(s == "lwc"){
        local_op = LWC;
        opcode = byte(0xA8);
    }else if(s == "j"){
        local_op = J;
        opcode = byte(0xB0);
    }else if(s == "jal"){
        local_op = JAL;
        opcode = byte(0xB8);
    }else if(s == "ret"){
        local_op = RET;
        opcode = byte(0xC0);
    }else if(s == "jc"){
        local_op = JC;
        opcode = byte(0xC8);
    }else if(s == "jgz"){
        local_op = JGZ;
        opcode = byte(0xD0);
    }else if(s == "jez"){
        local_op = JEZ;
        opcode = byte(0xD8);
    }else if(s == "jlz"){
        local_op = JLZ;
        opcode = byte(0xE0);
    }else if(s == "movi"){
        local_op = MOVi;
        opcode = byte(0xE8);
    }else{
        err = UNKNOWN_INSTRUCTION;
    }

    return make_tuple(local_op, opcode, err);
}

FORMAT Instruction::getFormat(const OP op){
    switch (op){
    case SMSB:
    case NOP:
        return SMSB_NOP; // 0 + 2 = 2
    case SL:
    case SR:
    case MOV:
        return R4_R4_I3; // 2 + 3 = 5
    case ADD:
    case ADDC:
    case SUB:
    case NAND:
    case NOR:
    case XOR:
        return R4_R4_R3; // 5 + 6 = 11
    case ADDi:
    case ADDCi:
    case SUBi:
    case NANDi:
    case NORi:
    case XORi:
    case SWi:
    case LWi:
    case MOVi:
        return R3_I8; // 11 + 9 = 20
    case NOT:
    case SW:
    case SWC:
    case LW:
    case LWC:
    case RET:
        return R4_R4; // 20 + 6 = 26
    case J:
    case JAL:
    case JC:
    case JGZ:
    case JEZ:
    case JLZ:
        return I11; // 26 + 6 = 32    
    default:
        return NO_FORMAT;
    }
}

tuple<byte, byte, int> Instruction::parseBody(const string s, const FORMAT f, const OP op, const bool print_errors){

    byte msb = byte(0);
    byte lsb = byte(0);
    int err = NO_ERROR;
    byte access;
    int ra = 0, rb = 0, rc = 0;
    int imm = 0;
    int set_msb = 0, en = 0;

    switch(f){
        case SMSB_NOP:
            if(op == SMSB){
                sscanf(s.c_str(), "%d %d", &en, &set_msb);
                if(set_msb){
                    msb |= byte(0b00000100);
                }
                if(en){
                    msb |= byte(0b00000010);
                }
            }
            break;
        case R4_R4_I3:
            sscanf(s.c_str(), "R%d R%d %d", &ra, &rb, &imm);
            if(imm > 7){
                if(print_errors){
                    fprintf(stderr, "Immediate of value %d out of range\n", imm);
                }
                err |= IMM3_OUT_OF_RANGE;
                imm %= 8;
            }
            msb |= byte(imm);
            if(rb > 15){
                if(print_errors){
                    fprintf(stderr, "Register of value %d out of range\n", rb);
                }
                err |= REGISTER_OUT_OF_RANGE;
                rb %= 16;
            }
            access = byte(rb);
            access <<= 4;
            lsb |= access;
            if(ra > 15){
                if(print_errors){
                    fprintf(stderr, "Register of value %d out of range\n", ra);
                }
                err |= REGISTER_OUT_OF_RANGE;
                ra %= 16;
            }
            lsb |= byte(ra);
            break;
        case R4_R4_R3:
            sscanf(s.c_str(), "R%d R%d R%d", &ra, &rb, &rc);
            if(rc > 15){
                if(print_errors){
                    fprintf(stderr, "Register of value %d out of range\n", rc);
                }
                err |= REGISTER_OUT_OF_RANGE;
                rc %= 8;
            }
            msb |= byte(rc);
            if(rb > 15){
                if(print_errors){
                    fprintf(stderr, "Register of value %d out of range\n", rb);
                }
                err |= REGISTER_OUT_OF_RANGE;
                rb %= 16;
            }
            access = byte(rb);
            access <<= 4;
            lsb |= access;
            if(ra > 15){
                if(print_errors){
                    fprintf(stderr, "Register of value %d out of range\n", ra);
                }
                err |= REGISTER_OUT_OF_RANGE;
                ra %= 16;
            }
            lsb |= byte(ra);
            break;
        case R3_I8:
            sscanf(s.c_str(), "R%d %d", &ra, &imm);
            if(ra > 15){
                if(print_errors){
                    fprintf(stderr, "Register of value %d out of range\n", ra);
                }
                err |= REGISTER_OUT_OF_RANGE;
                ra %= 8;
            }
            lsb |= byte(ra);
            if(imm > 255){
                if(print_errors){
                    fprintf(stderr, "Immediate of value %d out of range\n", imm);
                }
                err |= IMM8_OUT_OF_RANGE;
                imm %= 256;
            }
            access = byte(imm);
            access <<= 3;
            lsb |= access;
            access = byte(imm);
            access >>= 5;
            msb |= access;
            break;
        case R4_R4:
            sscanf(s.c_str(), "R%d R%d", &ra, &rb);
            if(rb > 15){
                if(print_errors){
                    fprintf(stderr, "Register of value %d out of range\n", rb);
                }
                err |= REGISTER_OUT_OF_RANGE;
                rb %= 16;
            }
            access = byte(rb);
            access <<= 4;
            lsb |= access;
            if(ra > 15){
                if(print_errors){
                    fprintf(stderr, "Register of value %d out of range\n", ra);
                }
                err |= REGISTER_OUT_OF_RANGE;
                ra %= 16;
            }
            lsb |= byte(ra);
            break;
        case I11:
            sscanf(s.c_str(), "%d", &imm);
            if(imm > 1023 || imm < -1024){
                if(print_errors){
                    fprintf(stderr, "Offset of value %d out of range\n", imm);
                }
                err |= OFFSET_OUT_OF_RANGE;
                imm %= 1024;
            }
            rc = imm >> 8;
            access = byte(rc) & byte(0b00000111);
            msb |= access;
            imm %= 256;
            lsb |= byte(imm);
            break;
        case NO_FORMAT:
            break;
    }

    return make_tuple(msb, lsb, err);
}


