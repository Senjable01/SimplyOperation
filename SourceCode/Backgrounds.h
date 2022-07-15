#ifndef INCLUDED_BACKGROUNDS_H
#define INCLUDED_BACKGROUNDS_H

//------< include >-----------------------------------------------------------------------
#include <map>
#include <string>
#include "../TechSharkLib/Inc/SpriteID.h"
#include "../TechSharkLib/Inc/Vector.h"
#include "Observer.h"
#include "Config.h"
#include "../TechSharkLib/Inc/TechSharkLib.h"

//========================================================================================
// 
//      Backgrounds
// 
//========================================================================================
class Backgrounds
{
public:
    using No = unsigned int;
    static constexpr No ERROR_NO = 0;

private:
    std::map<No, TechSharkLib::SpriteID> spriteMap;
    No                      spriteNo;
    TechSharkLib::Float2    position;
    TechSharkLib::Float2    scale;
    TechSharkLib::Float2    pivot;
    float                   rotationZ;
    class Observer_ : public Observer<No>
    {
    private:
        No lastReport;
        void OnNotify(const No& report) override { lastReport = report; }

    public:
        Observer_() : lastReport{} {}
        
        void Setup(No spriteNo) { lastReport = spriteNo; }
        No LastReport() const noexcept { return lastReport; }

    } observer;

public:
    Backgrounds() : 
        spriteNo{ERROR_NO},
        position{config::background::UI_POS}, 
        scale{config::background::UI_SCALE},
        pivot{config::background::PIVOT},
        rotationZ{0.0f}
    {
        spriteMap.emplace(ERROR_NO, TechSharkLib::ERROR_SPRITE_ID);
    }

    void AddBackground(const No& no, const wchar_t* backgroundPath)
    {
        spriteMap.emplace(no, TechSharkLib::LoadSprite(backgroundPath));
    }
    Observer_* GetObserverRef() { return &observer; }
    void Update()
    {
        spriteNo = observer.LastReport();
    }
    void Render(float red, float green, float blue, float alpha)
    {
        if (spriteNo == ERROR_NO) return;
        
        TechSharkLib::Render(
            spriteMap.at(spriteNo),
            position.x, position.y,
            scale.x, scale.y,
            pivot.x, pivot.y,
            rotationZ,
            red, green, blue, alpha
        );
    }
    void Deinit()
    {
        for (auto& id : spriteMap)
        {
            TechSharkLib::Release(id.second);
        }
    }

};

#endif // !INCLUDED_BACKGROUNDS_H