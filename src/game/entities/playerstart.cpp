#include "../game.h"
#include "playerstart.h"

namespace entities {
namespace classes {

PlayerStart::PlayerStart() : BaseEntity() {
    type = ENT_PLAYER;
}

PlayerStart::~PlayerStart() {

}

void PlayerStart::preload() {
    conoutf("%s", "Preloading playerstart entity");
}

void PlayerStart::think() {
    //moveplayer(this, 10, true);
}

void PlayerStart::render() {
    // TODO: Fix this.
    //if(isthirdperson()) renderclient(player1, "ogro", NULL, 0, ANIM_ATTACK1, 300, player1->lastaction, player1->lastpain);
}

} // classes
} // entities


// >>>>>>>>>> SCRIPTBIND >>>>>>>>>>>>>> //
// <<<<<<<<<< SCRIPTBIND <<<<<<<<<<<<<< //
