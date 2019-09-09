#include "../game.h"
#include "door.h"

namespace entities {
namespace classes {

Door::Door() : BaseEntity() {
    state = CS_ALIVE;
    type = ENT_INANIMATE;
}

Door::~Door() {

}

void Door::preload() {
    //conoutf("%s", "Preloading door entity");
    preloadmodel("world/door");

    // Preload door model.
    setbbfrommodel(this, "world/door");
}

void Door::think() {
    //conoutf("%s")
    //moveplayer(this, 1, true);
}

void Door::render() {

    //rendermodel("world/door", ANIM_ALL, o, 0, 0, 0);
    rendermodel("world/door", ANIM_MAPMODEL|ANIM_LOOP, o, yaw, 0, 0, MDL_CULL_VFC | MDL_CULL_DIST | MDL_CULL_OCCLUDED, this);
}

} // classes
} // entities
