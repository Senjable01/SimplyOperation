#pragma once

//------< include >-----------------------------------------------------------------------
#include <memory>

//========================================================================================
// 
//      Behavior
// 
//========================================================================================
template<typename Subject>
class Strategy
{
private:
    virtual void Run(Subject*) = 0;

public:
    virtual ~Strategy() {}

    void operator()(Subject* subject) { Run(subject); };

};