#ifndef BT_CONDITION_NODE_H
#define BT_CONDITION_NODE_H
#include "bt_node.h"

class BtConditionNode : public BtNode
{
public:
    BtConditionNode(BtNode* parent) : BtNode(parent) {}
    virtual ~BtConditionNode() {}

    BT_STATUS DoRun(BtProxy *proxy, int32_t now_time, int32_t &exec_idx) override;

protected:
    virtual bool IsValid(BtProxy *proxy, int32_t now_time) = 0;
};

#endif // BT_CONDITION_NODE_H
