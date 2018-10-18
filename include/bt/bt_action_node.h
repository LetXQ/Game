#ifndef BT_ACTION_NODE_H
#define BT_ACTION_NODE_H
#include "bt_node.h"

class BtActionNode : public BtNode
{
public:
    BtActionNode(BtNode* parent) : BtNode(parent) {}
    virtual ~BtActionNode() {}

    BT_STATUS DoRun(BtProxy* proxy, int32_t now_time, int32_t& exec_idx) override;

protected:
    void DoFinish(BtProxy* proxy) override;
    virtual void DoFinshAction(BtProxy* proxy);

    virtual bool StartAction(BtProxy* proxy, int32_t now_time) = 0;
    virtual BT_STATUS DoAction(BtProxy* proxy, int32_t now_time) = 0;
    virtual void FinshAction(BtProxy* proxy) = 0;
protected:
    enum ActionNodeStatus
    {
        AS_IDLE,
        AS_RUNNING,
    };

    ActionNodeStatus m_ActionStatus = AS_IDLE;
};

#endif // BT_ACTION_NODE_H
