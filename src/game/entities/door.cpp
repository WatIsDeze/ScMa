#include "../engine/engine.h"
#include "../game.h"
#include "ents.h"
#include "basemapmodel.h"
#include "door.h"
#include "shared/entities/entityfactory.h"

namespace entities {
namespace classes {


Door::Door() :  entities::classes::BaseMapModel("world/door") {
    state = CS_ALIVE;
    et_type = ET_GAMESPECIFIC;
    ent_type = ENT_INANIMATE;
    game_type = GAMEENTITY;
    collidetype = COLLIDE_OBB;
    physstate = PHYS_FLOOR;

    // Reset.
	setName("Door");
	setClassName("door");

    // Doors animate, makes sense.
    flags |= entities::EntityFlags::EF_ANIM;
}

Door::~Door() {

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
}
void Door::onAttributeSet(const std::string &key, const std::string &value) {
    // Call parent class onattributeset so it'll take its keys into consideration.
    BaseMapModel::onAttributeSet(key, value);
}

bool Door::onTrigger(entities::classes::BaseEntity *otherEnt, const vec &dir) {
    if (otherEnt == NULL) {
        return false;
    }
    conoutf("%s %s %s %f %f %f", "Door triggered by entity: ", otherEnt->classname.c_str(),
            "from Vector Direction: ", dir.x, dir.y, dir.z);
    return true;
}

bool Door::onTouch(entities::classes::BaseEntity *otherEnt, const vec &dir) {
    if (otherEnt == NULL) {
        return false;
    }
    conoutf("%s %s %s %f %f %f", "Door touched by entity: ", otherEnt->classname.c_str(),
            "from Vector Direction: ", dir.x, dir.y, dir.z);
    return true;
}

CoreEntity* Door::factory(){
	return new Door();
}

ENTITY_FACTORY(Door);

} // classes
} // entities
