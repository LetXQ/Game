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
constexpr int32_t INVALID_IDX = -1;
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
    void Finish(BtProxy* proxy);

    bool IsLastRunning() const;
    BtNode* GetParent();
    BtNode* GetRunningNode();

protected:
    virtual void DoFinish(BtProxy* proxy) {}
    virtual BT_STATUS DoRun(BtProxy* proxy, int32_t now_time, int32_t& exec_idx) = 0;

    bool IndexValid(int32_t idx) const;

private:
    void UpdateRunningIndex(BT_STATUS status, int32_t exec_idx);

protected:
    bool m_bLastRunning = false;
    int32_t m_ID = 0;
    int32_t m_iRunningIndex = INVALID_IDX;
    BtNode* m_pParent = nullptr;
    BtNodeVec m_ChildrenNode;
};

#endif // !BT_NODE_H_
