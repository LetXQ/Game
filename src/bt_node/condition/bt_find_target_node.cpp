#include "../include/bt_node/condition/bt_find_target_node.h"
#include "../include/common/common_json_func.h"
#include "../include/bt/bt_proxy.h"
#include "../include/bt/bt_parameter.h"

bool BtFindTargetNode::Init(Json::Value &js)
{
    if (!js["ParamTarget"].isNull())
    {
        CommonJsonFunc::ParseStringtByKey(js["ParamTarget"], "Name", m_ParamName);
    }
    std::cout << "FindTarget init\n";
    return true;
}

bool BtFindTargetNode::IsValid(BtProxy *proxy, int32_t now_time)
{
    return false;
    if (proxy)
    {
        std::cout << "Find target \n";
        BTParamPtr param = BTParamPtr(new BTParam(100));
        proxy->SetParam(m_ParamName, param);
        return true;
    }
    return false;
}
