#include <utility>

enum Error{
    NO_ERROR,
    UNKNOWN_INSTRUCTION_ERROR,
    STRUCTURAL_HAZARD_WARNING,
    CONTROL_HAZARD_WARNING,
    DATA_HAZARD_WARNING
};


class Line{
    private:

    public:
        Line(char *line);
        ~Line();
        std::pair<Instruction, Error> ProcessLine();

};