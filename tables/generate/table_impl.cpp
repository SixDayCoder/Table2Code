
        #include "table/table_array.h"
        TABLE_INSTANCE_IMPL(Table_Array);
        bool Table_Array::Load(const TableFile& tableFile, int32_t nLineIndex)
        {
            tableFile.Read(m_Id, nLineIndex, (int32_t)ID_ID);
			tableFile.Read(m_SkillId, nLineIndex, (int32_t)ID_SKILLID);
			tableFile.Read(m_SkillDamgeType0, nLineIndex, (int32_t)ID_SKILLDAMGETYPE0);
			tableFile.Read(m_SkillDamageVal0, nLineIndex, (int32_t)ID_SKILLDAMAGEVAL0);
			tableFile.Read(m_SkillDamgeType1, nLineIndex, (int32_t)ID_SKILLDAMGETYPE1);
			tableFile.Read(m_SkillDamageVal1, nLineIndex, (int32_t)ID_SKILLDAMAGEVAL1);
			tableFile.Read(m_SkillDamgeType2, nLineIndex, (int32_t)ID_SKILLDAMGETYPE2);
			tableFile.Read(m_SkillDamageVal2, nLineIndex, (int32_t)ID_SKILLDAMAGEVAL2);
			
            return true;
        }
        const char* Table_Array::TableFilePath() { return "D:/Table2Code/tables/Array.txt"; }
    
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
    