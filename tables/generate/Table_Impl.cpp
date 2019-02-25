
    #include "table/table_Item.h"

    bool Table_Item::Load(const TableFile& tableFile, int32_t nLineIndex)
    {
        tableFile.Read(m_Id, nLineIndex, (int32_t)ID_ID);
		tableFile.Read(m_DataId, nLineIndex, (int32_t)ID_DATAID);
		tableFile.Read(m_Price, nLineIndex, (int32_t)ID_PRICE);
		tableFile.Read(m_StackCount, nLineIndex, (int32_t)ID_STACKCOUNT);
		
        return true;
    }
    
    #include "table/table_Test.h"

    bool Table_Test::Load(const TableFile& tableFile, int32_t nLineIndex)
    {
        tableFile.Read(m_Id, nLineIndex, (int32_t)ID_ID);
		tableFile.Read(m_Int32Val, nLineIndex, (int32_t)ID_INT32VAL);
		tableFile.Read(m_Int64Val, nLineIndex, (int32_t)ID_INT64VAL);
		tableFile.Read(m_FloatVal, nLineIndex, (int32_t)ID_FLOATVAL);
		tableFile.Read(m_StringVal, nLineIndex, (int32_t)ID_STRINGVAL);
		
        return true;
    }
    