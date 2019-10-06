#include "../game.h"
#include "player.h"

namespace entities {
namespace classes {

Player::Player() : BaseEntity() {
    type = ENT_PLAYER;
}

Player::~Player() {

}

void Player::preload() {
    conoutf("%s", "Preloading playerstart entity");
}

void Player::think() {
    moveplayer(this, 10, true);
}

void Player::render() {
    // TODO: Fix this.
    //if(isthirdperson()) renderclient(player1, "ogro", NULL, 0, ANIM_ATTACK1, 300, player1->lastaction, player1->lastpain);
}

} // classes
} // entities


// >>>>>>>>>> SCRIPTBIND >>>>>>>>>>>>>> //
// <<<<<<<<<< SCRIPTBIND <<<<<<<<<<<<<< //
