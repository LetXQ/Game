#ifndef COMMON_JSON_FUNC_H
#define COMMON_JSON_FUNC_H
#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include "../json/json.h"

using namespace std;

class CommonJsonFunc
{
public:
    /*
     * 解析json文件
    */
    static bool ParseJsonFile(const std::string& file_name, Json::Value& msg)
    {
        ifstream file(file_name);
        if (!file.is_open())
        {
            std::cout << "Open [" << file_name << "] failed\n";
            return false;
        }
        std::cout << "Open [" << file_name << "] success\n";

        Json::Reader reader;
        if (reader.parse(file, msg, false))
        {
            return true;
        }
        return false;
    }

    static bool parse_json_file(const std::string& file_name, Json::Value& msg)
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
        bool ret = reader.parse(buff, buff+len, msg, false);
        delete [] buff;
        buff = nullptr;
        if (ret)
        {
            return true;
        }
        return false;
    }

    static void ParseIntByKey(const Json::Value& msg, const char* key,  int& val, int rate = 1)
    {
        if (!msg[key].isNull())
        {
            val = msg[key].asInt() * rate;
        }
    }

    static void ParseDoubleByKey(const Json::Value& msg, const char* key,  double& val, int rate = 1)
    {
        if (!msg[key].isNull())
        {
            val = msg[key].asDouble() * rate;
        }
    }

    static void ParseDoubleVectorByKey(const Json::Value& msg, const char* key,  std::vector<double>& val, int rate = 1)
    {
        if (!msg[key].isNull())
        {
            for (auto elem : msg[key])
            {
                val.push_back(elem.asDouble() * rate);
            }
        }
    }

    static void ParseStringtByKey(const Json::Value& msg, const char* key,  std::string& val)
    {
        if (!msg[key].isNull())
        {
            val = msg[key].asString();
        }
    }

    static void ParseStringVectorByKey(const Json::Value& msg, const char* key, std::vector<std::string>& str_vec)
    {
        if (!msg[key].isNull())
        {
            for (auto& elem : msg[key])
            {
                str_vec.push_back(elem.asString());
            }
        }
    }
};

#endif // COMMON_JSON_FUNC_H
