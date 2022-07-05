#pragma once

namespace TechSharkLib
{
    class GameObjectManager;
    class GameObject;
}
class GameMode;

namespace recipe
{
    void CreateMesh(TechSharkLib::GameObjectManager* objManager, const wchar_t* objFilePath);
    void CreateEntrant01(TechSharkLib::GameObjectManager* objManager, GameMode* gameMode);
    void CreateEntrant02(TechSharkLib::GameObjectManager* objManager, GameMode* gameMode, bool isNPC);
}