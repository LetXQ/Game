#ifndef BT_CONDITION_NODE_H
#define BT_CONDITION_NODE_H
#include "bt_node.h"

class BtConditionNode : public BtNode
{
public:
    BtConditionNode(BtNode* parent) : BtNode(parent) {}
};

class BtFindTargetNode : public BtConditionNode
{
public:
    BtFindTargetNode(BtNode* parent) : BtConditionNode(parent) {}
};

#endif // BT_CONDITION_NODE_H
