#include "../game.h"
#include "../engine/engine.h"
#include "basemapmodelentity.h"

namespace entities {
namespace classes {

BaseMapModelEntity::BaseMapModelEntity(const std::string &filename) : BaseEntity() {
    // State (Alive)
    state = CS_ALIVE;

    // Internal engine type.
    et_type = ET_MAPMODEL;

    // Internal engine entity type.
    ent_type = ENT_INANIMATE;

    // And our game entity type.
    game_type = GAMEENTITY;

    // Ensure it has a physstate, think this is the best.
    physstate = PHYS_FALL;

    // Last but not least, set our collide method.
    collidetype = COLLIDE_TRI;

    if (attributes.find("model") != attributes.end()) {
        // Try to load the model that is saved in the attributes.
        preloadMapModel(attributes["model"]);
    } else {
        // Try to preload the model passed to the constructor.
        preloadMapModel(filename.c_str());

        // Warn our user in case the model has not been found.
        if (model_idx == -1) {
            conoutf(CON_WARN, "Failed to load model: %s", filename.c_str());
        } else {
            attributes["model"] = filename;
        }
    }
}

BaseMapModelEntity::~BaseMapModelEntity() {

}

void BaseMapModelEntity::preload() {
}

void BaseMapModelEntity::think() {
}

void BaseMapModelEntity::render() {
}

void BaseMapModelEntity::preloadMapModel(const std::string &filename) {
    // Let's first preload this model.
    preloadmodel(filename.c_str());

    // Now store the map model index.
    model_idx = loadmapmodel(filename.c_str(), this);
}

} // classes
} // entities
