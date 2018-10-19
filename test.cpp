#include <iostream>
#include <fstream>
#include <string.h>

#include "include/json/json.h"
#include "include/config/mapconfig.h"
#include "include/config/bt_parse.h"
#include "include/obj/astar.h"
#include "include/bt/bt_proxy.h"

using namespace std;


int main(int argc, char* argv[])
{
    if (argc != 3)
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

    Point start(500, 100), end(1700, 900);
    PointList route_list;
    ret = AStar::Instance().RouteToTargetPos(start, end, route_list);
    std::cout << "Ret: " << (ret ? "Found it" : "Not Found") << ", size: " << route_list.size() << std::endl;
    for (auto& elem : route_list)
    {
        std::cout << "[" << elem.x << ", " << elem.y << "]\n";
    }

    ret = BtParse::Instance().ParseConfigFile(argv[2]);
    if (ret)
    {
        BtProxy bt_proxy;
        ret = bt_proxy.Init("Panda");

        std::cout <<"Ret: " << ret << "Root: " << bt_proxy.GetRoot() << std::endl;
    }
    return 0;
}
