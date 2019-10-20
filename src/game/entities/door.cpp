#include "../engine/engine.h"
#include "../game.h"
#include "ents.h"
#include "basemapmodel.h"
#include "door.h"
#include "shared/entities/entityfactory.h"

namespace entities {
namespace classes {


Door::Door() :  entities::classes::BaseMapModel("world/door") {
    // Reset.
    setName("Door");

    // Setup the door its states.
    state = CS_ALIVE;
    et_type = ET_GAMESPECIFIC;
    ent_type = ENT_INANIMATE;
    game_type = GAMEENTITY;
    collidetype = COLLIDE_OBB;
    physstate = PHYS_FLOOR;

    // Doors animate, makes sense.
    flags |= entities::EntityFlags::EF_ANIM;
    flags |= entities::EntityFlags::EF_SHADOWMESH;
    flags |= entities::EntityFlags::EF_RENDER;
    flags |= entities::EntityFlags::EF_SPAWNED;
}

void Door::preload() {

}
void Door::think() {

}
void Door::render() {
    // Ensure it renders.
    BaseMapModel::render();
}

void Door::onAnimate(int &anim, int &basetime) {
    conoutf("OnAnimate: %i %i", anim, basetime);
    anim = ANIM_MAPMODEL | ANIM_ALL | ANIM_REVERSE;
}

bool Door::onTrigger(const entities::classes::CoreEntity *otherEnt, const vec &dir) {
    if (otherEnt == nullptr) {
        return false;
    }
    conoutf("%s %s %s %f %f %f", "Door triggered by entity: ", otherEnt->classname.c_str(),
            "from Vector Direction: ", dir.x, dir.y, dir.z);
    return true;
}

bool Door::onTouch(const entities::classes::CoreEntity *otherEnt, const vec &dir) {
    if (otherEnt == nullptr) {
        return false;
    }
    conoutf("%s %s %s %f %f %f", "Door touched by entity: ", otherEnt->classname.c_str(),
            "from Vector Direction: ", dir.x, dir.y, dir.z);
    return true;
}


} // classes
} // entities

ADD_ENTITY_TO_FACTORY_SERIALIZED(Door, "door", BaseMapModel);
