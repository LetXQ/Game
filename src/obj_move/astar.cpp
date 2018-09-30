#include <cassert>
#include <map>
#include "../include/obj_move/astar.h"
#include "../include/config/mapconfig.h"

constexpr int32_t MAX_NODE_SIZE = 100;
AStar::AStar()
{
    m_pRouteNodes = new RouteNode[MAX_NODE_SIZE];
    assert(m_pRouteNodes);
    m_OtherNodesVec.clear();
}

AStar::~AStar()
{
    ResetNode();
}

bool AStar::RouteToTargetPos(const Point &cur_pos, const Point &target_pos, PointList &route)
{
    const auto& map_info = MapConfig::Instance().GetMapInfo();

    int32_t cur_x_grid = std::abs(cur_pos.x - map_info.start_pos.x) / 100;
    int32_t cur_y_grid = std::abs(cur_pos.y - map_info.start_pos.y) / 100;
    int32_t end_x_grid = std::abs(target_pos.x - map_info.start_pos.x) / 100;
    int32_t end_y_grid = std::abs(target_pos.y - map_info.start_pos.y) / 100;

    if (CheckSameGrid(cur_x_grid, cur_y_grid, end_x_grid, end_y_grid))
    {
        route.push_back(target.end_pos);
        return true;
    }

    RouteNode* start_node = GetNodeFromCache();
    if (!start_node)
        return false;
    start_node->node_type = T_START;
    start_node->x_grid = cur_x_grid;
    start_node->y_grid = cur_y_grid;

    RouteNodeMap route_node_map;
    route_node_map[GetKeyByGrid(cur_x_grid, cur_y_grid)] = start_node;
    bool b_same_grid = false;
    if (!GetFinalEnd(cur_x_grid, cur_y_grid, end_x_grid, end_y_grid, route_node_map, b_same_grid))
    {
        return false;
    }
    else
    {
        if (b_same_grid)
        {
            route.push_back(target.end_pos);
            return true;
        }
    }


}

bool AStar::CheckSameGrid(int32_t start_x_grid, int32_t start_y_grid, int32_t end_x_grid, int32_t end_y_grid)
{
    return ((start_x_grid == end_x_grid) && (start_y_grid == end_y_grid));
}

bool AStar::GetFinalEnd(int32_t start_x_grid, int32_t start_y_grid, int32_t end_x_grid, int32_t end_y_grid,
                        RouteNodeMap &route_map,
                        bool& same_grid)
{
    const auto& map_cfg = MapConfig::Instance();
    if (!map_cfg.IsBlockGrid(end_x_grid, end_y_grid)
            || !map_cfg.IsBlockGrid(end_x_grid, end_y_grid + 1)
            || !map_cfg.IsBlockGrid(end_x_grid, end_y_grid - 1)
            || !map_cfg.IsBlockGrid(end_x_grid + 1, end_y_grid)
            || !map_cfg.IsBlockGrid(end_x_grid - 1, end_y_grid))
    {
        auto& end_node = GetNodeFromCache();
        if (!end_node)
            return false;
        end_node->node_type = T_END;
        end_node->x_grid = end_x_grid;
        end_node->y_grid = end_y_grid;
        route_map[GetKeyByGrid(end_x_grid, end_y_grid)] = end_node;
    }
    else
    {
        int32_t pre_end_x = end_x_grid, pre_end_y = end_y_grid;
        int32_t flag_x = end_x_grid > start_x_grid ? 1 : -1;
        int32_t flag_y = end_y_grid > start_y_grid ? 1 : -1;

        while (map_cfg.IsBlockGrid(end_x_grid, end_y_grid))
        {
            if (end_x_grid == start_x_grid)
                flag_x = 0;
            if (end_y_grid == start_y_grid)
                flag_y = 0;

            pre_end_x = end_x_grid;
            pre_end_y = end_y_grid;
            end_x_grid += flag_x * flag_x;
            end_y_grid += flag_y * flag_y;
        }

        if (CheckSameGrid(start_x_grid, start_y_grid, end_x_grid, end_y_grid))
        {
            same_grid = true;
            return true;
        }
        auto& end_node = GetNodeFromCache();
        if (!end_node)
            return false;
        node->node_type = T_END;
        node->x_grid = pre_end_x;
        node->y_grid = pre_end_y;
        route_map[GetKeyByGrid(end_x_grid, end_y_grid)] = end_node;
    }
    return true;
}

RouteNode *AStar::GetNodeFromCache()
{
    if (m_iNodeIndex >= MAX_NODE_SIZE)
    {
        auto new_node = new RouteNode();
        assert(new_node);
        m_OtherNodesVec.push_back(new_node);
        return new_node;
    }
    else
    {
        return m_pRouteNodes[m_iNodeIndex++];
    }
}

int64_t AStar::GetKeyByGrid(int32_t x_grid, int32_t y_grid)
{
    return ((static_cast<int64_t>(x_grid) << 32) | y_grid);
}

void AStar::ResetNode()
{
    SAVE_DELETES(m_pRouteNodes);
    for (auto& elem : m_OtherNodesVec)
    {
        SAVE_DELETE(elem)
    }
}
