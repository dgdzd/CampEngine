#ifndef CE_FILE_UTILS_H
#define CE_FILE_UTILS_H

/*!
* FileUtils v1.0
* A simple util which can be used to read, create or modify files easily
*/

#include <fstream>
#include <string>

char* getFileContent(std::string path);

class File {
private:
    std::ofstream out;
    std::ifstream in;

public:
    std::string path;

    File(const char* path);

    void open(int mode, bool write=true);
    void close();
    char* getContent();
    template<typename Type> void write(Type content);
    template<typename Type> void write(Type content, unsigned long size);
    template<typename Type> Type read(unsigned long size);
    template<typename Type> Type read();
    void flush();
};

#endif
