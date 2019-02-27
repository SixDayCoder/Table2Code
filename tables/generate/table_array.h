
        /*Auto Generated.Do Not Modify.*/
    
        #include "table/table_instance.h"
    
        class Table_Array
        {
            public:
                enum
                {
                    ID_ID = 0,
					ID_DESC = 1,
					ID_SKILLID = 2,
					ID_SKILLDAMGETYPE0 = 3,
					ID_SKILLDAMAGEVAL0 = 4,
					ID_SKILLDAMGETYPE1 = 5,
					ID_SKILLDAMAGEVAL1 = 6,
					ID_SKILLDAMGETYPE2 = 7,
					ID_SKILLDAMAGEVAL2 = 8,
					
                };
            public:
                bool Load(const TableFile& tableFile, int32_t nLineIndex);

            public:
                static const char* TableFilePath();
    
        private:
            int32_t m_Id;
        public:
            int32_t GetId() const { return m_Id; }
    
        private:
            int32_t m_SkillId;
        public:
            int32_t GetSkillId() const { return m_SkillId; }
    
        private:
            ${Type} m_${VariableName}[${Count}];
        public:
            int32_t Get${VariableName}Count() const { return ${Count}; }
        public:
            ${Type} Get${VariableName}ByIndex(int32_t nIndex) const
            {
                if(nIndex ${LeftBrackets} 0 || nIndex ${RightBrackets}= ${Count}) {
                    m_${VariableName}[nIndex];
                }
                return m_${DefaultVal};
            }
    
        private:
            ${Type} m_${VariableName}[${Count}];
        public:
            int32_t Get${VariableName}Count() const { return ${Count}; }
        public:
            ${Type} Get${VariableName}ByIndex(int32_t nIndex) const
            {
                if(nIndex ${LeftBrackets} 0 || nIndex ${RightBrackets}= ${Count}) {
                    m_${VariableName}[nIndex];
                }
                return m_${DefaultVal};
            }
    
        private:
            ${Type} m_${VariableName}[${Count}];
        public:
            int32_t Get${VariableName}Count() const { return ${Count}; }
        public:
            ${Type} Get${VariableName}ByIndex(int32_t nIndex) const
            {
                if(nIndex ${LeftBrackets} 0 || nIndex ${RightBrackets}= ${Count}) {
                    m_${VariableName}[nIndex];
                }
                return m_${DefaultVal};
            }
    
        private:
            ${Type} m_${VariableName}[${Count}];
        public:
            int32_t Get${VariableName}Count() const { return ${Count}; }
        public:
            ${Type} Get${VariableName}ByIndex(int32_t nIndex) const
            {
                if(nIndex ${LeftBrackets} 0 || nIndex ${RightBrackets}= ${Count}) {
                    m_${VariableName}[nIndex];
                }
                return m_${DefaultVal};
            }
    
        private:
            ${Type} m_${VariableName}[${Count}];
        public:
            int32_t Get${VariableName}Count() const { return ${Count}; }
        public:
            ${Type} Get${VariableName}ByIndex(int32_t nIndex) const
            {
                if(nIndex ${LeftBrackets} 0 || nIndex ${RightBrackets}= ${Count}) {
                    m_${VariableName}[nIndex];
                }
                return m_${DefaultVal};
            }
    
        private:
            ${Type} m_${VariableName}[${Count}];
        public:
            int32_t Get${VariableName}Count() const { return ${Count}; }
        public:
            ${Type} Get${VariableName}ByIndex(int32_t nIndex) const
            {
                if(nIndex ${LeftBrackets} 0 || nIndex ${RightBrackets}= ${Count}) {
                    m_${VariableName}[nIndex];
                }
                return m_${DefaultVal};
            }
    
        };
        TABLE_INSTANCE_DECLARE(Table_Array);
    