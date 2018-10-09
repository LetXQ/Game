#include <cassert>
#include <map>
#include <algorithm>
#include <iostream>
#include "../include/obj_move/astar.h"
#include "../include/config/mapconfig.h"

constexpr int32_t MAX_NODE_SIZE = 100;

namespace  AStarHeuristic
{
constexpr int32_t STRAIGHT_COST = 10;
constexpr int32_t DIAGONAL_COST = 14;

int32_t CalcG(const RouteNode* temp, const RouteNode* last)
{
     int32_t extG = ((temp->x_grid != last->x_grid) && (temp->y_grid != last->y_grid))? DIAGONAL_COST : STRAIGHT_COST;

    return last->g_val + extG;
}

//用简单的欧几里得距离计算H
int32_t CalcH(const RouteNode* temp, const RouteNode* end)
{
    int dx =end->x_grid - temp->x_grid;
    int dy = end->y_grid - temp->y_grid;

    return  (int32_t)(std::sqrt(dx * dx + dy * dy) * STRAIGHT_COST);
}

int32_t CalcH(const RouteNode* temp, int32_t end_x_grid, int32_t end_y_grid)
{
    int dx = end_x_grid - temp->x_grid;
    int dy = end_y_grid - temp->y_grid;

    return (int32_t)(std::sqrt(dx * dx + dy * dy) * STRAIGHT_COST);
}
}

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
    std::cout << "cur: "<< cur_pos.x << ", " << cur_pos.y << ", target: " << target_pos.x << ", " << target_pos.y << std::endl;
    const auto& map_info = MapConfig::Instance().GetMapInfo();

    int32_t cur_x_grid = std::abs(cur_pos.x - map_info.start_pos.x) / 100;
    int32_t cur_y_grid = std::abs(cur_pos.y - map_info.start_pos.y) / 100;
    int32_t end_x_grid = std::abs(target_pos.x - map_info.start_pos.x) / 100;
    int32_t end_y_grid = std::abs(target_pos.y - map_info.start_pos.y) / 100;

    if (CheckSameGrid(cur_x_grid, cur_y_grid, end_x_grid, end_y_grid))
    {
        route.push_back(target_pos);
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
    // 目标点是单纯一个点，没有长宽
    // 待实现：如果目标有长宽，可以将周围点都作为终点，放到 route_node_map里
    if (!GetFinalEnd(cur_x_grid, cur_y_grid, end_x_grid, end_y_grid, route_node_map, b_same_grid))
    {
        return false;
    }
    else
    {
        if (b_same_grid)
        {
            route.push_back(cur_pos);
            return true;
        }
    }

    RouteNodeVec open_vec;
    start_node->in_open = true;
    AddNewNode(open_vec, start_node);
    bool b_found = false;
    RouteNode* p_end_node = nullptr;
    while (!open_vec.empty())
    {
        RouteNode* next_node = GetMinFValNode(open_vec);
        if (!next_node)
            break;
        std::cout << "GetMinFValNode x: " << next_node->x_grid << ", y: " << next_node->y_grid << std::endl;
        next_node->in_open = false;
        next_node->in_close = true;

        if (T_END == next_node->node_type)
        {
            p_end_node = next_node;
            b_found = true;
            break;
        }
        UpdateBySurroundNodes(next_node, open_vec, route_node_map, end_x_grid, end_y_grid);
    }

    if (b_found)
    {
        while (p_end_node)
        {
            Point tmp(p_end_node->x_grid*100, p_end_node->y_grid*100);
            route.push_front(tmp);
            p_end_node = p_end_node->p_parent;
        }
    }

    ResetNode();
    return b_found;
}

bool AStar::CheckSameGrid(int32_t start_x_grid, int32_t start_y_grid, int32_t end_x_grid, int32_t end_y_grid)
{
    return ((start_x_grid == end_x_grid) && (start_y_grid == end_y_grid));
}

bool AStar::GetFinalEnd(int32_t start_x_grid, int32_t start_y_grid, int32_t end_x_grid, int32_t end_y_grid,
                        RouteNodeMap &route_map,
                        bool& same_grid)
{
   std::cout << "start_x_grid: "<< start_x_grid << ", " << start_y_grid << ", target: " <<end_x_grid<< ", " << end_y_grid << std::endl;
    auto& map_cfg = MapConfig::Instance();
    if (!map_cfg.IsBlockGrid(end_x_grid, end_y_grid)
            || !map_cfg.IsBlockGrid(end_x_grid, end_y_grid + 1)
            || !map_cfg.IsBlockGrid(end_x_grid, end_y_grid - 1)
            || !map_cfg.IsBlockGrid(end_x_grid + 1, end_y_grid)
            || !map_cfg.IsBlockGrid(end_x_grid - 1, end_y_grid))
    {
        auto end_node = GetNodeFromCache();
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
        int32_t flag_x = end_x_grid > start_x_grid ? -1 : 1;
        int32_t flag_y = end_y_grid > start_y_grid ? -1 : 1;

        while (map_cfg.IsBlockGrid(end_x_grid, end_y_grid))
        {
            std::cout << "---------------flag_x: " << flag_x << ", flagy" << flag_y << "\n";
            if (end_x_grid == start_x_grid)
                flag_x = 0;
            if (end_y_grid == start_y_grid)
                flag_y = 0;

            pre_end_x = end_x_grid;
            pre_end_y = end_y_grid;
            end_x_grid += flag_x * 1;
            end_y_grid += flag_y * 1;
        }
        std::cout << end_x_grid << ", " << end_y_grid << std::endl;;
        if (CheckSameGrid(start_x_grid, start_y_grid, end_x_grid, end_y_grid))
        {
            same_grid = true;
            return true;
        }
        auto end_node = GetNodeFromCache();
        if (!end_node)
            return false;
        end_node->node_type = T_END;
        end_node->x_grid = pre_end_x;
        end_node->y_grid = pre_end_y;
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
        auto res = & m_pRouteNodes[m_iNodeIndex++];
        res->Reset();
        return res;
    }
}

