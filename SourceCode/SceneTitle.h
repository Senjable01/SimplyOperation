#pragma once

//------< include >-----------------------------------------------------------------------
#include "../TechSharkLib/Inc/Scene.h"

//========================================================================================
// 
//      SceneTitle
// 
//========================================================================================
class SceneTitle : public TechSharkLib::Scene
{
private:
    void Init() override;
    void Setup() override;
    void Update(float) override;
    void Render() override;
    void Deinit() override;

public:
    SceneTitle() : TechSharkLib::Scene{} {}
    ~SceneTitle() override {}

};