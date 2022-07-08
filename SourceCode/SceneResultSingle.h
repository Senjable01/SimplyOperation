#pragma once

//------< include >-----------------------------------------------------------------------
#include "../TechSharkLib/Inc/Scene.h"

//========================================================================================
// 
//      SceneResultSingle
// 
//========================================================================================
class SceneResultSingle : public TechSharkLib::Scene
{
private:
    int result;

    void Init() override;
    void Setup() override;
    void Update(float/*deltaTime*/) override;
    void Render() override;
    void Deinit() override;

public:
    SceneResultSingle(int result) : result{result}, TechSharkLib::Scene{} {}
    ~SceneResultSingle() override {}

};