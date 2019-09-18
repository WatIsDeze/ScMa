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

    // Load it in here.
    preloadMapModel("world/door_redeclipse");
}

BaseMapModel::~BaseMapModel() {

}

void BaseMapModel::preload() {

}

void BaseMapModel::think() {
}

void BaseMapModel::render() {
}

void BaseMapModel::preloadMapModel(const std::string &filename) {
    // In case this is the first time, a filename will be supplied for sure.
    if (!filename.empty()) {
        // Let's first preload this model.
        preloadmodel(filename.c_str());

        // Now store the map model index.
        model_idx = loadmapmodel(filename.c_str(), this);

        // We have found a model index, so all loading went well.
        if (model_idx > -1) {
            // store attributes since all went well.
            attributes["model"] = filename;
            attributes["model_idx"] = std::to_string(model_idx);
        }
    } else {
        std::string filename = attributes["model"];

        // Load in our model.
        preloadmodel(filename.c_str());

        // Store map model index.
        model_idx = loadmapmodel(filename.c_str(), this);

         // store attributes since all went well.
        if (model_idx > -1) {
            // store attributes since all went well.
            attributes["model_idx"] = std::to_string(model_idx);
        }
    }
}

} // classes
} // entities
