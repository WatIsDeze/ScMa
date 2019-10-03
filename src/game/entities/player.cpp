#include "cube.h"
#include "game.h"
#include "ents.h"
#include "player.h"

namespace entities {
namespace classes {

Player::Player() : BaseDynamicEntity() {
    state = CS_ALIVE;
    et_type = ET_GAMESPECIFIC;
    ent_type = ENT_PLAYER;
    game_type = GAMEENTITY;
    collidetype = COLLIDE_OBB;
    physstate = PHYS_FLOOR;

    // Reset.
	setName("Player");
	setClassName("player");

    // Camera.
    camera = new entities::classes::BasePhysicalEntity();
}

Player::~Player() {
    delete camera;
}

void Player::preload() {
    // Load in our player entity model.
    conoutf("%s", "Preloading player entity");
    preloadmodel("player/bones");

    state = CS_ALIVE;
    et_type = ET_GAMESPECIFIC;
    ent_type = ENT_PLAYER;
	game_type = PLAYER;
    collidetype = COLLIDE_OBB;
	physstate = PHYS_FALL;

    // Reset.
    setName("player");
    setClassName("Player");
}

void Player::think() {
//    o.x = 512;
//    o.y = 512;
    //o.z = 512;

    //camera->o = o; //WatIsDeze: Uncomment this and camera moves??
    moveplayer(this, 10, true);
    //conoutf("Player1->o {%f, %f, %f} player1->camera->o {%f, %f, %f}", o.x, o.y, o.z, camera->o.x, camera->o.y, camera->o.z);
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
//extern void rendermodel(const char *mdl, int anim, const vec &o, float yaw, float pitch, float roll, int flags, entities::classes::BaseDynamicEntity *d, modelattach *a, int basetime, int basetime2, float size, const vec4 &color);
void Player::render() {
    if (isthirdperson()) {
        // Calculate the position.
        vec pos = o;
        pos.z -= eyeheight;
        //rendermodel("player/bones", ANIM_IDLE, pos, yaw, pitch, roll, MDL_CULL_VFC | MDL_CULL_DIST | MDL_CULL_OCCLUDED, NULL, NULL, 1, 1, 1, vec4(1, 1, 1, 1));
        /*vec4 color (0.5f, 0.5f, 0.5f, 1.0f);
        float fade = 1;
        int basetime = 1;*/
        rendermodel("player/bones", ANIM_IDLE, pos, yaw, pitch, 0, MDL_CULL_VFC | MDL_CULL_DIST | MDL_CULL_OCCLUDED);
    }
}

bool Player::onTrigger(entities::classes::BaseEntity *otherEnt, const vec &dir) {
    if (otherEnt != NULL) {
        conoutf("%s '%s' %s %s %s %f %f %f", "Player: ", name.c_str(), " triggered by entity: ", otherEnt->classname.c_str(),
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

void Player::reset() {
    // Reset.
    setName("player");
	setClassName("playerentity");
}

void Player::respawn() {
    // First respawn base entity.
    //BaseDynamicEntity::reset();

    // Set spawned state.
    setspawned(true);

    // Edit mode or in-game?
    if(editmode)
        state = CS_EDITING;
    else
        state = CS_ALIVE;
}

} // classes
} // entities
