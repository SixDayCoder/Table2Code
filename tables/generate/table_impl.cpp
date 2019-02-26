
        #include "table/table_item.h"
        TABLE_INSTANCE_IMPL(Table_Item);
        bool Table_Item::Load(const TableFile& tableFile, int32_t nLineIndex)
        {
            tableFile.Read(m_Id, nLineIndex, (int32_t)ID_ID);
			tableFile.Read(m_DataId, nLineIndex, (int32_t)ID_DATAID);
			tableFile.Read(m_Price, nLineIndex, (int32_t)ID_PRICE);
			tableFile.Read(m_StackCount, nLineIndex, (int32_t)ID_STACKCOUNT);
			
            return true;
        }
        const char* Table_Item::TableFilePath() { return "D:/Table2Code/tables/Item.txt"; }
    
        #include "table/table_test.h"
        TABLE_INSTANCE_IMPL(Table_Test);
        bool Table_Test::Load(const TableFile& tableFile, int32_t nLineIndex)
        {
            tableFile.Read(m_Id, nLineIndex, (int32_t)ID_ID);
			tableFile.Read(m_Int32Val, nLineIndex, (int32_t)ID_INT32VAL);
			tableFile.Read(m_Int64Val, nLineIndex, (int32_t)ID_INT64VAL);
			tableFile.Read(m_FloatVal, nLineIndex, (int32_t)ID_FLOATVAL);
			tableFile.Read(m_StringVal, nLineIndex, (int32_t)ID_STRINGVAL);
			
            return true;
        }
        const char* Table_Test::TableFilePath() { return "D:/Table2Code/tables/Test.txt"; }
    