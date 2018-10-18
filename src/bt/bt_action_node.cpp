#include "../include/bt/bt_action_node.h"
#include "../include/bt/bt_proxy.h"


BT_STATUS BtActionNode::DoRun(BtProxy *proxy, int32_t now_time, int32_t &exec_idx)
{
    BT_STATUS ret = S_SUCCESS;
    do {
        if (AS_IDLE == m_ActionStatus)
        {
            if (proxy && proxy->LastRunning())
            {
                BtNode* node = m_pParent;
                // 找到当前节点和上一帧正在执行中节点最近的共同父节点
                while (node && !node->IsLastRunning())
                {
                    node = node->GetParent();
                }

                if (node)
                {
                    BtNode* running_node = node->GetRunningNode();
                    if (running_node)
                    {
                        running_node->Finish(proxy);
                    }
                }
            }

            if (!StartAction(proxy, now_time))
            {
                ret = S_FAILED;
                break;
            }

            m_ActionStatus = AS_RUNNING;
        }

        ret = DoAction(proxy, now_time);
    } while(0);

    if (S_SUCCESS == ret || S_FAILED == ret)
    {
        Finish(proxy);
    }
    return ret;
}

void BtActionNode::DoFinish(BtProxy *proxy)
{
    DoFinshAction(proxy);
}

void BtActionNode::DoFinshAction(BtProxy *proxy)
{
    FinshAction(proxy);
    m_ActionStatus = AS_IDLE;
}
