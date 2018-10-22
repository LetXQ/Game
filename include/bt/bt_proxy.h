#ifndef BT_PROXY_H
#define BT_PROXY_H
#include <string.h>
#include <iostream>
#include <memory>
#include <map>

class BTParam;
using BTParamPtr = std::shared_ptr<BTParam>;
using BTParamPtrMap = std::map<std::string, BTParamPtr>;

class BtNode;
class BtProxy
{
public:
    bool Init(const std::string& obj_name);
    void OnTimeUpdate(int32_t now_time);
    bool LastRunning() const;
    BtNode* GetRoot();

    void SetParam(const std::string& param_name, BTParamPtr param_value);
    const BTParamPtr GetParam(const std::string& param_name) const;
private:
    bool m_LastRunning = false;
    BtNode* m_pRoot = nullptr;
    BTParamPtrMap m_ParamMap;
};

#endif // BT_PROXY_H
