#include "../game.h"
#include "../engine/engine.h"
#include "ents.h"
#include "basemodel.h"

namespace entities {
namespace classes {

BaseModel::BaseModel() : entities::classes::BaseEntity() {
    state = CS_ALIVE;

    // Internal engine type.
    et_type = ET_MAPMODEL;

    // Internal engine entity type.
    ent_type = ENT_INANIMATE;

    // And our game entity type.
    game_type = GAMEENTITY;

    // Last but not least, set our collide method.
    collidetype = COLLIDE_TRI;
}

BaseModel::BaseModel(const std::string &filename) : BaseModel() {
    state = CS_ALIVE;

    // Internal engine type.
    et_type = ET_MAPMODEL;

    // Internal engine entity type.
    ent_type = ENT_INANIMATE;

    // And our game entity type.
    game_type = GAMEENTITY;

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

BaseModel::~BaseModel() {

}

void BaseModel::preload() {

}

void BaseModel::think() {
}

void BaseModel::render() {

}

void BaseModel::onAttributeSet(const std::string &key, const std::string &value) {
    if (key == "model")
        preloadMapModel(value);
}

void BaseModel::onAnimate(int &anim, int &basetime) {
    conoutf("OnAnimate: %i %i", anim, basetime);
}

void BaseModel::preloadMapModel(const std::string &filename) {
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
            attributes["model"] = filename;
            attributes["model_idx"] = std::to_string(model_idx);
        }
    }
}

} // classes
} // entities
