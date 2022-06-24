#pragma once

//------< include >-----------------------------------------------------------------------
#include "../TechSharkLib/Inc/Scene.h"

//========================================================================================
// 
//      SceneSelect
// 
//========================================================================================
class SceneSelect : public TechSharkLib::Scene
{
private:
    void Init() override;
    void Setup() override;
    void Update(float/*deltaTime*/) override;
    void Render() override;
    void Deinit() override;

public:
    SceneSelect() : TechSharkLib::Scene{} {}
    ~SceneSelect() override {}

};