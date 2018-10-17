#include "../include/bt/bt_node.h"

BtNode::BtNode(BtNode *parent)
    : m_pParent(parent)
{
    if (!parent)
    {
        m_ChildrenNode.push_back(this);
    }
}

BtNode::~BtNode()
{

}

void BtNode::SetID(int32_t id)
{
    m_ID = id;
}

bool BtNode::Init(Json::Value &js)
{
    return true;
}

BT_STATUS BtNode::Run(BtProxy *proxy, int32_t now_time)
{

}
