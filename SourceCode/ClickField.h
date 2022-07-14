#ifndef INCLUDED_CLICK_FIELD_H
#define INCLUDED_CLICK_FIELD_H

//------< include >-----------------------------------------------------------------------
#include "../TechSharkLib/Inc/Vector.h"

//========================================================================================
// 
//      ClickField
// 
//========================================================================================
class ClickField
{
private:
    TechSharkLib::Float2 pos;
    TechSharkLib::Float2 size;
    TechSharkLib::Float4 debugColor;

public:
    ClickField() : pos{}, size{}, debugColor{} {}

    void Setup(
        float posX, float posY,
        float sizeX, float sizeY,
        float red, float green, float blue, float alpha
    );
    bool IsClicked(int clickedBitFlag);
    void Render();

};

#endif // !INCLUDED_CLICK_FIELD_H