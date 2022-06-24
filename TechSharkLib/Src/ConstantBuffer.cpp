//------< include >-----------------------------------------------------------------------
#include "../Inc/ConstantBuffer.h"

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
namespace TechSharkLib
{
    //------< functions >---------------------------------------------------------------------

    void SetObjectConstantBuffer(
        ID3D11DeviceContext* immediateContext,
        ID3D11Buffer** objConstantBuffer,
        const DirectX::XMFLOAT4X4& world,
        const DirectX::XMFLOAT4& materialColor
    )
    {
        ObjectConstants objConstantData = {world, materialColor};
        immediateContext->UpdateSubresource(*objConstantBuffer, 0, 0, &objConstantData, 0, 0);
        immediateContext->VSSetConstantBuffers(REGISTER_OBJECT_CONSTANT, 1, objConstantBuffer);
    }
    void SetObjectConstantBuffer(
        ID3D11DeviceContext* immediateContext,
        ID3D11Buffer** objConstantBuffer,
        const DirectX::XMFLOAT4X4& world,
        const DirectX::XMFLOAT4& materialColor, const DirectX::XMFLOAT4& colorFactor
    )
    {
        ObjectConstants objConstantData = {world, materialColor};
        DirectX::XMStoreFloat4(&objConstantData.materialColor, DirectX::XMVectorMultiply(DirectX::XMLoadFloat4(&objConstantData.materialColor), DirectX::XMLoadFloat4(&colorFactor)));
        immediateContext->UpdateSubresource(*objConstantBuffer, 0, 0, &objConstantData, 0, 0);
        immediateContext->VSSetConstantBuffers(REGISTER_OBJECT_CONSTANT, 1, objConstantBuffer);
    }

    void SetSceneConstantBuffer(
        ID3D11DeviceContext* immediateContext,
        ID3D11Buffer** sceneConstantBuffer,
        const DirectX::XMFLOAT4X4& viewProjection,
        const DirectX::XMFLOAT4& lightDirection
    )
    {
        SceneConstants sceneConstantData = {viewProjection, lightDirection};
        immediateContext->UpdateSubresource(*sceneConstantBuffer, 0, nullptr, &sceneConstantData, 0, 0);
        immediateContext->VSSetConstantBuffers(REGISTER_SCENE_CONSTANT, 1, sceneConstantBuffer);
        immediateContext->PSSetConstantBuffers(REGISTER_SCENE_CONSTANT, 1, sceneConstantBuffer);
    }
    void SetSpecularSceneConstantBuffer(
        ID3D11DeviceContext* immediateContext,
        ID3D11Buffer** sceneConstantBuffer,
        const DirectX::XMFLOAT4X4& viewProjection,
        const DirectX::XMFLOAT4& lightDirection,
        const DirectX::XMFLOAT4& cameraEye
    )
    {
        SpecularSceneConstants sceneConstantData = {viewProjection, lightDirection, cameraEye};
        immediateContext->UpdateSubresource(*sceneConstantBuffer, 0, nullptr, &sceneConstantData, 0, 0);
        immediateContext->VSSetConstantBuffers(REGISTER_SCENE_CONSTANT, 1, sceneConstantBuffer);
        immediateContext->PSSetConstantBuffers(REGISTER_SCENE_CONSTANT, 1, sceneConstantBuffer);
    }

}