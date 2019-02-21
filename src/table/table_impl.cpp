//TODO:auto generated needed

#include "table/table_test.h"

bool Table_Test::Load(const TableFile &tableFile, int32_t nLineIndex)
{
    tableFile.Read(m_Id, nLineIndex, (int32_t)(ID_ID));
    tableFile.Read(m_Int32Val, nLineIndex, (int32_t)(ID_INT32VAL));
    tableFile.Read(m_Int64Val, nLineIndex, (int32_t)(ID_INT64VAL));
    tableFile.Read(m_FloatVal, nLineIndex, (int32_t)(ID_FLOATVAL));
    tableFile.Read(m_StringVal, nLineIndex, (int32_t)(ID_STRINGVAL));
    return true;
}
