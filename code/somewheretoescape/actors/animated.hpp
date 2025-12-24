#pragma once

#include <t3d/t3danim.h>
#include "../physics/physics.hpp"
#include "models/complex.hpp"

class Animated {
public:
	Animated(Physics& physics)
		: _physics(physics) {
	}
	~Animated() {
	}
	ComplexBody createAnimatedBody(T3DModel *model, T3DVec3 scale, T3DVec3 startingPosition, T3DVec3 startingRotation,  joypad_port_t controlPort);
	void updateAnimatedBodyControls(ComplexBody *body);
	void render(ComplexBody *body, float deltaTime);
	void drawAnimatedBody(ComplexBody *body);
	void deleteAnimatedBody(ComplexBody *body);

	ComplexBody escapePlayer1;
	//ComplexBody escapePlayer2;
	//ComplexBody escapePlayer3;
	//ComplexBody enemyPlayer4;
private:
	Physics& _physics;
	T3DVec3 defaultSize = (T3DVec3){{ 9.0f, 9.0f, 9.0f}};
};
