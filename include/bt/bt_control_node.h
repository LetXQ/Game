#ifndef BT_CONTROL_NODE_H
#define BT_CONTROL_NODE_H
#include "bt_node.h"

class BtControlNode : public BtNode
{
public:
    BtControlNode(BtNode* parent) : BtNode(parent){}
    virtual ~BtControlNode() {}

    BT_STATUS DoRun(BtProxy* proxy, int32_t now_time, int32_t& exec_idx) override;

protected:
    virtual BT_STATUS DoControl(BtProxy* proxy, int32_t now_time, int32_t& exec_idx) = 0;

private:
    /*
     * 如果该控制节点在上一帧是运行状态，在本帧运行时子节点返回非运行状态，
     * 需结束上一帧执行中的子节点
     */
    void FinishControlNode(BtProxy* proxy,  BT_STATUS status, int32_t exec_idx);
};

/*
 * 非优先级选择节点
 * 如果上一帧有运行的子节点，则从运行节点开始执行
 * 如果当前子节点执行失败，则继续执行下一个子节点
 * 否则返回执行状态，不在继续执行下一个子节点
 */
class BtSelectorNode final: public BtControlNode
{
public:
    BtSelectorNode(BtNode* parent) : BtControlNode(parent){}

private:
    BT_STATUS DoControl(BtProxy* proxy, int32_t now_time, int32_t& exec_idx) override;
};

/*
 * 顺序选择节点
 * 如果上一帧有运行的子节点，则从运行节点开始执行
 * 如果当前子节点执行成功，则继续执行下一个子节点
 * 否则返回执行状态，不在继续执行下一个子节点
 */
class BtSequenceNode final: public BtControlNode
{
public:
    BtSequenceNode(BtNode* parent) : BtControlNode(parent){}

private:
    BT_STATUS DoControl(BtProxy* proxy, int32_t now_time, int32_t& exec_idx) override;
};

#endif // BT_CONTROL_NODE_H
