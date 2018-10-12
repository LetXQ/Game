#ifndef ASTAR_H_
#define ASTAR_H_
#include <vector>
#include <map>
#include "../include/common/world_pos.h"
#include "../include/common/common_def.h"
#include "../include/common/singleton.h"
enum NodeType
{
    T_NONE = 0,
    T_START = 1,
    T_END = 2,
};

struct RouteNode
{
    void Reset()
    {
        in_close = false;
        in_open = false;
        node_type = 0;
        g_val = 0;
        h_val = 0;
        x_grid = 0;
        y_grid = 0;
        p_parent = nullptr;
    }

    int32_t FVal() const
    {
        return g_val + h_val;
    }

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
class AStar : public Singleton<AStar>
{
public:
    AStar();
    ~AStar();
    /*
     * 获取到达目标点的路径
     * @param cur_pos: 起始点位置
     * @param target: 目标点位置
     * @param route: 路径
    */
    bool RouteToTargetPos(const Point& cur_pos, const Point& target, PointList& route);

private:
    /*
     * 是否在同一个网格
    */
    bool CheckSameGrid(int32_t start_x_grid,
                       int32_t start_y_grid,
                       int32_t end_x_grid,
                       int32_t end_y_grid);

    /*
     * 获取最终的目标点，如果目标点周围都是阻挡物，选取阻挡物外面的点作为最终点
    */
    bool GetFinalEnd(int32_t start_x_grid,
                     int32_t start_y_grid,
                     int32_t end_x_grid,
                     int32_t end_y_grid,
                     RouteNodeMap& route_map,
                     bool& same_grid);

    /*
     * 从缓存中获取一个node
    */
    RouteNode* GetNodeFromCache();

    /*
     * 根据网格坐标生成一个key
    */
    int32_t GetKeyByGrid(int16_t x_grid, int16_t y_grid);

    /*
     * 从open列表中获取F值最小的点
    */
    RouteNode* GetMinFValNode(RouteNodeVec& node_vec);

    /*
     * 添加新的node到open列表中，并从新调整堆
    */
    void AddNewNode(RouteNodeVec& node_vec, RouteNode* new_node);

    /*
     * 遍历当前位置的周围8个点，更新open列表
    */
    void UpdateBySurroundNodes(RouteNode* cur_node, RouteNodeVec& open_node_vec, RouteNodeMap& node_map, int32_t end_x_grid, int32_t end_y_grid);
    void ResetNode();

private:
    int32_t m_iNodeIndex = 0;
    RouteNode* m_pRouteNodes = nullptr;
    RouteNodeVec m_OtherNodesVec;
};

#endif // ASTAR_H_
