#include "../include/bt/bt_node_factory.h"
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

#define INIT_CREATE_FUNC(name) { \
        m_CreateFuncs.insert(std::make_pair(#name, Create##name##Node)); \
    }

void BtNodeFactory::Init()
{
    INIT_CREATE_FUNC(Selector);
    INIT_CREATE_FUNC(Sequence);
}

BtNode *BtNodeFactory::CreateNode(const std::string &type, BtNode* parent)
{
    auto iter = m_CreateFuncs.find(type);
    if (iter != m_CreateFuncs.end())
    {
        auto new_node = iter->second(parent);
        return new_node;
    }
    return nullptr;
}
