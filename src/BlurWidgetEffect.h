#pragma once

#include "Background.h"
#include "Tank.h"

class BlurWidgetEffect
{
private:	
	Render::Target* _targetX;
	Render::Target* _targetY;
	Render::ShaderProgramPtr _blurShaderX;
	Render::ShaderProgramPtr _blurShaderY;
	
public:
	BlurWidgetEffect();
	typedef boost::shared_ptr<BlurWidgetEffect> HardPtr;
	virtual void draw(const Background::HardPtr bkg, const std::vector <Enemy::HardPtr>& enemies, const Tank::HardPtr tank);
	virtual void update(float dt);
};