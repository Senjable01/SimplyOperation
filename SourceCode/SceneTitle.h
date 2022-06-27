#pragma once

//------< include >-----------------------------------------------------------------------
#include "../TechSharkLib/Inc/Scene.h"
#include "../TechSharkLib/Inc/GameObject.h"

//========================================================================================
// 
//      SceneTitle
// 
//========================================================================================
class SceneTitle : public TechSharkLib::Scene
{
private:
    TechSharkLib::GameObjectManager objManager;

    void Init() override;
    void Setup() override;
    void Update(float) override;
    void Render() override;
    void Deinit() override;

public:
    SceneTitle() : objManager{}, TechSharkLib::Scene{} {}
    ~SceneTitle() override {}

};