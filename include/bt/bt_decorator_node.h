#ifndef BT_DECORATOR_NODE_H
#define BT_DECORATOR_NODE_H
#include "bt_node.h"

/*
 * 装饰节点的子节点只有一个
 * 子节点持续运行时长
 */
class BtRunTimeDecoratorNode final: public BtNode
{
public:
    BtRunTimeDecoratorNode(BtNode* parent);
    BT_STATUS DoRun(BtProxy* proxy, int32_t now_time, int32_t& exec_idx) override;
    bool Init(Json::Value& js) override;

private:
    void Start(int32_t now_time);
    BT_STATUS Execute(BtProxy* proxy, int32_t now_time, int32_t& exec_idx);
    void DoFinish(BtProxy* proxy) override;
private:
    enum {
        SD_IDLE = 0,
        SD_RUNNING,
    };
    int32_t m_Status = 0;
    int32_t m_Lower = 0;
    int32_t m_Upper = 0;
    int32_t m_SustainTime = 0;
    int32_t m_StartTime = 0;
};

#endif // BT_DECORATOR_NODE_H
