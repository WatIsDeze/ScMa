#include "playerstart.h"

namespace entities {
namespace classes {

PlayerStart::PlayerStart() : BaseEntity() {
	// Reset defaults.
	reset();

	// Setup specifics.
    et_type = ET_GAMESPECIFIC;
    ent_type = ENT_INANIMATE;
    game_type = PLAYERSTART;
    
    // This is a joke for Micha.
    conoutf("\f3Hey Micha! Conoutf Boy! Haha! PlayerStart constructed.");
}

PlayerStart::~PlayerStart() {

}

void PlayerStart::preload() {

}

void PlayerStart::think() {

}

void PlayerStart::render() {

}

void PlayerStart::reset() {
	// Reset Base.
    BaseEntity::reset();

	// Set names.
    setName("PlayerStart");
}

nlohmann::json PlayerStart::toJson()
{
	return {
		{"yaw", yaw}
	};
}

void PlayerStart::fromJson(const nlohmann::json& document)
{
	json_utils::tryQueryJsonVar(document, "yaw", yaw);
}

} // classes
} // entities

ADD_ENTITY_TO_FACTORY_SERIALIZED(PlayerStart, "playerstart", BaseEntity);
