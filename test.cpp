#include <iostream>
#include <fstream>
#include <string.h>

#include "include/json/json.h"
#include "include/config/mapconfig.h"

using namespace std;


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage %s [filename]\n", argv[0]);
        exit(-1);
    }

    bool ret = MapConfig::Instance().ParseConfigFile(argv[1]);
    if (ret)
    {
        MapConfig::Instance().PrintConfigs();
        std::cout << "ParseConfigFile [" << argv[1] << "] success!\n";
    }
    else
    {
        std::cout << "ParseConfigFile [" << argv[1] << "] failed!\n";
    }
    return 0;
}
