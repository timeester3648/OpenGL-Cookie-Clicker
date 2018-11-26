#pragma once

#include "../objects/TexturedModel.h"

struct TexturedModelCompare {

	public:

		bool operator() (TexturedModel* t1, TexturedModel* t2) const {

			return ((t1->getRawModel().getVaoID() < t2->getRawModel().getVaoID()) || (t1->getTexture().getID() < t2->getTexture().getID()));

		}

		bool operator() (TexturedModel t1, TexturedModel t2) const {

			return ((t1.getRawModel().getVaoID() < t2.getRawModel().getVaoID()) || (t1.getTexture().getID() < t2.getTexture().getID()));

		}

};