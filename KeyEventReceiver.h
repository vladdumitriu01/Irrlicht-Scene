#include <irrlicht.h>
using namespace irr;

//Adapted from Rytz 2008. http://irrlicht.sourceforge.net/forum/viewtopic.php?t=29139&view=next&sid=3fa2a975c8abd1ccff1778deb852ac90

class KeyEventReceiver : public IEventReceiver
{
public:

    // -------------------------------------
    // KeyEventReceiver Method Declarations
    // -------------------------------------
   KeyEventReceiver();
   virtual bool IsKeyDown(EKEY_CODE) const;
   virtual bool OnEvent(const SEvent&);

private:
   bool KeyIsDown[KEY_KEY_CODES_COUNT];
};