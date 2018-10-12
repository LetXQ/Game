#include "../include/bt/bt_node.h"

BtNode::BtNode(BtNode *parent)
    : m_pParent(parent)
{

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
