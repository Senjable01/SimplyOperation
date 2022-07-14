#pragma once

//------< include >-----------------------------------------------------------------------
#include "../TechSharkLib/Inc/Scene.h"
#include "../TechSharkLib/Inc/SpriteID.h"

//========================================================================================
// 
//      SceneTitle
// 
//========================================================================================
class SceneTitle : public TechSharkLib::Scene
{
private:
    TechSharkLib::SpriteID background;

    void Init() override;
    void Setup() override;
    void Update(float) override;
    void Render() override;
    void Deinit() override;

public:
    SceneTitle() : background{}, TechSharkLib::Scene{} {}
    ~SceneTitle() override {}

};