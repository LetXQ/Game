#include "../include/bt/bt_node_factory.h"
#include "../include/bt/bt_create_node_funcs.h"

void BtNodeFactory::Init()
{
    INIT_CREATE_FUNC(Selector);
    INIT_CREATE_FUNC(Sequence);
    INIT_CREATE_FUNC(FindTarget);
    INIT_CREATE_FUNC(Attack);
    INIT_CREATE_FUNC(Walk);
    INIT_CREATE_FUNC(Sleep);
}

BtNode *BtNodeFactory::CreateNode(const std::string &type, BtNode* parent)
{
    auto iter = m_CreateFuncs.find(type);
    if (iter != m_CreateFuncs.end())
    {
        BtNode * new_node = iter->second(parent);
        if (new_node)
            return new_node;
        std::cout << "Found new failed\n";
    }
    std::cout << "Not found size: " << m_CreateFuncs.size() << std::endl;
    return nullptr;
}
