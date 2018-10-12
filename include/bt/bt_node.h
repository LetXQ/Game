#ifndef BT_NODE_H_
#define BT_NODE_H_
#include <vector>
#include <cstdint>
#include "../include/json/json.h"

class BtNode;
using BtNodeVec = std::vector<BtNode*>;

class BtNode
{
public:
    BtNode(BtNode* parent);
    virtual ~BtNode();
    void SetID(int32_t id);
    virtual bool Init(Json::Value& js);
private:
    int32_t m_ID = 0;
    int32_t m_iRunningIndex = 0;
    BtNode* m_pParent = nullptr;
    BtNodeVec m_ChildrenNode;
};

#endif // !BT_NODE_H_
