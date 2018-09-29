#include <iostream>
#include <fstream>
#include <string.h>

#include "include/json/json.h"


using namespace std;

bool parse_json_file(const std::string& file_name, Json::Value& msg)
{
    ifstream file(file_name);
    if (!file)
    {
        std::cout << "Open [" << file_name << "] failed\n";
        return false;
    }
    file.seekg(0, ios::end);
    long len = file.tellg();
    file.seekg(0, ios::beg);
    char* buff = new char[len + 1];
    memset(buff, 0, len + 1);
    file.read(buff, len);
    file.close();
    Json::Reader reader;
    if (reader.parse(buff, buff+len, msg, false))
    {
        return true;
    }
    return false;
}

bool parse_json_file1(const std::string& file_name, Json::Value& msg)
{
    ifstream file(file_name);
    if (!file.is_open())
    {
        std::cout << "Open [" << file_name << "] failed\n";
        return false;
    }

    Json::Reader reader;
    if (reader.parse(file, msg, false))
    {
        return true;
    }
    return false;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage %s [filename]\n", argv[0]);
        exit(-1);
    }

    Json::Value val;
    val["Id"] = Json::Int(100);
    val["Name"] = "Hello world";

    std::cout << val.toStyledString() << std::endl;

    Json::Value contents;

    bool ret = parse_json_file1(argv[1], contents);
    if (ret)
    {
        std::cout <<contents.toStyledString() << std::endl;
    }
    else
    {
        std::cout << "Parses [" << argv[1] << "] failed!\n";
    }
    return 0;
}
