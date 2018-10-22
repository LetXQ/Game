#include "../include/bt/bt_proxy.h"
#include "../include/bt/bt_node.h"
#include "../include/bt/bt_parameter.h"
#include "../include/config/bt_parse.h"

bool BtProxy::Init(const std::string &obj_name)
{
    m_pRoot = BtParse::Instance().GetBtRootNode(obj_name);

    if (!m_pRoot)
        return false;
    return true;
}

void BtProxy::OnTimeUpdate(int32_t now_time)
{
    if (m_pRoot)
    {
        auto ret = m_pRoot->Run(this, now_time);
        m_LastRunning = (S_RUNNING == ret) ? true : false;
    }
}

bool BtProxy::LastRunning() const
{
    return m_LastRunning;
}

BtNode *BtProxy::GetRoot()
{
    return m_pRoot;
}

void BtProxy::SetParam(const std::string &param_name, BTParamPtr param_value)
{
    m_ParamMap[param_name] = param_value;
}

static BTParamPtr empty_ptr = nullptr;
const BTParamPtr BtProxy::GetParam(const std::string &param_name) const
{
    auto iter = m_ParamMap.find(param_name);
    if (iter != m_ParamMap.end())
    {
        return iter->second;
    }
    return empty_ptr;
}

