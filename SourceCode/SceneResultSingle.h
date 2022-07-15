#pragma once

//------< include >-----------------------------------------------------------------------
#include "../TechSharkLib/Inc/Scene.h"
#include "Config.h"
#include "../TechSharkLib/Inc/SpriteID.h"
#include "ClickField.h"

//========================================================================================
// 
//      SceneResultSingle
// 
//========================================================================================
class SceneResultSingle : public TechSharkLib::Scene
{
private:
    using RESULT = config::rule::RESULT;
    RESULT result;

    TechSharkLib::SpriteID  backResult;
    TechSharkLib::SpriteID  backToTitle;
    TechSharkLib::SpriteID  retry;
    float                   rotationZ;
    float                   rotateZPerSec;
    ClickField              toTitle;
    ClickField              toGame;

    void Init() override;
    void Setup() override;
    void Update(float deltaTime) override;
    void Render() override;
    void Deinit() override;

public:
    SceneResultSingle(RESULT result) : 
        result{result},
        backResult{}, backToTitle{}, retry{},
        rotationZ{0.0f}, rotateZPerSec{},
        toTitle{}, toGame{},
        TechSharkLib::Scene{}
    {
    }
    ~SceneResultSingle() override {}

};