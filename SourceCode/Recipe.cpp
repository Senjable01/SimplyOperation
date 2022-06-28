//------< include >-----------------------------------------------------------------------
#include "Recipe.h"
#include "../TechSharkLib/Inc/GameObject.h"
#include <crtdbg.h>
#include "../TechSharkLib/Inc/Transform3D.h"
#include "../TechSharkLib/Inc/StaticMeshRenderer.h"

namespace recipe
{
    //------< using >-------------------------------------------------------------------------
    using TechSharkLib::GameObjectManager;
    using TechSharkLib::GameObject;
    using TechSharkLib::Transform3D;
    using TechSharkLib::StaticMeshRenderer;

    void CreateMesh(GameObjectManager* objManager)
    {
        GameObject* obj = nullptr;
        objManager->CreateObject(&obj);
        _ASSERT_EXPR(obj != nullptr, L"GameObject‚Ì¶¬‚ÉŽ¸”s");



        obj->Init();
        obj->Setup();
    }
}