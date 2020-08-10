#include "Line.h"

Line::Line(const char *line, const size_t count){
    this->count = count;
    original = string(line);
    lower = Utils::tolower(original);

    pair<string, string> access = separateLabel(lower);

    label = access.first;
    body = access.second;

    access = Instruction::separateLine(body);

    instruction = access.first;
    body = access.second;

    tuple<Instruction::OP, byte, Instruction::ERROR> op = Instruction::parseOp(instruction);

    this->op = get<0>(op);
    opcode = get<1>(op);
    if(get<2>(op) == Instruction::ERROR::UNKNOWN_INSTRUCTION){
        valid = false;
    }else{
        valid = true;
    }

}

size_t Line::len(){
    return original.length();
}

pair<string, string> Line::separateLabel(const string s){
    string label, body;

    body = string(s);
    size_t end_of_label = body.find_first_of(":");

    if(end_of_label == string::npos){
        label = "";
    }else{
        label = body.substr(0, end_of_label-1);
        label = Utils::trimm(label);
        body.erase(0, end_of_label);
    }

    return make_pair(label, body);
}

string Line::replaceLabel(const string s, const map<string, size_t> label_table, const size_t word_count){
    size_t pos;
    size_t label_len;
    int offset;
    string ns = string(s);
    for(auto it = label_table.begin(); it != label_table.end(); it++){
        pos = s.find(it->first);
        if(pos != string::npos){
            label_len = it->first.length();
            offset = it->second-(word_count+1);
            ns.erase(pos, label_len);
            ns.insert(pos, std::to_string(offset));
            break;
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

int Line::processLine(const size_t word_count){

}