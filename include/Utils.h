#ifndef ASSEMBLER_UTILS
#define ASSEMBLER_UTILS

#include <string>
#include <algorithm>

using std::string;

class Utils {

public:
    static string tolower(const string s);
    static string trimm(const string s);

};

#endif