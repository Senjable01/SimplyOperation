//------< include >-----------------------------------------------------------------------
#include "Recipe.h"
#include "../TechSharkLib/Inc/GameObject.h"
#include <crtdbg.h>
#include "../TechSharkLib/Inc/Transform3D.h"
#include "../TechSharkLib/Inc/StaticMeshRenderer.h"
#include "Obj3DDebugger.h"
#include "Entrant.h"
#include "../TechSharkLib/Inc/KeyAssign.h"
#include "GameMode.h"
#include "FourWayGuide.h"

using TechSharkLib::Transform3D;
using TechSharkLib::StaticMeshRenderer;
using TechSharkLib::BIT_NO;
using TechSharkLib::Float3;

namespace recipe
{
    //------< using >-------------------------------------------------------------------------
    using TechSharkLib::GameObjectManager;
    using TechSharkLib::GameObject;
    using TechSharkLib::Transform3D;
    using TechSharkLib::StaticMeshRenderer;

    void CreateMesh(GameObjectManager* objManager, const wchar_t* objFilePath, const char* debugName)
    {
        TechSharkLib::GameObjectID objId = objManager->CreateObject();

        TechSharkLib::Transform3DDesc transformDesc = {};
        transformDesc.position  = { 0.0f, 0.0f, 0.0f };
        transformDesc.scale     = { 0.3f, 0.3f, 0.3f };
        transformDesc.rotation  = { 0.0f, 0.0f, 0.0f };
        objManager->AttachComponent<Transform3D>(objId, transformDesc);

        TechSharkLib::StaticMeshRendererDesc rendererDesc = {};
        rendererDesc.objFilePath    = objFilePath;
        rendererDesc.flipVCoord     = true;
        rendererDesc.materialColor  = { 1.0f, 0.0f, 0.0f, 1.0f };
        objManager->AttachComponent<StaticMeshRenderer>(objId, rendererDesc);

        Obj3DDebuggerDesc debuggerDesc = {};
        debuggerDesc.name = debugName;
        objManager->AttachComponent<Obj3DDebugger>(objId, debuggerDesc);

        objManager->Init(objId);
        objManager->Setup(objId);
    }
    void CreateMesh(
        GameObjectManager* objManager,
        const wchar_t* objFilePath,
        const DirectX::XMFLOAT3& position, const DirectX::XMFLOAT3& scale, const DirectX::XMFLOAT3& rotation,
        const char* debugName
    )
    {
        TechSharkLib::GameObjectID objId = objManager->CreateObject();

        TechSharkLib::Transform3DDesc transformDesc = {};
        transformDesc.position  = position;
        transformDesc.scale     = scale;
        transformDesc.rotation  = rotation;
        objManager->AttachComponent<Transform3D>(objId, transformDesc);

        TechSharkLib::StaticMeshRendererDesc rendererDesc = {};
        rendererDesc.objFilePath    = objFilePath;
        rendererDesc.flipVCoord     = true;
        rendererDesc.materialColor  = { 1.0f, 0.0f, 0.0f, 1.0f };
        objManager->AttachComponent<StaticMeshRenderer>(objId, rendererDesc);

        Obj3DDebuggerDesc debuggerDesc = {};
        debuggerDesc.name = debugName;
        objManager->AttachComponent<Obj3DDebugger>(objId, debuggerDesc);

        objManager->Init(objId);
        objManager->Setup(objId);
    }

    void CreateEntrant01(TechSharkLib::GameObjectManager* objManager, GameMode* gameMode)
    {
        TechSharkLib::GameObjectID objId = objManager->CreateObject();

        TechSharkLib::Transform3DDesc transformDesc = {};
        transformDesc.position  = { -1.0f, -0.5f, -1.0f };
        transformDesc.scale     = { 0.3f, 0.3f, 0.3f };
        transformDesc.rotation  = { 1.8f, 0.0f, 0.0f };
        objManager->AttachComponent<Transform3D>(objId, transformDesc);

        EntrantDesc entrantDesc     = {};
        entrantDesc.keyLeft         = BIT_NO::BIT_13;
        entrantDesc.keyRight        = BIT_NO::BIT_12;
        entrantDesc.keyUp           = BIT_NO::BIT_11;
        entrantDesc.keyDown         = BIT_NO::BIT_14;
        entrantDesc.activeKey       = true;
        entrantDesc.isSecondEntrant = false;
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
        transformDesc.position  = { 1.0f, 0.5f, 1.0f };
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
        entrantDesc.isSecondEntrant = true;
        objManager->AttachComponent<Entrant>(objId, entrantDesc);
        Entrant* entrant = objManager->GetGameObjectRef(objId)->SearchComponent<Entrant>();
        gameMode->SetEntrant02(entrant);

        objManager->Init(objId);
        objManager->Setup(objId);
    }

