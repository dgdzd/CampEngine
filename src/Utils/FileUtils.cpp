#include <CampEngine/Utils/FileUtils.h>

#include <CampEngine/Utils/ResourceManager.h>

#include <iostream>

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

File::File(const char* path) {
    this->path = path;
}

void File::open(int mode, bool write) {
    if(write) out = ofstream(path, mode);
    in = ifstream(path, mode);
}

void File::close() {
    if(out.is_open()) {
        out.flush();
        out.close();
    }
    if(in.is_open()) in.close();
}

char* File::getContent() {
    ifstream file(path);

    file.seekg(0, ios::end);
    const long long size = file.tellg();
    char* contents = new char [size];
    file.seekg (0, ios::beg);
    file.read (contents, size);
    file.close();

    return contents;
}


template<> void File::write<const char*>(const char* content) {
    unsigned long size = strlen(content);
    out.write((char*)&size, sizeof(unsigned long));
    out.write(content, size);
}

template<> void File::write<char*>(char* content) {
    unsigned long size = strlen(content);
    out.write((char*)&size, sizeof(unsigned long));
    out.write(content, size);
}

template<> void File::write<unsigned char*>(unsigned char* content) {
    unsigned long size = strlen((char*)content);
    out.write((char*)&size, sizeof(unsigned long));
    out.write((char*)&content, size);
}

template<> void File::write<std::string>(std::string content) {
    unsigned long size = content.size();
    out.write((char*)&size, sizeof(unsigned long));
    out.write(&content[0], size);
}

template<> void File::write<int>(int content) {
    out.write((char*)&content, sizeof(int));
}

template<> void File::write<float>(float content) {
    out.write((char*)&content, sizeof(float));
}

template<> void File::write<double>(double content) {
    out.write((char*)&content, sizeof(double));
}

template<> void File::write<long>(long content) {
    out.write((char*)&content, sizeof(long));
}

template<> void File::write<short>(short content) {
    out.write((char*)&content, sizeof(short));
}

template<> void File::write<Shader*>(Shader* content) {
    write(content->vertexShaderSource);
    write(content->fragmentShaderSource);
}

template<> void File::write<Texture*>(Texture* content) {
    write(content->data);
    out.write((char*)&content->width, sizeof(int));
    out.write((char*)&content->height, sizeof(int));
}

template<> void File::write<PostProcessor*>(PostProcessor* content) {
    write(&content->PPShader);
    out.write((char*)&content->width, sizeof(int));
    out.write((char*)&content->height, sizeof(int));
}

template<> int File::read<int>() {
    int result;
    in.read((char*)&result, sizeof(int));
    return result;
}

template<> float File::read<float>() {
    float result;
    in.read((char*)&result, sizeof(float));
    return result;
}

template<> double File::read<double>() {
    double result;
    in.read((char*)&result, sizeof(double));
    return result;
}

template<> long File::read<long>() {
    long result;
    in.read((char*)&result, sizeof(long));
    return result;
}

template<> unsigned long File::read<unsigned long>() {
    unsigned long result;
    in.read((char*)&result, sizeof(long));
    return result;
}

template<> short File::read<short>() {
    short result;
    in.read((char*)&result, sizeof(short));
    return result;
}

template<> const char* File::read<const char*>(unsigned long size) {
    char* result;
    in.read(result, size);
    return result;
}

template<> char* File::read<char*>(unsigned long size) {
    char* result;
    in.read((char*)&result, size);
    return result;
}

template<> unsigned char* File::read<unsigned char*>(unsigned long size) {
    unsigned char* result;
    in.read((char*)&result, size);
    //result[size] = '\0';
    return result;
}

template<> std::string File::read<std::string>(unsigned long size) {
    std::string result;
    result.resize(size);
    in.read(&result[0], size);
    return result;
}

template<> const char* File::read<const char*>() {
    auto size = read<unsigned long>();
    char* result = new char[size];
    in.read(result, size);
    return result;
}

template<> char* File::read<char*>() {
    auto size = read<unsigned long>();
    char* result = new char[size];
    in.read(result, size);
    return result;
}

template<> unsigned char* File::read<unsigned char*>() {
    auto size = read<unsigned long>();
    auto* result = new unsigned char[size];
    in.read((char*)&result, size);
    //result[size] = '\0';
    return result;
}

template<> std::string File::read<std::string>() {
    std::string result;
    auto size = read<unsigned long>();
    result.resize(size);
    in.read(&result[0], size);
    return result;
}

template<> Shader File::read<Shader>() {
    auto vs = read<char*>();
    auto fs = read<char*>();

    Shader result;
    result.compiled = false;
    result.vertexShaderSource = vs;
    result.fragmentShaderSource = fs;
    result.compile();
    return result;
}

template<> Texture File::read<Texture>() {
    auto* data = read<unsigned char*>();
    int width = read<int>();
    int height = read<int>();
    Texture result;
    result.generate(width, height, data);
    return result;
}

template<> PostProcessor File::read<PostProcessor>() {
    Shader shader = read<Shader>();
    int width = read<int>();
    int height = read<int>();
    PostProcessor result(shader, width, height);
    return result;
}

void File::flush() {
    out.flush();
}
