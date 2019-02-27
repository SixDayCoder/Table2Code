
        /*Auto Generated.Do Not Modify.*/
        #include "table/table_manager.h"
    
        #include "table/table_array.h"
		#include "table/table_item.h"
		#include "table/table_test.h"
		
    
        std::map<std::string, TableInstancePtr> TableManager::gTableMap;
    
        void TableManager::Load()
        {
            
            TABLE_INSTANCE(Table_Array).Load();
            gTableMap.insert(std::make_pair(Table_Array::TableFilePath(), &TABLE_INSTANCE(Table_Array)));
    
            TABLE_INSTANCE(Table_Item).Load();
            gTableMap.insert(std::make_pair(Table_Item::TableFilePath(), &TABLE_INSTANCE(Table_Item)));
    
            TABLE_INSTANCE(Table_Test).Load();
            gTableMap.insert(std::make_pair(Table_Test::TableFilePath(), &TABLE_INSTANCE(Table_Test)));
    
        }
    