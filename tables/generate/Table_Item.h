
        /*Auto Generated.Do Not Modify.*/
    
        #include "table/table_file.h"
    
        class Table_Item
        {
            public:
                enum
                {
                    ID_ID = 0,
					ID_DESC = 1,
					ID_DATAID = 2,
					ID_PRICE = 3,
					ID_STACKCOUNT = 4,
					
                };
            public:
                bool Load(const TableFile& tableFile, int32_t nLineIndex);
    
        private:
            int32_t m_Id;
        public:
            int32_t GetId() const { return m_Id; }
    
        private:
            int32_t m_DataId;
        public:
            int32_t GetDataId() const { return m_DataId; }
    
        private:
            int32_t m_Price;
        public:
            int32_t GetPrice() const { return m_Price; }
    
        private:
            int32_t m_StackCount;
        public:
            int32_t GetStackCount() const { return m_StackCount; }
    
        };
    