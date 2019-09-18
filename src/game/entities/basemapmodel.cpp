#include "../game.h"
#include "../engine/engine.h"
#include "basemapmodel.h"

namespace entities {
namespace classes {

BaseMapModel::BaseMapModel(const std::string &filename) : BaseEntity() {
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
}

BaseMapModel::~BaseMapModel() {

}

void BaseMapModel::preload() {

}

void BaseMapModel::think() {
}

void BaseMapModel::render() {
}

void BaseMapModel::loadModelAttributes() {
    if (filename != "" && !filename.empty()) {
        if (attributes.find("model") != attributes.end()) {
            // Try to load the model that is saved in the attributes.
            preloadMapModel(attributes["model"]);
        } else {
            // Try to preload the model passed to the constructor.
            preloadMapModel(filename.c_str());

            // Warn our user in case the model has not been found.
            if (model_idx == -1)
                conoutf(CON_WARN, "Failed to load model: %s", filename.c_str());
        }
    } else {
        conoutf(CON_WARN, "No model filename supplied to BaseMapModel entity.");
    }
}

void BaseMapModel::preloadMapModel(const std::string &filename) {
    // Let's first preload this model.
    preloadmodel(filename.c_str());

    // Now store the map model index.
    model_idx = loadmapmodel(filename.c_str(), this);

    if (model_idx != -1) {
        // store attributes since all went well.
        attributes["model"] = filename;
        attributes["model_idx"] = model_idx;
    }
}

} // classes
} // entities
