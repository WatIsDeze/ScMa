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
    conoutf("%s", "Preloading player entity");
    preloadmodel("player_azul");
}

void Player::think() {
    moveplayer(this, 10, true);
}

void Player::render() {
    // TODO: Fix this.
    //if(isthirdperson())
    //    renderclient(game::player1, "ogro", NULL, 0, ANIM_ATTACK1, 300, player1->lastaction, player1->lastpain);
    rendermodel("player_azul", ANIM_INDEX | 3, o, 0, 0, 0, MDL_CULL_VFC | MDL_CULL_DIST | MDL_CULL_OCCLUDED, 0, 0, 0, 0, 1, vec4(1, 1, 1, 1));
}

} // classes
} // entities
