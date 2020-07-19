#include "stdafx.h"
#include "Tank.h"

Tank::Tank() {
	_tank= Core::resourceManager.Get<Render::Texture>("Tank");
};


