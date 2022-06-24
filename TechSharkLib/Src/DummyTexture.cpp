//------< include >-------------------------------------------------------------
#include "../Inc/DummyTexture.h"
#include <vector>
#include <wrl.h>
#include "../Inc/ResourceManager.h"
#include "../Inc/DebugTools.h"

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
namespace TechSharkLib
{
    void CreateDummyTexture(
        ID3D11Device* device,
        const wchar_t* name,
        ID3D11ShaderResourceView** shaderResourceView,
        DWORD value, UINT textureWidth
    )
    {
        ResourceManager::GetInstance()->CreateShaderResourceView(
            device, name, value, textureWidth,
            shaderResourceView
        );
    }
}