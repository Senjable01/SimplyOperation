//------< include >-----------------------------------------------------------------------
#include "../Inc/Projector.h"
#include "../Inc/DebugTools.h"
#include "../Inc/MiscTools.h"

//**************************************************************************************************
// 
// 
//          TechSharkLib
// 
// 
//**************************************************************************************************
namespace TechSharkLib
{
    //========================================================================================
    // 
    //      Projector
    // 
    //========================================================================================

    //------------------------------------------------------------------------------
    // member function
    //------------------------------------------------------------------------------

    void Projector::Initialize(ID3D11Device* device, ID3D11DeviceContext* immediateContext)
    {
        _ASSERT_EXPR(device, L"immediateContext‚Ínullptr");
        _ASSERT_EXPR(immediateContext, L"immediateContext‚Ínullptr");
        this->device            = device;
        this->immediateContext  = immediateContext;

    }

    void Projector::Setup(SCENE_CONSTANTS type)
    {
        HRESULT hr = S_OK;

        //UNIT17 Section4
        D3D11_BUFFER_DESC bufferDesc    = {};
        // bufferDesc.ByteWidth
        bufferDesc.Usage                = D3D11_USAGE::D3D11_USAGE_DEFAULT;
        bufferDesc.BindFlags            = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
        bufferDesc.CPUAccessFlags       = 0;
        bufferDesc.MiscFlags            = 0;
        bufferDesc.StructureByteStride  = 0;

        switch (type)
        {
        case SCENE_CONSTANTS::DEFAULT:
            bufferDesc.ByteWidth = sizeof(SceneConstants);
            this->SetSceneConstantBuffer = [this](Camera* camera, const DirectX::XMFLOAT4& lightDirection) -> void {
                DirectX::XMFLOAT4X4 viewProjection = camera->CalcViewProjection();
                TechSharkLib::SetSceneConstantBuffer(
                    this->immediateContext,
                    &sceneConstantBuffer,
                    camera->CalcViewProjection(), lightDirection
                );
            };
            break;

        case SCENE_CONSTANTS::SPECULAR_DIFFUSE:
            //UNDONE:08 ‹¾–Ê”½ŽË+ŠgŽU”½ŽËŒõ‚É‘Î‰ž
            _ASSERT_EXPR(false, L"‹¾–Ê”½ŽË+ŠgŽU”½ŽËŒõ‚É‚Í‘Î‰ž‚µ‚Ä‚¢‚Ü‚¹‚ñB");
            bufferDesc.ByteWidth = sizeof(SpecularSceneConstants);
            this->SetSceneConstantBuffer = [this](Camera* camera, const DirectX::XMFLOAT4& lightDirection) -> void {
                DirectX::XMFLOAT4X4 viewProjection = camera->CalcViewProjection();
                const DirectX::XMFLOAT4& cameraEye = camera->Eye();
                TechSharkLib::SetSpecularSceneConstantBuffer(
                    this->immediateContext,
                    &sceneConstantBuffer,
                    camera->CalcViewProjection(), lightDirection, {cameraEye.x, cameraEye.y, cameraEye.z, 1.0f}
                );
            };
            break;

        }

        hr = device->CreateBuffer(&bufferDesc, nullptr, &sceneConstantBuffer);
        _ASSERT_EXPR(SUCCEEDED(hr), ResultTrace(hr));
    }

    void Projector::Project(Camera* camera, const DirectX::XMFLOAT4& lightDirection)
    {
        this->SetSceneConstantBuffer(camera, lightDirection);
    }

    void Projector::Reset()
    {
        SafeRelease(sceneConstantBuffer);
    }

    void Projector::Uninitialize()
    {
        device              = nullptr;
        immediateContext    = nullptr;
    }

}