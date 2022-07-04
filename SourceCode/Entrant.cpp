//------< include >-----------------------------------------------------------------------
#include "Entrant.h"

//========================================================================================
// 
//      Entrant
// 
//========================================================================================

//------------------------------------------------------------------------------
// member function
//------------------------------------------------------------------------------

void Entrant::Setup()
{
    keyLeft     = (1 << description.keyLeft);
    keyRight    = (1 << description.keyRight);
    keyUp       = (1 << description.keyUp);
    keyDown     = (1 << description.keyDown);
}

void Entrant::Deinit()
{
    description = {};
    keyLeft     = NULL;
    keyRight    = NULL;
    keyUp       = NULL;
    keyDown     = NULL;
}