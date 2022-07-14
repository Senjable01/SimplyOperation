#pragma once

//------< include >-----------------------------------------------------------------------
#include <DirectXMath.h>
#include "../TechSharkLib/Inc/Vector.h"

//------< using >-------------------------------------------------------------------------

namespace TechSharkLib
{
    class GameObjectManager;
    class GameObject;
    class Camera;
}
class GameMode;

//========================================================================================
// 
//      Recipe
// 
//========================================================================================
namespace recipe
{
    void CreateMesh(
        TechSharkLib::GameObjectManager* objManager,
        const wchar_t* objFilePath,
        const DirectX::XMFLOAT3& position, const DirectX::XMFLOAT3& scale, const DirectX::XMFLOAT3& rotation,
        const char* debugName
    );
    void CreateEntrant01(
        TechSharkLib::GameObjectManager* objManager,
        GameMode* gameMode
    );
    void CreateEntrant02(
        TechSharkLib::GameObjectManager* objManager,
        GameMode* gameMode,
        bool isNPC
    );
    void CreateGuide(
        TechSharkLib::GameObjectManager* objManager,
        GameMode* gameMode,
        TechSharkLib::Camera* defaultCamera,
        const TechSharkLib::Float4& lightDirection
    );
}