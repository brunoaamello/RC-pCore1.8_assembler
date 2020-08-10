#include "Utils.h"

string Utils::tolower(const string s){
    string ls(s);
    std::transform(ls.begin(), ls.end(), ls.begin(), ::tolower);
    return ls;
}

string Utils::trimm(const string s){
    string ns(s);
    ns.erase(remove_if(ns.begin(), ns.end(), ::isspace), ns.end());
    return ns;
}