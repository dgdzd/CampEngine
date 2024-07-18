#include <CampEngine/Utils/filereader.h>
using namespace std;

char* getFileContent(std::string path) {
    ifstream file (path);
    string content = "";
    char* s;
    string line;

    if(file.is_open()) {
        while(getline(file, line)) {
            content += line + "\n";
        }
    }
    s = new char[content.length() + 1];
    strcpy(s, content.c_str());

    return s;
}
