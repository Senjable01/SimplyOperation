#ifndef INCLUDED_GAMEMODE_H
#define INCLUDED_GAMEMODE_H

//------< include >-----------------------------------------------------------------------
#include <memory>
#include "Strategy.h"
#include "Entrant.h"
#include <array>
#include "../TechSharkLib/Inc/Camera.h"
#include "../TechSharkLib/Inc/StaticMeshID.h"
#include "OperateGuide.h"
#include "Backgrounds.h"

//------< class >-------------------------------------------------------------------------

class GameMode;

//========================================================================================
// 
//      GameRule
// 
//========================================================================================
class GameRule : public Strategy<GameMode>
{
private:
    using PHASE = config::rule::PHASE;

    void Run(GameMode* entrant) override;

protected:
    PHASE phase;

    virtual void Setup(GameMode* /*entrant*/) = 0;
    virtual void Reception(GameMode* /*entrant*/) = 0;
    virtual void Judge(GameMode* /*entrant*/) = 0;
    virtual void Idle(GameMode* /*entrant*/) = 0;

public:
    explicit GameRule() : phase{PHASE::SETUP} {}
    virtual void DrawDebugGUI() = 0;
};

//========================================================================================
// 
//      GameMode
// 
//========================================================================================
class GameMode
{
public:
    using RESULT    = config::rule::RESULT;
    using BG_NO     = config::background::GAME_BG_NO;
    enum class ENTRANT : int {_01, _02, NUM};

private:
    std::unique_ptr<GameRule>   gameRule;
    std::unique_ptr<GameRule>   nextRule;
    TechSharkLib::Camera*       camera;
    TechSharkLib::Float4        firstCameraFocus;
    TechSharkLib::StaticMeshID  entrant02Head;
    TechSharkLib::Float3        headPos;
    TechSharkLib::Float3        headScale;
    TechSharkLib::Float3        headRotation;
    TechSharkLib::Float3        firstHeadRotation;
    std::array<Entrant*, static_cast<size_t>(ENTRANT::NUM)> entrants;
    float timerSec;
    bool onceSkipAddSec; //TODO: ???[?h????????????deltaTime??????????????????????(???{?I??????????????)
    RESULT lastResult;
    bool isFinished;
    Subject<OperateGuide::STATE>    guideSubject;
    Subject<Backgrounds::No>        backgroundsSubject;

    void Setup();

public:
    GameMode() : 
        gameRule{nullptr}, nextRule{nullptr}, camera{nullptr}, firstCameraFocus{},
        entrant02Head{}, headPos{}, headScale{}, headRotation{}, firstHeadRotation{},
        entrants{}, timerSec{0.0f}, onceSkipAddSec{true}, lastResult{RESULT::NONE}, isFinished{false},
        guideSubject{}
    {
    }
    
    template<typename Rule> void Start()
    {
        if (gameRule == nullptr)
        {
            gameRule = std::make_unique<Rule>();
        }

        Setup();
    }
    void Update(float deltaTime);
    void Render();
    void End();

    float TimerSec() const noexcept { return timerSec; }
    RESULT LastResult() const noexcept { return lastResult; }
    bool IsFinished() const noexcept { return isFinished; }
    const TechSharkLib::Float4& FirstCameraFocus() const noexcept { return firstCameraFocus; }
    const TechSharkLib::Float3& FirstEntrant02HeadRotation() const noexcept { return firstHeadRotation; }
    Entrant* GetEntrant01Ref() {return entrants.at(static_cast<size_t>(ENTRANT::_01)); }
    Entrant* GetEntrant02Ref() {return entrants.at(static_cast<size_t>(ENTRANT::_02)); }

    void RezeroTimer() { timerSec = 0.0f; }
    void SetResult(RESULT result) { this->lastResult = result; }
    template<typename Rule> void SetNextRule()
    {
        if (nextRule == nullptr)
        {
            nextRule = std::make_unique<Rule>();
        }
    }
    void FinishGame() { isFinished = true; }
    void SetCameraFocus(const TechSharkLib::Float4& focus)
    {
        camera->LookAt(camera->Eye(), focus, camera->Up());
    }
    void ResetCameraFocus()
    {
        camera->LookAt(camera->Eye(), firstCameraFocus, camera->Up());
    }
    void SetEntrant02HeadRotation(const TechSharkLib::Float3& rotation) { headRotation = rotation; }
    void ResetEntrant02HeadRotation() { headRotation = firstHeadRotation; }
    void SetEntrant01Ref(Entrant* entrant01) { entrants.at(static_cast<size_t>(ENTRANT::_01)) = entrant01; }
    void SetEntrant02Ref(Entrant* entrant02) { entrants.at(static_cast<size_t>(ENTRANT::_02)) = entrant02; }
    void SetCamera(TechSharkLib::Camera* camera) { this->camera = camera; }

    void AddGuideObserver(Observer<OperateGuide::STATE>* observer) { guideSubject.AddObserver(observer); }
    void NotyfyToGuide(OperateGuide::STATE state) { guideSubject.Notify(state); }
    void AddBackgroundsObserver(Observer<Backgrounds::No>* observer) { backgroundsSubject.AddObserver(observer); }
    void NotyfyToBackgrounds(BG_NO state) { backgroundsSubject.Notify(static_cast<Backgrounds::No>(state)); }

};

#endif // !INCLUDED_GAMEMODE_H