#include "../game.h"
#include "../engine/engine.h"
#include "door.h"
#include "basemapmodelentity.h"

namespace entities {
namespace classes {

Door::Door() : entities::classes::BaseMapModelEntity("world/door_redeclipse") {
    // Doors animate, makes sense.
    flags |= EF_ANIM;
}

Door::~Door() {

}

void Door::preload() {}
void Door::think() {}
void Door::render() {}

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

} // classes
} // entities
