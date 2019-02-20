//KeyEventReceiver Method Definitions
// -----------------------------------
//Adapted from Rytz 2008. http://irrlicht.sourceforge.net/forum/viewtopic.php?t=29139&view=next&sid=3fa2a975c8abd1ccff1778deb852ac90

#include "./KeyEventReceiver.h"

KeyEventReceiver::KeyEventReceiver()
{
   for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
      KeyIsDown[i] = false;
}


bool KeyEventReceiver::OnEvent(const SEvent& event)
{
   if (event.EventType == EET_KEY_INPUT_EVENT)
      KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

   return false;
}


bool KeyEventReceiver::IsKeyDown(EKEY_CODE keyCode) const
{
   return KeyIsDown[keyCode];
}
