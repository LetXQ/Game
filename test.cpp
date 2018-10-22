#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>

#include "include/json/json.h"
#include "include/config/mapconfig.h"
#include "include/config/bt_parse.h"
#include "include/obj/astar.h"
#include "include/bt/bt_proxy.h"
#include "include/bt/bt_node.h"

using namespace std;

void StartBT(const std::string& obj_name)
{
    bool ret = BtParse::Instance().ParseConfigFile(obj_name);
    if (ret)
    {
        BtProxy bt_proxy;
        ret = bt_proxy.Init("Panda");

        std::cout <<"Ret: " << ret << "Root: " << bt_proxy.GetRoot() << std::endl;
        if (bt_proxy.GetRoot())
        {
            int32_t now_time = 100;
            while (true)
            {
                bt_proxy.OnTimeUpdate(now_time);
                now_time += 3;
                sleep(1);
            }
        }
    }
}

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

    StartBT(argv[2]);
    return 0;
}
