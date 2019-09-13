#include "../game.h"
#include "../engine/engine.h"
#include "door.h"
#include "basemapmodelentity.h"

namespace entities {
namespace classes {

Door::Door() : entities::classes::BaseMapModelEntity() {
    state = CS_ALIVE;
    ent_type = ENT_INANIMATE;
    collidetype = COLLIDE_TRI;

    conoutf("%s", "Preloading door entity");

    if (attributes.find("model") != attributes.end()) {
        preloadMapModel(attributes["model"]);
    } else {
        preloadMapModel("world/door");
        attributes["model"] = std::string("world/door");
    }

    conoutf("%s", attributes["model"].c_str());
}

Door::~Door() {

}

void Door::preload() {

}

void Door::think() {
    //conoutf("%s")
    //moveplayer(this, 1, true);
}

void Door::render() {
    //int anim = ANIM_MAPMODEL|ANIM_LOOP, basetime = 0;
    //if(e.flags&EF_ANIM) entities::animatemapmodel(e, anim, basetime);
    //rendermapmodel(model_idx, ANIM_MAPMODEL|ANIM_LOOP, o, attr2, attr3, attr4, MDL_CULL_VFC | MDL_CULL_DIST, 0, attr5 > 0 ? attr5/100.0f : 1.0f);
    //rendermapmodel(model_idx, ANIM_MAPMODE,)
    //rendermapmodel(model_idx, ANIM_MAPMODEL|ANIM_LOOP, o, 0, 0, 1, MDL_CULL, 1, 1.0f);
    //rendermodel("world/door", ANIM_ALL, o, 0, 0, 0);
    //rendermodel("world/door", ANIM_MAPMODEL|ANIM_LOOP, o, yaw, 0, 0, MDL_CULL_VFC | MDL_CULL_DIST | MDL_CULL_OCCLUDED, this);
}

} // classes
} // entities
