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

bool BtNode::IndexValid(int32_t idx) const
{
    return ((idx >= 0) && (idx < (int32_t)m_ChildrenNode.size()) );
}

bool BtNode::IsLastRunning() const
{
    return m_bLastRunning;
}

BtNode *BtNode::GetParent()
{
    return m_pParent;
}

BtNode *BtNode::GetRunningNode()
{
    if (IndexValid(m_iRunningIndex))
    {
        return m_ChildrenNode[m_iRunningIndex];
    }
    return nullptr;
}

bool BtNode::Init(Json::Value &js)
{
    return true;
}

BT_STATUS BtNode::Run(BtProxy *proxy, int32_t now_time)
{
    int32_t exec_idx = m_iRunningIndex;
    auto ret = DoRun(proxy, now_time, exec_idx);
    UpdateRunningIndex(ret, exec_idx);
    return ret;
}

void BtNode::UpdateRunningIndex(BT_STATUS status, int32_t exec_idx)
{
    if (S_RUNNING == status)
    {
        m_iRunningIndex = exec_idx;
    }
    else
    {
        m_iRunningIndex = INVALID_IDX;
    }
}

void BtNode::Finish(BtProxy *proxy)
{
    if (IndexValid(m_iRunningIndex))
    {
        m_ChildrenNode[m_iRunningIndex]->Finish(proxy);
        m_iRunningIndex = INVALID_IDX;
    }

    m_bLastRunning = false;
    DoFinish(proxy);
}
