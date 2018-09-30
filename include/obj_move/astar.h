#ifndef ASTAR_H_
#define ASTAR_H_
#include <vector>
#include <map>
#include "../include/common/world_pos.h"
#include "../include/common/common_def.h"

enum NodeType
{
    T_NONE = 0,
    T_START = 1,
    T_END = 2,
};

struct RouteNode
{
    bool in_close = false;
    bool in_open = false;
    int32_t node_type = 0;
    int32_t g_val = 0;
    int32_t h_val = 0;
    int32_t x_grid = 0;
    int32_t y_grid = 0;
    RouteNode* p_parent = nullptr;
};

using RouteNodeVec = std::vector<RouteNode*>;
using RouteNodeMap = std::map<int32_t, RouteNode*>;
class AStar
{
public:
    AStar();
    ~AStar();
    bool RouteToTargetPos(const Point& cur_pos, const Point& target, PointList& route);

private:
    bool CheckSameGrid(int32_t start_x_grid,
                       int32_t start_y_grid,
                       int32_t end_x_grid,
                       int32_t end_y_grid);

    bool GetFinalEnd(int32_t start_x_grid,
                     int32_t start_y_grid,
                     int32_t end_x_grid,
                     int32_t end_y_grid,
                     RouteNodeMap& route_map,
                     bool& same_grid);

    RouteNode* GetNodeFromCache();
    int64_t GetKeyByGrid(int32_t x_grid, int32_t y_grid);

    void ResetNode();

private:
    int32_t m_iNodeIndex = 0;
    RouteNode* m_pRouteNodes = nullptr;
    RouteNodeVec m_OtherNodesVec;
};

#endif // ASTAR_H_
