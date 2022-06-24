#pragma once

//------< include >-----------------------------------------------------------------------
#include "../TechSharkLib/Inc/Scene.h"
#include "../TechSharkLib/Inc/Camera.h"
#include "../TechSharkLib/Inc/Vector.h"

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

    void Init() override;
    void Setup() override;
    void Update(float/*deltaTime*/) override;
    void Render() override;
    void Deinit() override;

public:
    SceneGameSingle() : 
        camera{}, lightDirection{1.0f, 0.7f, 0.0f, 1.0f},
        TechSharkLib::Scene{}
    {
    }
    ~SceneGameSingle() override {}

};