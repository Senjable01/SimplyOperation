//------< include >-----------------------------------------------------------------------
#include "ClickField.h"
#include "../TechSharkLib/Inc/TechSharkLib.h"
#include "../TechSharkLib/Inc/Configulation.h"

//========================================================================================
// 
//      ClickField
// 
//========================================================================================

//------------------------------------------------------------------------------
// member function
//------------------------------------------------------------------------------

void ClickField::Setup(
    float posX, float posY,
    float sizeX, float sizeY,
    float red, float green, float blue, float alpha
)
{
    pos         = TechSharkLib::Float2{posX, posY};
    size        = TechSharkLib::Float2{sizeX, sizeY};
    debugColor  = TechSharkLib::Float4{red, green, blue, alpha};
}

bool ClickField::IsClicked(int clickedBitFlag)
{
    const float cursorX = TechSharkLib::MouseCursorX();
    const float cursorY = TechSharkLib::MouseCursorY();
    if (cursorX < pos.x || pos.x + size.x < cursorX)
    {
        return false;
    }
    else if (cursorY < pos.y || pos.y + size.y < cursorY)
    {
        return false;
    }
    else if (TechSharkLib::keyTrigger(0) ^ clickedBitFlag)
    {
        return false;
    }

    return true;

}

void ClickField::Render()
{
    #if USE_IMGUI
    TechSharkLib::DrawRect(
        pos.x, pos.y,
        size.x, size.y,
        debugColor.x, debugColor.y, debugColor.z, debugColor.w
    );

    #endif // USE_IMGUI
}