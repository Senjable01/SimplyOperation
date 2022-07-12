#pragma once

//------< include >-----------------------------------------------------------------------
#include "../TechSharkLib/Inc/Scene.h"
#include "../TechSharkLib/Inc/Camera.h"
#include "../TechSharkLib/Inc/Vector.h"
#include "../TechSharkLib/Inc/GameObject.h"
#include "GameMode.h"

//========================================================================================
// 
//      GameSingle
// 
//========================================================================================
class SceneGameSingle : public TechSharkLib::Scene
{
private:
    TechSharkLib::Camera    camera;
    TechSharkLib::Float4    lightDirection;
    TechSharkLib::GameObjectManager objManager;
    GameMode gameMode;

    void Init() override;
    void Setup() override;
    void Update(float/*deltaTime*/) override;
    void Render() override;
    void Deinit() override;

    static void CreateGameObjects(TechSharkLib::GameObjectManager* objManager, GameMode* gameMode);

public:
    SceneGameSingle() : 
        camera{}, lightDirection{1.0f, 0.7f, 0.0f, 1.0f}, objManager{}, gameMode{},
        TechSharkLib::Scene{}
    {
    }
    ~SceneGameSingle() override {}

};