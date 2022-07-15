#pragma once

//------< include >-----------------------------------------------------------------------
#include "../TechSharkLib/Inc/Scene.h"
#include "../TechSharkLib/Inc/SpriteID.h"
#include "ClickField.h"

//========================================================================================
// 
//      SceneTitle
// 
//========================================================================================
class SceneTitle : public TechSharkLib::Scene
{
private:
    TechSharkLib::SpriteID background;
    TechSharkLib::SpriteID start;
    TechSharkLib::SpriteID exit;
    ClickField toGame;
    ClickField toExit;
    float       elapsedSec;

    void Init() override;
    void Setup() override;
    void Update(float) override;
    void Render() override;
    void Deinit() override;

public:
    SceneTitle() : background{}, start{}, exit{}, toGame{}, toExit{}, elapsedSec{}, TechSharkLib::Scene{} {}
    ~SceneTitle() override {}

};