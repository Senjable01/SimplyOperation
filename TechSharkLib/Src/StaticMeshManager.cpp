//------< include >-----------------------------------------------------------------------
#include "../Inc/StaticMeshManager.h"
#include "../Inc/Configulation.h"
#if DEBUG_MODE
#include "../Inc/DebugTools.h"

#else
#include <crtdbg.h>

#endif // DEBUG_MODE

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
    //      StaticMeshManager
    // 
    //========================================================================================

    //------------------------------------------------------------------------------
    // member functions
    //------------------------------------------------------------------------------

    void StaticMeshManager::Initialize(ID3D11Device* device, ID3D11DeviceContext* immediateContext)
    {
        _ASSERT_EXPR(device != nullptr, L"deviceÇ™nullptr");
        _ASSERT_EXPR(immediateContext != nullptr, L"immediateContextÇ™nullptr");
        this->device            = device;
        this->immediateContext  = immediateContext;
    }

    StaticMeshID StaticMeshManager::Load(const wchar_t* filePath, bool flipVCoord)
    {
        StaticMeshID id = StaticMeshID{StaticMeshManager::nextId++};
        staticMeshMap.emplace(id, std::make_unique<StaticMesh>(device, filePath, flipVCoord));
        return id;
    }
    void StaticMeshManager::Render(const StaticMeshID& id, const DirectX::XMFLOAT4X4& world, const DirectX::XMFLOAT4& materialColor)
    {
        staticMeshMap.at(id)->Render(immediateContext, world, materialColor);
    }
    void StaticMeshManager::Release(const StaticMeshID& id)
    {
        staticMeshMap.erase(id);
    }

    void StaticMeshManager::ReleaseAll()
    {
        #if DEBUG_MODE
        size_t remainNum = staticMeshMap.size();
        if (remainNum)
        {
            ExpressDebugLog("<WARNING>: ", remainNum, L"å¬ÇÃStaticMeshÇ™ÉäÉäÅ[ÉXÇ≥ÇÍÇƒÇ¢Ç‹ÇπÇÒÇ≈ÇµÇΩÅB");
        }

        #endif // DEBUG_MODE
        staticMeshMap.clear();

    }

    //--------------------------------------------------------------------------
    // instance
    //--------------------------------------------------------------------------

    unsigned int StaticMeshManager::nextId = ERROR_STATIC_MESH_ID + 1;

}