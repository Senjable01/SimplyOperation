#pragma once

//------< include >-----------------------------------------------------------------------
#include <DirectXMath.h>

namespace TechSharkLib
{
    class GameObjectManager;
    class GameObject;
}
class GameMode;

namespace recipe
{
    void CreateMesh(TechSharkLib::GameObjectManager* objManager, const wchar_t* objFilePath, const char* debugName);
    void CreateMesh(
        TechSharkLib::GameObjectManager* objManager,
        const wchar_t* objFilePath,
        const DirectX::XMFLOAT3& position, const DirectX::XMFLOAT3& scale, const DirectX::XMFLOAT3& rotation,
        const char* debugName
    );
    void CreateEntrant01(TechSharkLib::GameObjectManager* objManager, GameMode* gameMode);
    void CreateEntrant02(TechSharkLib::GameObjectManager* objManager, GameMode* gameMode, bool isNPC);
    void CreateControllerGuide(
        TechSharkLib::GameObjectManager* objManager,
        const DirectX::XMFLOAT3& position
    );
}