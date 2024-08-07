#include <CampEngine/Utils/FileUtils.h>

#include <CampEngine/Utils/ResourceManager.h>

#include <iostream>

using namespace std;

char* getFileContent(std::string path) {
    ifstream file(path);
    file.seekg(0, ios::end);
    const long long size = file.tellg();
    char* contents = new char [size];
    file.seekg (0, ios::beg);
    file.read (contents, size);
    file.close();
    return contents;
}

File::File(const char* path) {
    this->path = path;
}

void File::open(int mode) {
    out = ofstream(path, mode);
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
    std::string s(content);
    unsigned long size = s.size();
    out.write((char*)&size, sizeof(unsigned long));
    out.write((char*)&content, size);
}

template<> void File::write<char*>(char* content) {
    std::string s(content);
    unsigned long size = s.size();
    out.write((char*)&size, sizeof(unsigned long));
    out.write((char*)&content, size);
}

template<> void File::write<unsigned char*>(unsigned char* content) {
    unsigned long size = strlen((char*)content);
    out.write((char*)&size, sizeof(unsigned long));
    out.write((char*)&content, size);
}

template<> void File::write<std::string>(std::string content) {
    unsigned long size = content.size();
    out.write((char*)&size, sizeof(unsigned long));
    out.write(content.c_str(), size);
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
    const char* result;
    in.read((char*)&result, size);
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
    return result;
}

template<> std::string File::read<std::string>(unsigned long size) {
    const char* result;
    in.read((char*)&result, size);
    return std::string(result);
}

template<> const char* File::read<const char*>() {
    const char* result;
    auto size = read<unsigned long>();
    in.read((char*)&result, size);
    return result;
}

template<> unsigned char* File::read<unsigned char*>() {
    unsigned char* result;
    auto size = read<unsigned long>();
    in.read((char*)&result, size);
    return result;
}

template<> std::string File::read<std::string>() {
    const char* result;
    auto size = read<unsigned long>();
    in.read((char*)&result, size);
    return result;
}

template<> Shader File::read<Shader>() {
    auto* vs = read<const char*>();
    auto* fs = read<const char*>();

    Shader result(vs, fs);
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
