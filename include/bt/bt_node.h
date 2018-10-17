#ifndef BT_NODE_H_
#define BT_NODE_H_
#include <vector>
#include <cstdint>
#include "../include/json/json.h"

enum BT_STATUS
{
    S_SUCCESS,
    S_FAILED,
    S_RUNNING
};

class BtNode;
using BtNodeVec = std::vector<BtNode*>;
class BtProxy;
class BtNode
{
public:
    BtNode(BtNode* parent);

    virtual ~BtNode();
    virtual bool Init(Json::Value& js);

    BT_STATUS Run(BtProxy* proxy, int32_t now_time);

    void SetID(int32_t id);

protected:
    virtual BT_STATUS DoRun(BtProxy* proxy, int32_t now_time) = 0;
private:
    int32_t m_ID = 0;
    int32_t m_iRunningIndex = 0;
    BtNode* m_pParent = nullptr;
    BtNodeVec m_ChildrenNode;
};

#endif // !BT_NODE_H_
