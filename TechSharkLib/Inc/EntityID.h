#ifndef INCLUDED_INC_ENTITY_ID_H
#define INCLUDED_INC_ENTITY_ID_H

//------< include >-----------------------------------------------------------------------
#include <ostream>

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
#define TSL_CREATE_ENTITY_ID( TYPENAME, ID_TYPE, INIT_VALUE ) \
class TYPENAME \
{\
    private:\
        ID_TYPE id;\
    public:\
        TYPENAME() : id{INIT_VALUE} {}\
        explicit TYPENAME(ID_TYPE id) : id{id} {}\
        bool operator<(const TYPENAME& src)\
        {\
            return (id < src.id);\
        }\
        friend bool operator<(const TYPENAME& src, const TYPENAME& dst)\
        {\
            return (src.id < dst.id);\
        }\
        bool operator==(ID_TYPE idNo) const { return id == idNo; }\
        bool operator!=(ID_TYPE idNo) const { return id == idNo; }\
        friend std::ostream& operator<<(std::ostream& os, const TYPENAME& src) { os << src.id; return os; }\
        friend std::wostream& operator<<(std::wostream& os, const TYPENAME& src) { os << src.id; return os; }\
}

#endif // !INCLUDED_INC_ENTITY_ID_H