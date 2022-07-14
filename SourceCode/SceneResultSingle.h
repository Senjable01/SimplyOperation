#pragma once

//------< include >-----------------------------------------------------------------------
#include "../TechSharkLib/Inc/Scene.h"
#include "Config.h"

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

    void Init() override;
    void Setup() override;
    void Update(float/*deltaTime*/) override;
    void Render() override;
    void Deinit() override;

public:
    SceneResultSingle(RESULT result) : result{result}, TechSharkLib::Scene{} {}
    ~SceneResultSingle() override {}

};