#include "../include/bt/bt_decorator_node.h"
#include "../include/common/random.h"
#include "../include/common/common_json_func.h"

BtRunTimeDecoratorNode::BtRunTimeDecoratorNode(BtNode *parent)
    : BtNode(parent)
{

}

BT_STATUS BtRunTimeDecoratorNode::DoRun(BtProxy *proxy, int32_t now_time, int32_t &exec_idx)
{
    if (SD_IDLE == m_Status)
    {
        Start(now_time);
    }

    BT_STATUS ret = Execute(proxy, now_time, exec_idx);

    if (S_SUCCESS == ret || S_FAILED == ret)
    {
        Finish(proxy);
    }
    return ret;
}

bool BtRunTimeDecoratorNode::Init(Json::Value &js)
{
    if (!js["ParamSleepTime"].isNull())
    {
        CommonJsonFunc::ParseIntByKey(js["ParamSleepTime"], "LowerTime", m_Lower);
        CommonJsonFunc::ParseIntByKey(js["ParamSleepTime"], "UpperTime", m_Upper);
    }

    return true;
}

void BtRunTimeDecoratorNode::Start(int32_t now_time)
{
        m_Status = SD_RUNNING;
        m_SustainTime = Random::Instance().UniformIntDistribution(m_Lower, m_Upper);
        m_StartTime = now_time;
}

BT_STATUS BtRunTimeDecoratorNode::Execute(BtProxy *proxy, int32_t now_time, int32_t &exec_idx)
{
    if (m_SustainTime + m_StartTime >= now_time)
    {
        Finish(proxy);
        return S_SUCCESS;
    }
    else
    {
        BT_STATUS ret = m_ChildrenNode[0]->Run(proxy, now_time);
        if (S_RUNNING == ret)
        {
            exec_idx = 0;
        }
        else
        {
            exec_idx =  INVALID_IDX;
        }
        return ret;
    }
}

void BtRunTimeDecoratorNode::DoFinish(BtProxy *proxy)
{
    m_Status = SD_IDLE;
    m_StartTime = 0;
    m_SustainTime = 0;
}
