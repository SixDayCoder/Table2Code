#include "table/table_file.h"


//TODO:auto generated needed

class Table_Test
{
public:
    enum
    {
        ID_INVALID = -1,
        ID_ID = 0,
        ID_DESC = 1,
        ID_INT32VAL = 2,
        ID_INT64VAL = 3,
        ID_FLOATVAL = 4,
        ID_STRINGVAL = 5,
    };

public:

    bool Load(const TableFile& tableFile, int32_t nLineIndex);

private:

    int32_t m_Id;

public:

    int32_t GetId() const { return m_Id; }

private:

    int32_t m_Int32Val;

public:

    int32_t GetInt32Val() const { return m_Int32Val; }

private:

    int64_t m_Int64Val;

public:

    int64_t GetInt64Val() const { return m_Int64Val; }

private:

    float m_FloatVal;

public:

    float GetFloatVal() const { return m_FloatVal; }

private:

    std::string m_StringVal;

public:

    const char* GetStringVal() const { return m_StringVal.c_str(); }
};