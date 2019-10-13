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

			float yaw;
		protected:
			//Serialization
			nlohmann::json toJson();
			void fromJson(const nlohmann::json& document);

        private:
        };
    } // classes
} // entities

