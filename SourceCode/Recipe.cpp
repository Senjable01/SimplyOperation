//------< include >-----------------------------------------------------------------------
#include "Recipe.h"
#include "../TechSharkLib/Inc/GameObject.h"
#include "../TechSharkLib/Inc/Transform3D.h"
#include "../TechSharkLib/Inc/StaticMeshRenderer.h"
#include "../TechSharkLib/Inc/TechSharkLib.h"
#include "OBJDebugger.h"
#include "Config.h"
#include "Entrant.h"
#include "GameMode.h"
#include "OperateGuide.h"
#include "../TechSharkLib/Inc/Camera.h"

//------< using >-------------------------------------------------------------------------

using TechSharkLib::GameObjectID;
using TechSharkLib::Transform3DDesc;
using TechSharkLib::Transform3D;
using TechSharkLib::StaticMeshRendererDesc;
using TechSharkLib::StaticMeshRenderer;

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
    )
    {
        GameObjectID obj = objManager->CreateObject();

        Transform3DDesc transformDesc   = {};
        transformDesc.position          = position;
        transformDesc.scale             = scale;
        transformDesc.rotation          = rotation;
        objManager->AttachComponent<Transform3D>(obj, transformDesc);

        StaticMeshRendererDesc rendererDesc = {};
        rendererDesc.staticMeshId           = TechSharkLib::LoadStaticMesh(objFilePath, true);
        rendererDesc.materialColor          = {1.0f, 1.0f, 1.0f, 1.0f};
        objManager->AttachComponent<StaticMeshRenderer>(obj, rendererDesc);

        OBJDebuggerDesc debuggerDesc    = {};
        debuggerDesc.debugName          = debugName;
        objManager->AttachComponent<OBJDebugger>(obj, debuggerDesc);

        objManager->Init(obj);
        objManager->Setup(obj);
    }

    void CreateEntrant01(
        TechSharkLib::GameObjectManager* objManager,
        GameMode* gameMode
    )
    {
        GameObjectID obj = objManager->CreateObject();

        Transform3DDesc transformDesc   = {};
        transformDesc.position          = config::entrant::BEGIN_POS_FRONT;
        //transformDesc.scale             = {1.0f, 1.0f, 1.0f};
        transformDesc.rotation          = {0.0f, 0.0f, 0.0f};
        objManager->AttachComponent<Transform3D>(obj, transformDesc);

        StaticMeshRendererDesc rendererDesc = {};
        rendererDesc.materialColor          = {1.0f, 1.0f, 1.0f, 1.0f};
        objManager->AttachComponent<StaticMeshRenderer>(obj, rendererDesc);

        EntrantDesc entrantDesc = {};
        entrantDesc.keyLeft     = &config::key::left1;
        entrantDesc.keyRight    = &config::key::right1;
        entrantDesc.keyUp       = &config::key::up1;
        entrantDesc.keyDown     = &config::key::down1;
        entrantDesc.typeFlags   = config::entrant::TYPE_FLAG::NONE;
        objManager->AttachComponent<Entrant>(obj, entrantDesc);
        Entrant* entrant = objManager->GetGameObjectRef(obj)->SearchComponent<Entrant>();
        _ASSERT_EXPR(entrant != nullptr, L"EntrantƒRƒ“ƒ|[ƒlƒ“ƒg‚ÌŒŸõ‚ÉŽ¸”s");
        _ASSERT_EXPR(gameMode->GetEntrant01Ref() == nullptr, L"Entrant01‚Í“o˜^Ï‚Ý");
        gameMode->SetEntrant01Ref(entrant);

        objManager->Init(obj);
        objManager->Setup(obj);
    }

    void CreateEntrant02(
        TechSharkLib::GameObjectManager* objManager,
        GameMode* gameMode,
        bool isNPC
    )
    {
        GameObjectID obj = objManager->CreateObject();

        Transform3DDesc transformDesc   = {};
        transformDesc.position          = config::entrant::BEGIN_POS_BACK;
        //transformDesc.scale             = {1.0f, 1.0f, 1.0f};
        transformDesc.rotation          = {0.0f, 0.0f, 0.0f};
        objManager->AttachComponent<Transform3D>(obj, transformDesc);

        StaticMeshRendererDesc rendererDesc = {};
        rendererDesc.materialColor          = {1.0f, 1.0f, 1.0f, 1.0f};
        objManager->AttachComponent<StaticMeshRenderer>(obj, rendererDesc);

        EntrantDesc entrantDesc = {};
        if (isNPC)
        {
            entrantDesc.typeFlags   = config::entrant::TYPE_FLAG::IS_2ND | config::entrant::TYPE_FLAG::IS_NPC;
        }
        else
        {
            entrantDesc.keyLeft     = &config::key::left2;
            entrantDesc.keyRight    = &config::key::right2;
            entrantDesc.keyUp       = &config::key::up2;
            entrantDesc.keyDown     = &config::key::down2;
            entrantDesc.typeFlags   = config::entrant::TYPE_FLAG::IS_2ND;
        }
        objManager->AttachComponent<Entrant>(obj, entrantDesc);
        Entrant* entrant = objManager->GetGameObjectRef(obj)->SearchComponent<Entrant>();
        _ASSERT_EXPR(entrant != nullptr, L"EntrantƒRƒ“ƒ|[ƒlƒ“ƒg‚ÌŒŸõ‚ÉŽ¸”s");
        _ASSERT_EXPR(gameMode->GetEntrant02Ref() == nullptr, L"Entrant02‚Í“o˜^Ï‚Ý");
        gameMode->SetEntrant02Ref(entrant);

        objManager->Init(obj);
        objManager->Setup(obj);
    }
    void CreateGuide(
        TechSharkLib::GameObjectManager* objManager,
        GameMode* gameMode,
        TechSharkLib::Camera* defaultCamera,
        const TechSharkLib::Float4& lightDirection
    )
    {
        namespace stick     = config::model::stick;
        namespace button    = config::model::button;
        namespace guide     = config::guide;
        using TechSharkLib::Float3;

        TechSharkLib::GameObjectID obj = objManager->CreateObject();

        TechSharkLib::Transform3DDesc transformDesc = {};
        transformDesc.position  = {-3.5f, -0.0f, 0.0f};
        transformDesc.scale     = stick::SCALE;
        transformDesc.rotation  = stick::ROTATE_NORMAL;
        objManager->AttachComponent<Transform3D>(obj, transformDesc);

        OperateGuideDesc guideDesc = {};
        guideDesc.relativePositions[static_cast<int>(guide::DIRECTION::LEFT)]   = Float3{-0.6f, 0.0f, 0.0f};
        guideDesc.relativePositions[static_cast<int>(guide::DIRECTION::RIGHT)]  = Float3{0.6f, 0.0f, 0.0f};
        guideDesc.relativePositions[static_cast<int>(guide::DIRECTION::UP)]     = Float3{0.0f, 0.6f, 0.0f};
        guideDesc.relativePositions[static_cast<int>(guide::DIRECTION::DOWN)]   = Float3{0.0f, -0.6f, 0.0f};
        guideDesc.scales[static_cast<int>(guide::DIRECTION::LEFT)]              = Float3{0.025f, 0.025f, 0.025f};
        guideDesc.scales[static_cast<int>(guide::DIRECTION::RIGHT)]             = Float3{0.025f, 0.025f, 0.025f};
        guideDesc.scales[static_cast<int>(guide::DIRECTION::UP)]                = Float3{0.025f, 0.025f, 0.025f};
        guideDesc.scales[static_cast<int>(guide::DIRECTION::DOWN)]              = Float3{0.025f, 0.025f, 0.025f};
        guideDesc.buttonRotations[static_cast<int>(guide::DIRECTION::LEFT)]     = button::ROTATE_LEFT;
        guideDesc.buttonRotations[static_cast<int>(guide::DIRECTION::RIGHT)]    = button::ROTATE_RIGHT;
        guideDesc.buttonRotations[static_cast<int>(guide::DIRECTION::UP)]       = button::ROTATE_UP;
        guideDesc.buttonRotations[static_cast<int>(guide::DIRECTION::DOWN)]     = button::ROTATE_DOWN;
        guideDesc.stickRotations[static_cast<int>(guide::DIRECTION::LEFT)]      = stick::ROTATE_LEFT;
        guideDesc.stickRotations[static_cast<int>(guide::DIRECTION::RIGHT)]     = stick::ROTATE_RIGHT;
        guideDesc.stickRotations[static_cast<int>(guide::DIRECTION::UP)]        = stick::ROTATE_UP;
        guideDesc.stickRotations[static_cast<int>(guide::DIRECTION::DOWN)]      = stick::ROTATE_DOWN;
        guideDesc.defaultCamera     = defaultCamera;
        guideDesc.lightDirection    = lightDirection;
        objManager->AttachComponent<OperateGuide>(obj, guideDesc);
        OperateGuide* operateGuide = objManager->GetGameObjectRef(obj)->SearchComponent<OperateGuide>();
        gameMode->AddGuideObserver(operateGuide->GetGuideObserverRef());

        objManager->Init(obj);
        objManager->Setup(obj);
    }
}