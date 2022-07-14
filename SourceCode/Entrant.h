#ifndef INCLUDED_ENTRANT_H
#define INCLUDED_ENTRANT_H

//------< include >-----------------------------------------------------------------------
#include "../TechSharkLib/Inc/Component.h"
#include "../TechSharkLib/Inc/KeyAssign.h"
#include "../TechSharkLib/Inc/Transform3D.h"
#include "../TechSharkLib/Inc/StaticMeshRenderer.h"
#include "../TechSharkLib/Inc/StaticMeshID.h"
#include <array>
#include "Config.h"

//========================================================================================
// 
//      EntrantDesc
// 
//========================================================================================
struct EntrantDesc
{
    TechSharkLib::KeyAssign* keyLeft;
    TechSharkLib::KeyAssign* keyRight;
    TechSharkLib::KeyAssign* keyUp;
    TechSharkLib::KeyAssign* keyDown;
    unsigned int typeFlags; // config::entrant::TYPE_FLAG enum
};

//========================================================================================
// 
//      Entrant
// 
//========================================================================================
class Entrant : public TechSharkLib::Component
{
TSL_DEFINE_COMPONENT(Entrant);
public:
    using TYPE_FLAG = config::entrant::TYPE_FLAG;
    using STATE     = config::entrant::STATE;
    using MESH      = config::entrant::MESH;

private:
    TechSharkLib::Transform3D*          transform;
    TechSharkLib::StaticMeshRenderer*   renderer;

    DirectX::XMFLOAT3 firstPosition;

    struct KeyBind {
        int left     = -1;
        int right    = -1;
        int up       = -1;
        int down     = -1;
    } keyBind;
    int onlyPushedKey;
    unsigned int typeFlags;
    STATE state;

    EntrantDesc description;

    static std::array<TechSharkLib::StaticMeshID, static_cast<size_t>(MESH::NUM)> meshes;

public:
    Entrant() = delete;
    Entrant(const TechSharkLib::ComponentID& selfId, TechSharkLib::GameObject* owner, const EntrantDesc& desc) : 
        transform{nullptr}, renderer{nullptr},
        firstPosition{},
        keyBind{}, onlyPushedKey{NULL},
        typeFlags{TYPE_FLAG::NONE},
        state{STATE::NONE},
        description{desc},
        TechSharkLib::Component{selfId, owner}
    {
    }

    void Init() override;
    void Setup() override;
    void Update(float /*deltaTime*/);
    void Render(float /*deltaTime*/, float /*deltaTime*/) override {}
    void Deinit() override {}

    void DrawDebugGUI() override {}

    const DirectX::XMFLOAT3& Position() const { return transform->Position(); }
    const DirectX::XMFLOAT3& FirstPosition() const noexcept { return firstPosition; }
    int OnlyPushedKey() const noexcept { return onlyPushedKey; }
    const KeyBind* GetKeyBindRef() const { return &keyBind; }
    bool IsNPC() { return (typeFlags & TYPE_FLAG::IS_NPC); }
    bool IsSecondPlayer() { return (typeFlags & TYPE_FLAG::IS_2ND) != NULL; }
    
    void SetMesh(STATE state);
    void SetPosition(const DirectX::XMFLOAT3& position) { transform->SetPosition(position); }
    void ResetPosition() { transform->SetPosition(firstPosition); }
    
    static void LoadMeshes();
    static void ReleaseMeshes();
};

#endif // !INCLUDED_ENTRANT_H