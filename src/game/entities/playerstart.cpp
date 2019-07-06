#include "../game.h"
//#include "baseentity.h"
#include "playerstart.h"

namespace entities {
namespace classes {

PlayerStart::PlayerStart() : BaseEntity() {

}

PlayerStart::~PlayerStart() {

}

void PlayerStart::preload() {
    conoutf("%s", "Preloading playerstart entity");
}

void PlayerStart::think() {
    conoutf("%s", "Printf boy kijkt ff of deze functie wel opgeroepen word");
    moveplayer(this, 10, true);
}

} // classes
} // entities
