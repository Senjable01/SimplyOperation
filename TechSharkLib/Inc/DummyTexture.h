#ifndef INCLUDED_DUMMY_TEXTURE_H
#define INCLUDED_DUMMY_TEXTURE_H

//------< include >-----------------------------------------------------------------------
#include <d3d11.h>

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
namespace TechSharkLib
{
    //UNIT26 Section2
    void CreateDummyTexture(
        ID3D11Device* device,
        const wchar_t* name,
        ID3D11ShaderResourceView** shaderResourceView,
        DWORD value, UINT textureWidth
    );
    inline void CreateDummyColorMap(
        ID3D11Device* device,
        ID3D11ShaderResourceView** shaderResourceView,
        UINT textureWidth
    )
    {
        return CreateDummyTexture(device, L"DummyColorMap", shaderResourceView, 0xffffffff, textureWidth);
    }
    inline void CreateDummyNormalMap(
        ID3D11Device* device,
        ID3D11ShaderResourceView** shaderResourceView,
        UINT textureWidth
    )
    {
        return CreateDummyTexture(device, L"DummyUVMap", shaderResourceView, 0xffff7f7f, textureWidth);
    }
}

#endif // !INCLUDED_DUMMY_TEXTURE_H