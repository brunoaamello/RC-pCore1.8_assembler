#include "Utils.h"

string Utils::tolower(const string s){
    string ls(s);
    std::transform(ls.begin(), ls.end(), ls.begin(), ::tolower);
    return ls;
}