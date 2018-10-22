#ifndef BT_PARAMETER_H
#define BT_PARAMETER_H
#include <cstdint>
#include <memory>

enum ValueType
{
    T_INT32,
};

class BTParam
{
private:
    union Value
    {
        int32_t m_iVal = 0;
    };

public:
    BTParam() {}

    BTParam(int32_t iVal) :m_ValueType(T_INT32)
    { m_Value.m_iVal = iVal;}
    bool IsInt32() const { return T_INT32 == m_ValueType; }
    int32_t AsInt32() const { return m_Value.m_iVal;}

private:
    Value m_Value;
    ValueType m_ValueType = T_INT32;
};
using BTParamPtr = std::shared_ptr<BTParam>;
#endif // BT_PARAMETER_H
