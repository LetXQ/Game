#ifndef BT_NODE_FACTORY_H
#define BT_NODE_FACTORY_H
#include <string.h>
#include <functional>
#include <map>
#include "../include/common/singleton.h"

class BtNode;
using CreateFunc = std::function<BtNode*(BtNode*)>;
using CreateFuncMap = std::map<std::string, CreateFunc>;
class BtNodeFactory : public Singleton<BtNodeFactory>
{
public:
    void Init();
    BtNode *CreateNode(const std::string& type, BtNode* parent);
private:
    CreateFuncMap m_CreateFuncs;
};
#endif // BT_NODE_FACTORY_H
