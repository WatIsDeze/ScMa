#include "../game.h"
#include "player.h"

namespace entities {
namespace classes {

Player::Player() : BaseEntity() {
    state = CS_ALIVE;
    et_type = ET_GAMESPECIFIC;
    ent_type = ENT_PLAYER;
    game_type = GAMEENTITY;
    collidetype = COLLIDE_OBB;
}

Player::~Player() {

}

void Player::preload() {
    conoutf("%s", "Preloading player entity");
    preloadmodel("player/bones");
}

void Player::think() {
    //crouchplayer(this, 10, true);
    moveplayer(this, 10, true);
}

enum
{
    ANIM_DEAD = ANIM_GAMESPECIFIC, ANIM_DYING,
    ANIM_IDLE, ANIM_RUN_N, ANIM_RUN_NE, ANIM_RUN_E, ANIM_RUN_SE, ANIM_RUN_S, ANIM_RUN_SW, ANIM_RUN_W, ANIM_RUN_NW,
    ANIM_JUMP, ANIM_JUMP_N, ANIM_JUMP_NE, ANIM_JUMP_E, ANIM_JUMP_SE, ANIM_JUMP_S, ANIM_JUMP_SW, ANIM_JUMP_W, ANIM_JUMP_NW,
    ANIM_SINK, ANIM_SWIM,
    ANIM_CROUCH, ANIM_CROUCH_N, ANIM_CROUCH_NE, ANIM_CROUCH_E, ANIM_CROUCH_SE, ANIM_CROUCH_S, ANIM_CROUCH_SW, ANIM_CROUCH_W, ANIM_CROUCH_NW,
    ANIM_CROUCH_JUMP, ANIM_CROUCH_JUMP_N, ANIM_CROUCH_JUMP_NE, ANIM_CROUCH_JUMP_E, ANIM_CROUCH_JUMP_SE, ANIM_CROUCH_JUMP_S, ANIM_CROUCH_JUMP_SW, ANIM_CROUCH_JUMP_W, ANIM_CROUCH_JUMP_NW,
    ANIM_CROUCH_SINK, ANIM_CROUCH_SWIM,
    ANIM_SHOOT, ANIM_MELEE,
    ANIM_PAIN,
    ANIM_EDIT, ANIM_LAG, ANIM_TAUNT, ANIM_WIN, ANIM_LOSE,
    ANIM_GUN_IDLE, ANIM_GUN_SHOOT, ANIM_GUN_MELEE,
    ANIM_VWEP_IDLE, ANIM_VWEP_SHOOT, ANIM_VWEP_MELEE,
    NUMANIMS
};

void Player::render() {
    //if (isthirdperson()) {
        // Calculate the position.
        vec pos = o;
        pos.z -= eyeheight;
        rendermodel("player/bones", ANIM_IDLE, pos, 0, 0, 0);
    //}
}

bool Player::onTrigger(entities::classes::BaseEntity *otherEnt, const vec &dir) {
    if (otherEnt != NULL) {
        conoutf("%s %s %s %f %f %f", "Player triggered by entity: ", otherEnt->classname.c_str(),
            "from Vector Direction: ", dir.x, dir.y, dir.z);
            return true;
    } else {
        return false;
    }
}

bool Player::onTouch(entities::classes::BaseEntity *otherEnt, const vec &dir) {
     if (otherEnt != NULL) {
        conoutf("%s %s %s %f %f %f", "Player touched by entity: ", otherEnt->classname.c_str(),
            "from Vector Direction: ", dir.x, dir.y, dir.z);
        return true;
    } else {
        return false;
    }
}

void Player::respawn() {
    // First respawn base entity.
    dynent::reset();

    // Set spawned state.
    setspawned(true);

    // Edit mode or in-game?
    if(editmode)
        state = CS_EDITING;
    else if(state != CS_SPECTATOR)
        state = CS_ALIVE;
}

} // classes
} // entities
