#ifndef BT_CREATE_NODE_FUNCS_H
#define BT_CREATE_NODE_FUNCS_H

#include "../include/bt/bt_action_node.h"
#include "../include/bt/bt_condition_node.h"
#include "../include/bt/bt_control_node.h"

BtNode* CreateSelectorNode(BtNode* parent)
{
    return new BtSelectorNode(parent);
}

BtNode* CreateSequenceNode(BtNode* parent)
{
    return new BtSequenceNode(parent);
}

BtNode* CreateFindTargetNode(BtNode* parent)
{
    return new BtFindTargetNode(parent);
}

BtNode* CreateSleepNode(BtNode* parent)
{
    return new BtSleepNode(parent);
}

BtNode* CreateWalkNode(BtNode* parent)
{
    return new BtWalkNode(parent);
}

BtNode* CreateAttackNode(BtNode* parent)
{
    return new BtAttackNode(parent);
}

#define INIT_CREATE_FUNC(name) { \
        m_CreateFuncs.insert(std::make_pair(#name, Create##name##Node)); \
    }

#endif // BT_CREATE_NODE_FUNCS_H