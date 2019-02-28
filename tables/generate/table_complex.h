
        /*Auto Generated.Do Not Modify.*/
    
        #include "table/table_instance.h"
    
        class Table_Complex
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
					ID_RATE = 9,
					ID_TIME = 10,
					ID_SKILLEXID0 = 11,
					ID_SKILLEXID1 = 12,
					ID_PRICE = 13,
					
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
            int32_t m_SkillDamgeType[3];

        public:
            int32_t GetSkillDamgeTypeCount() const { return 3; }

            int32_t GetSkillDamgeTypeByIndex(int32_t nIndex) const
            {
                if(nIndex < 0 || nIndex >= 3) {
                    return -1;
                }
                return m_SkillDamgeType[nIndex];
            }
    
        private:
            int32_t m_SkillDamageVal[3];

        public:
            int32_t GetSkillDamageValCount() const { return 3; }

            int32_t GetSkillDamageValByIndex(int32_t nIndex) const
            {
                if(nIndex < 0 || nIndex >= 3) {
                    return -1;
                }
                return m_SkillDamageVal[nIndex];
            }
    
        private:
            int32_t m_SkillExId[2];

        public:
            int32_t GetSkillExIdCount() const { return 2; }

            int32_t GetSkillExIdByIndex(int32_t nIndex) const
            {
                if(nIndex < 0 || nIndex >= 2) {
                    return -1;
                }
                return m_SkillExId[nIndex];
            }
    
        private:
            float m_Rate;

        public:
            float GetRate() const { return m_Rate; }
    
        private:
            int64_t m_Time;

        public:
            int64_t GetTime() const { return m_Time; }
    
        private:
            int32_t m_Price;

        public:
            int32_t GetPrice() const { return m_Price; }
    
        };
        TABLE_INSTANCE_DECLARE(Table_Complex);
    