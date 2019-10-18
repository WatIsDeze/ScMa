#include "playerstart.h"

namespace entities {
namespace classes {

PlayerStart::PlayerStart() {
	et_type = ET_GAMESPECIFIC;
	ent_type = ENT_INANIMATE;
	game_type = PLAYERSTART;
}

void PlayerStart::preload() {

}

void PlayerStart::think() {

}

void PlayerStart::render() {

}

void PlayerStart::reset() {

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