    void CreateControllerGuide(
        TechSharkLib::GameObjectManager* objManager,
        const DirectX::XMFLOAT3& position
    )
    {
        TechSharkLib::GameObjectID objId = objManager->CreateObject();

        TechSharkLib::Transform3DDesc transformDesc = {};
        transformDesc.position  = position;
        transformDesc.scale     = { 0.3f, 0.3f, 0.3f };
        transformDesc.rotation  = { 1.8f, 0.0f, 0.0f };
        objManager->AttachComponent<Transform3D>(objId, transformDesc);

        FourWayGuideDesc fourWayDesc    = {};
        // Path
        fourWayDesc.stickObjPath        = L"Data/Models/Stick_1/Stick_1.obj";
        fourWayDesc.allowObjPath        = L"Data/Models/Arrow_button/Arrow_button.obj";
        fourWayDesc.leanStickObjPath    = L"Data/Models/Stick_2/Stick_2.obj";
        // Position
        fourWayDesc.posBase             = position;
        fourWayDesc.relativePosLeft     = Float3{ -0.6f, 0.0f, 0.0f };
        fourWayDesc.relativePosRight    = Float3{ 0.6f, 0.0f, 0.0f };
        fourWayDesc.relativePosUp       = Float3{ 0.0f, 0.6f, 0.0f };
        fourWayDesc.relativePosDown     = Float3{ 0.0f, -0.6f, 0.0f };
        // Scale
        fourWayDesc.scaleBase           = Float3{ 0.2f, 0.2f, 0.2f };
        fourWayDesc.scaleLeft           = Float3{ 0.025f, 0.025f, 0.025f };
        fourWayDesc.scaleRight          = Float3{ 0.025f, 0.025f, 0.025f };
        fourWayDesc.scaleUp             = Float3{ 0.025f, 0.025f, 0.025f };
        fourWayDesc.scaleDown           = Float3{ 0.025f, 0.025f, 0.025f };
        // Rotation
        constexpr float RIGHT_ANGLE     = DirectX::XM_PIDIV2;
        fourWayDesc.rotationBase        = Float3{ -RIGHT_ANGLE, 0.0f, 0.0f };
        fourWayDesc.rotationLeft        = Float3{ 0.0f, RIGHT_ANGLE, -RIGHT_ANGLE };
        fourWayDesc.rotationRight       = Float3{ 0.0f, -RIGHT_ANGLE, RIGHT_ANGLE };
        fourWayDesc.rotationUp          = Float3{ RIGHT_ANGLE, DirectX::XM_PI, 0.0f };
        fourWayDesc.rotationDown        = Float3{ -RIGHT_ANGLE, 0.0f, 0.0f };
        // (Stick Ver.)
        fourWayDesc.stickLeanUpRotation     = Float3{ 0.0f, -RIGHT_ANGLE, RIGHT_ANGLE };
        fourWayDesc.stickLeanRightRotation  = Float3{ -RIGHT_ANGLE, 0.0f, 0.0f };
        fourWayDesc.stickLeanDownRotation   = Float3{ 0.0f, RIGHT_ANGLE, -RIGHT_ANGLE };
        fourWayDesc.stickLeanLeftRotation   = Float3{ RIGHT_ANGLE, DirectX::XM_PI, 0.0f };

        objManager->AttachComponent<FourWayGuide>(objId, fourWayDesc);

        objManager->Init(objId);
        objManager->Setup(objId);
    }

}