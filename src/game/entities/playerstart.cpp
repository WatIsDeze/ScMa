#include "../game.h"
#include "playerstart.h"

namespace entities {
namespace classes {

PlayerStart::PlayerStart() : BaseEntity() {
    et_type = ET_PLAYERSTART;
    ent_type = ENT_INANIMATE;
    game_type = PLAYERSTART;
}

PlayerStart::~PlayerStart() {

}

void PlayerStart::preload() {
    conoutf("%s", "Preloading playerstart entity");
}

void PlayerStart::think() {

}

void PlayerStart::render() {

}

void PlayerStart::reset() {
    BaseEntity::reset();
    // Reset.
    setName("playerstart");
    setClassName("PlayerStart");
}

} // classes
} // entities
