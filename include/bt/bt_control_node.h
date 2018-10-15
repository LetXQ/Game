#ifndef BT_CONTROL_NODE_H
#define BT_CONTROL_NODE_H
#include "bt_node.h"

class BtControlNode : public BtNode
{
public:
    BtControlNode(BtNode* parent) : BtNode(parent){}
};

class BtSelectorNode : public BtControlNode
{
public:
    BtSelectorNode(BtNode* parent) : BtSelectorNode(parent){}
};

class BtSequenceNode : public BtControlNode
{
public:
    BtSequenceNode(BtNode* parent) : BtSequenceNode(parent){}
};

#endif // BT_CONTROL_NODE_H