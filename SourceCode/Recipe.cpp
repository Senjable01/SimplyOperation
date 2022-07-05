//------< include >-----------------------------------------------------------------------
#include "Recipe.h"
#include "../TechSharkLib/Inc/GameObject.h"
#include <crtdbg.h>
#include "../TechSharkLib/Inc/Transform3D.h"
#include "../TechSharkLib/Inc/StaticMeshRenderer.h"
#include "Entrant.h"
#include "../TechSharkLib/Inc/KeyAssign.h"
#include "GameMode.h"

using TechSharkLib::Transform3D;
using TechSharkLib::StaticMeshRenderer;
using TechSharkLib::BIT_NO;

namespace recipe
{
    //------< using >-------------------------------------------------------------------------
    using TechSharkLib::GameObjectManager;
    using TechSharkLib::GameObject;
    using TechSharkLib::Transform3D;
    using TechSharkLib::StaticMeshRenderer;

    void CreateMesh(GameObjectManager* objManager, const wchar_t* objFilePath)
    {
        TechSharkLib::GameObjectID objId = objManager->CreateObject();

        TechSharkLib::Transform3DDesc transformDesc = {};
        transformDesc.position  = { 0.0f, 0.0f, 0.0f };
        transformDesc.scale     = { 0.3f, 0.3f, 0.3f };
        transformDesc.rotation  = { 0.0f, 0.0f, 0.0f };
        objManager->AttachComponent<Transform3D>(objId, transformDesc);

        TechSharkLib::StaticMeshRendererDesc rendererDesc = {};
        rendererDesc.objFilePath = objFilePath;
        rendererDesc.flipVCoord = true;
        rendererDesc.materialColor = { 1.0f, 0.0f, 0.0f, 1.0f };
        objManager->AttachComponent<StaticMeshRenderer>(objId, rendererDesc);

        objManager->Init(objId);
        objManager->Setup(objId);
    }

    void CreateEntrant01(TechSharkLib::GameObjectManager* objManager, GameMode* gameMode)
    {
        TechSharkLib::GameObjectID objId = objManager->CreateObject();

        TechSharkLib::Transform3DDesc transformDesc = {};
        transformDesc.position  = { -1.0f, 0.0f, 0.0f };
        transformDesc.scale     = { 0.3f, 0.3f, 0.3f };
        transformDesc.rotation  = { 1.8f, 0.0f, 0.0f };
        objManager->AttachComponent<Transform3D>(objId, transformDesc);

        EntrantDesc entrantDesc = {};
        entrantDesc.keyLeft     = BIT_NO::BIT_13;
        entrantDesc.keyRight    = BIT_NO::BIT_12;
        entrantDesc.keyUp       = BIT_NO::BIT_11;
        entrantDesc.keyDown     = BIT_NO::BIT_14;
        entrantDesc.activeKey   = true;
        objManager->AttachComponent<Entrant>(objId, entrantDesc);
        Entrant* entrant = objManager->GetGameObjectRef(objId)->SearchComponent<Entrant>();
        gameMode->SetEntrant01(entrant);

        objManager->Init(objId);
        objManager->Setup(objId);

    }
    void CreateEntrant02(TechSharkLib::GameObjectManager* objManager, GameMode* gameMode, bool isNPC)
    {
        TechSharkLib::GameObjectID objId = objManager->CreateObject();

        TechSharkLib::Transform3DDesc transformDesc = {};
        transformDesc.position  = { 1.0f, 0.0f, 0.0f };
        transformDesc.scale     = { 0.3f, 0.3f, 0.3f };
        transformDesc.rotation  = { 1.8f, 0.0f, 0.0f };
        objManager->AttachComponent<Transform3D>(objId, transformDesc);

        EntrantDesc entrantDesc = {};
        if (isNPC)
        {
            entrantDesc.activeKey = false;
        }
        else
        {
            entrantDesc.keyLeft     = BIT_NO::BIT_17;
            entrantDesc.keyRight    = BIT_NO::BIT_16;
            entrantDesc.keyUp       = BIT_NO::BIT_15;
            entrantDesc.keyDown     = BIT_NO::BIT_18;
            entrantDesc.activeKey   = true;
        }
        objManager->AttachComponent<Entrant>(objId, entrantDesc);
        Entrant* entrant = objManager->GetGameObjectRef(objId)->SearchComponent<Entrant>();
        gameMode->SetEntrant02(entrant);

        objManager->Init(objId);
        objManager->Setup(objId);
    }

}