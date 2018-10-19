#ifndef BT_CREATE_NODE_FUNCS_H
#define BT_CREATE_NODE_FUNCS_H
#include "bt_node.h"
#include "bt_control_node.h"
#include "bt_decorator_node.h"
#include "../bt_node/action/bt_attack_node.h"
#include "../bt_node/action/bt_sleep_node.h"
#include "../bt_node/action/bt_walk_node.h"
#include "../bt_node/condition/bt_find_target_node.h"

/*-----------------------Decorator Node --------start-----------------------*/
BtNode* CreateRunTimeNode(BtNode* parent)
{
    return new BtRunTimeDecoratorNode(parent);
}

/*-----------------------Decorator Node --------end-----------------------*/

/*-----------------------Control Node --------start-----------------------*/
BtNode* CreateSelectorNode(BtNode* parent)
{
    return new BtSelectorNode(parent);
}

BtNode* CreateSequenceNode(BtNode* parent)
{
    return new BtSequenceNode(parent);
}
/*-----------------------Control Node --------end-----------------------*/

/*-----------------------Condition Node --------start-----------------------*/
BtNode* CreateFindTargetNode(BtNode* parent)
{
    return new BtFindTargetNode(parent);
}
/*-----------------------Condition Node --------end-----------------------*/

/*-----------------------Action Node --------start-----------------------*/
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
/*-----------------------Action Node --------end-----------------------*/
#define INIT_CREATE_FUNC(name) { \
        m_CreateFuncs.insert(std::make_pair(#name, Create##name##Node)); \
    }

#endif // BT_CREATE_NODE_FUNCS_H