int32_t AStar::GetKeyByGrid(int16_t x_grid, int16_t y_grid)
{
    return ((x_grid << 16) | y_grid);
}

RouteNode *AStar::GetMinFValNode(RouteNodeVec &node_vec)
{
    if (node_vec.empty())
        return nullptr;
    for (auto elem : node_vec)
    {
        //std::cout << "["<<elem->x_grid << ", " << elem->y_grid << "] : "<<elem->FVal() << std::endl;
    }
    RouteNode* res = node_vec[0];
    std::swap(node_vec[0], node_vec[node_vec.size() - 1]);
    node_vec.erase(node_vec.begin() + node_vec.size() - 1);
    int32_t len = (int32_t)node_vec.size();

    // 将数组中的首位元素互换位置(小顶堆第一个元素是最小)后再重新调整堆结构
    if (len > 1)
    {
        int left = 0, right = 0, pre = 0;
        for (int32_t i = 0; i < (len + 1) / 2; )
        {
            pre = i;
            left = 2 * i + 1;
            right = left + 1;

            if (left < len && node_vec[i]->FVal() >= node_vec[left]->FVal())
                i = left;
            if (right < len && node_vec[i]->FVal() >= node_vec[right]->FVal())
                i = right;

            if (i == pre)
                break;
            std::swap(node_vec[i], node_vec[pre]);
        }
    }
    return res;
}

void AStar::AddNewNode(RouteNodeVec &node_vec, RouteNode *new_node)
{
    //将新元素插入到有序堆的最后一位，再调整堆
    node_vec.push_back(new_node);
    if (node_vec.size() > 1)
    {
        int end_idx = node_vec.size() - 1;
        int idx = (end_idx - 1) / 2;
        while (node_vec[idx]->FVal() >= node_vec[end_idx]->FVal()) {
            std::swap(node_vec[idx], node_vec[end_idx]);
            end_idx = idx;
            idx = end_idx/2;
            if (end_idx == idx)
                break;
        }
    }
}

void AStar::UpdateBySurroundNodes(RouteNode *cur_node, RouteNodeVec &open_node_vec, RouteNodeMap &node_map, int32_t end_x_grid, int32_t end_y_grid)
{
    for (int x = cur_node->x_grid - 1; x <= cur_node->x_grid + 1; ++x)
    {
        for (int y = cur_node->y_grid - 1; y <= cur_node->y_grid + 1; ++y)
        {
            if (!MapConfig::Instance().IsGridValid(x, y) || ((x == cur_node->x_grid) && (y == cur_node->y_grid)))
            {
                continue;
            }

            int32_t key = GetKeyByGrid(x, y);
            if (MapConfig::Instance().IsBlockGrid(x, y)
                    && (node_map.count(key) == 0 || node_map[key]->node_type != T_END) )
            {
                continue;
            }

            if (node_map.count(key) == 0)
            {
                RouteNode* new_node = GetNodeFromCache();
                new_node->x_grid = x;
                new_node->y_grid = y;

                node_map[key] = new_node;
            }

            RouteNode* surround_node = node_map[key];
            if (surround_node->in_close)
                continue;

            if (surround_node->in_open)
            {
//                std::cout << "in_open x: " << x << ", y: " << y << std::endl;
                int32_t temp_g = AStarHeuristic::CalcG(surround_node, cur_node);
                if (temp_g < surround_node->g_val)
                {
                    surround_node->g_val = temp_g;
                    surround_node->p_parent = cur_node;
                }
            }
            else
            {
//                std::cout << "AddNewNode x: " << x << ", y: " << y << std::endl;
                surround_node->in_open = true;
                surround_node->p_parent = cur_node;
                surround_node->g_val = AStarHeuristic::CalcG(surround_node, cur_node);
                surround_node->h_val = AStarHeuristic::CalcH(surround_node, end_x_grid, end_y_grid);
                AddNewNode(open_node_vec, surround_node);
            }
        }
    }
}

void AStar::ResetNode()
{
    SAVE_DELETES(m_pRouteNodes);
    for (auto& elem : m_OtherNodesVec)
    {
        SAVE_DELETE(elem)
    }
}
