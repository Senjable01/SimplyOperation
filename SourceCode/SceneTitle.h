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
    TechSharkLib::SpriteID specialThanks;

    void Init() override;
    void Setup() override;
    void Update(float) override;
    void Render() override;
    void Deinit() override;

public:
    SceneTitle() : background{}, specialThanks{}, TechSharkLib::Scene{} {}
    ~SceneTitle() override {}

};