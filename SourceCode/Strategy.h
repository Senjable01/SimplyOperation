#pragma once

//------< include >-----------------------------------------------------------------------
#include <memory>

//========================================================================================
// 
//      Behavior
// 
//========================================================================================
template<typename Subject>
class Behavior
{
private:
    virtual void Run(Subject*) = 0;

public:
    virtual ~Behavior() {}

    void operator()(Subject* subject) { Run(subject); }

};

//------< using >-------------------------------------------------------------------------

template<typename Arg>
using Strategy = std::unique_ptr<Behavior<Arg>>;