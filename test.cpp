#include <iostream>
#include <fstream>
#include <string.h>

#include "include/json/json.h"
#include "include/config/mapconfig.h"
#include "include/obj_move/astar.h"

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

    ret = MapConfig::Instance().IsBlockGrid(13, 9);
    std::cout << "Ret: " << ret << std::endl;
    Point start(500, 100), end(1700, 900);
    PointList route_list;
    ret = AStar::Instance().RouteToTargetPos(start, end, route_list);
    std::cout << "Ret: " << (ret ? "Found it" : "Not Found") << ", size: " << route_list.size() << std::endl;
    for (auto& elem : route_list)
    {
        std::cout << "[" << elem.x << ", " << elem.y << "]\n";
    }
    return 0;
}
