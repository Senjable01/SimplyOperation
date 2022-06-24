//------< include >-----------------------------------------------------------------------
#include "../Inc/StringTool.h"

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
namespace TechSharkLib
{
    namespace string
    {
        //------< function >----------------------------------------------------------------------

        std::wstring ReplaceFileName(std::wstring src, const std::wstring& dst)
        {
            size_t result = src.rfind(L"/") + 1;
            src.replace(result, (src.size() - result), dst);
            return src;
        }

    }
}