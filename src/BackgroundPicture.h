#pragma once
#include "BkgObject.h"

class BackgroundPicture : public BkgObject
{
private:
	
public:
	BackgroundPicture() {
		_tex = Core::resourceManager.Get<Render::Texture>("Background");
	};
	virtual void draw() {
		_tex->Draw();
	}

	virtual void update(float dt) {
		
	}
};