#include "../include/bt/bt_condition_node.h"

BT_STATUS BtConditionNode::DoRun(BtProxy *proxy, int32_t now_time, int32_t &exec_idx)
{
    return IsValid(proxy, now_time) ? S_SUCCESS : S_FAILED;
}
