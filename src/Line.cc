#include "Line.h"

Line::Line(const char *line, const size_t count){
    this->count = count;
    original = string(line);
    lower = Utils::tolower(original);
    lower = Utils::removeBreaks(lower);

    pair<string, string> access = separateLabel(lower);

    label = access.first;
    body = access.second;

    access = Instruction::separateLine(body);

    instruction = access.first;
    body = access.second;

    tuple<Instruction::OP, byte, Instruction::ERROR> op = Instruction::parseOp(instruction);

    this->op = get<0>(op);
    opcode = get<1>(op);

    format = Instruction::getFormat(this->op);
    
    if(get<2>(op) == Instruction::ERROR::UNKNOWN_INSTRUCTION || format == Instruction::NO_FORMAT){
        valid = false;
    }else{
        valid = true;
    }

    printf("Line %lu: [%s|%s|%s]\n", this->count, label.c_str(), instruction.c_str(), body.c_str());

}

size_t Line::len(){
    return original.length();
}

size_t Line::numWords(){
    return 1;
}

pair<string, string> Line::separateLabel(const string s){
    string label, body;

    body = string(s);
    size_t end_of_label = body.find_first_of(":");

    if(end_of_label == string::npos){
        label = "";
    }else{
        label = body.substr(0, end_of_label);
        label = Utils::trimm(label);
        body.erase(0, end_of_label+1);
    }

    return make_pair(label, body);
}

string Line::replaceLabel(const string s, const map<string, size_t> label_table, const size_t word_count){
    size_t pos;
    size_t label_len;
    int offset;
    string ns = string(s);
    for(auto it = label_table.begin(); it != label_table.end(); it++){
        pos = ns.find(it->first);
        if(pos != string::npos){
            label_len = it->first.length();
            if(ns.length() == pos + label_len || ::isspace(ns.at(pos + label_len))){
                offset = it->second-(word_count+1);
                ns.erase(pos, label_len);
                ns.insert(pos, std::to_string(offset));
                break;
            }
        }
    }
    return ns;
}

bool Line::hasLabel(){
    return label.length() >= 2;
}

string Line::getLabel(){
    return label;
}

bool Line::isValid(){
    return valid;
}

int Line::processLine(const map<string, size_t> label_table, const size_t word_count){
    tuple<byte, byte, int> bytes;

    if(Instruction::labelAble(op)){
        body = replaceLabel(body, label_table, word_count);
    }


    printf("Line %lu: [%s|%s|%s]\n", this->count, label.c_str(), instruction.c_str(), body.c_str());

    bytes = Instruction::parseBody(body, format, op);
    line[0] = get<0>(bytes);
    line[1] = get<1>(bytes);
    
    line[0] |= opcode;

    vector<Instruction::ERROR> err = Instruction::unpackErrors(get<2>(bytes));
    for(auto it = err.begin(); it != err.end(); it++){
        fprintf(stderr, "Error in line %lu: %s\n", count, Instruction::getError(*it).c_str());
    }

    return get<2>(bytes);
}

vector<byte> Line::getWords(){
    vector<byte> words;
    words.insert(words.end(), line[0]);
    words.insert(words.end(), line[1]);
    return words;
}
