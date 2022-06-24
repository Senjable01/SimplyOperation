#ifndef INCLUDED_INC_ENTITY_ID_H
#define INCLUDED_INC_ENTITY_ID_H

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
}

#endif // !INCLUDED_INC_ENTITY_ID_H