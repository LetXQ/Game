#include "../include/bt/bt_control_node.h"

BT_STATUS BtControlNode::DoRun(BtProxy *proxy, int32_t now_time, int32_t &running_idx)
{
    auto ret = DoControl(proxy, now_time, running_idx);

    return ret;
}

void BtControlNode::FinishControlNode(BtProxy *proxy, BT_STATUS status, int32_t running_idx)
{
    if (IsLastRunning()
            && (m_iRunningIndex != running_idx)
            && (S_SUCCESS == status || S_RUNNING == status))
    {
        BtNode* running_node = m_ChildrenNode[m_iRunningIndex];
        if (running_node)
        {
            running_node->Finish(proxy);
        }
    }
}

BT_STATUS BtSelectorNode::DoControl(BtProxy *proxy, int32_t now_time, int32_t &running_idx)
{
    int32_t tmp_idx = m_iRunningIndex;

    if (!IndexValid(tmp_idx))
    {
        tmp_idx = 0;
    }

    BT_STATUS ret = S_SUCCESS;
    while (IndexValid(tmp_idx))
    {
        ret = m_ChildrenNode[tmp_idx]->Run(proxy, now_time);
        if (S_FAILED == ret)
        {
            ++tmp_idx;
            continue;
        }
        break;
    }
    running_idx = tmp_idx;
    return ret;
}

BT_STATUS BtSequenceNode::DoControl(BtProxy *proxy, int32_t now_time, int32_t &running_idx)
{
    int32_t tmp_idx = m_iRunningIndex;

    if (!IndexValid(tmp_idx))
    {
        tmp_idx = 0;
    }

    BT_STATUS ret = S_SUCCESS;
    while (IndexValid(tmp_idx))
    {
        ret = m_ChildrenNode[tmp_idx]->Run(proxy, now_time);
        if (S_SUCCESS == ret)
        {
            ++tmp_idx;
            continue;
        }
        break;
    }
    running_idx = tmp_idx;
    return ret;
}
