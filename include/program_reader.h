#ifndef __PROGRAM_READER_H__
#define __PROGRAM_READER_H__

#include <vector>

class ProgramReader {
public:
    static std::vector<uint8_t> readProgram(const std::string &filepath);
};

#endif
