#include <iostream>
#include <string>
#include <fstream>

/** path: path to file */
std::string readFile(const char* path) {
    std::string rtrn;
    std::fstream file(path);
    std::string line;
    while (getline(file, line)) {
        rtrn.append(line+"\n");
    }
    return rtrn;
}
