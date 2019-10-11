#pragma once
#include "shared/entities/baseentity.h"

namespace entities {
    namespace classes {
        class PlayerStart : public BaseEntity {
			ENTITY_FACTORY_IMPL(PlayerStart);
        public:
            PlayerStart();
            virtual ~PlayerStart();

            void preload();
            void think();
            void render();

            void reset();

            //
            // Entity Factory functions.
            //
            static CoreEntity* factory();

			//Serialization
			virtual void toJson(nlohmann::json& document);
			virtual void fromJson(const nlohmann::json& document);

			float yaw;
        private:
        };
    } // classes
} // entities

