#include "engine/engine.h"
#include "game/game.h"

#include "basemapmodel.h"
#include "shared/entities/entityfactory.h"

namespace entities {
namespace classes {

BaseMapModel::BaseMapModel() : BaseDynamicEntity() {
    // State (Alive)
    state = CS_ALIVE;

    // Internal engine type.
	et_type = MAPMODEL;

    // Internal engine entity type.
    ent_type = ENT_INANIMATE;

    // And our game entity type.
    game_type = GAMEENTITY;

    // Ensure it has a physstate, think this is the best.
    physstate = PHYS_FALL;

    // Last but not least, set our collide method.
    collidetype = COLLIDE_TRI;

    setName("model");
}

BaseMapModel::BaseMapModel(const std::string &filename) : BaseMapModel() {
    // Load it in here.
    if (filename.empty())
        preloadMapModel(getAttribute("model"));
    else
        preloadMapModel(filename);
}

BaseMapModel::~BaseMapModel() {

}

void BaseMapModel::preload() {
    if (attributes.find("model") != attributes.end())
        preloadMapModel(getAttribute("model"));
}

void BaseMapModel::think() {

}

void BaseMapModel::render() {

}

void BaseMapModel::onAttributeSet(const std::string &key, const std::string &value) {
    if (key == "model") {
        preloadMapModel(value);
    }
}

void BaseMapModel::onAnimate(int &anim, int &basetime) {
    conoutf("OnAnimate: %i %i", anim, basetime);
}

void BaseMapModel::preloadMapModel(const std::string &filename) {
    // In case this is the first time, a filename will be supplied for sure.
    if (!filename.empty()) {
        mmi = mapmodels.add();
        mmi.m = loadmodel(filename.c_str(), -1, true);
        mmi.collide = loadmodel(filename.c_str(), -1, true);
        copycubestr(mmi.name, filename.c_str());

        // Copy into mmi.
//		mmi = loadmodelinfo(filename.c_str(), this);
		//mapmodels.add();
        model_idx = mapmodels.length() + 1;
    } else {
        preloadMapModel("world/box");
    }
}

CoreEntity* BaseMapModel::factory(){
	return new BaseMapModel();
}

ADD_ENTITY_TO_FACTORY(BaseMapModel, base_map_model);

} // classes
} // entities
