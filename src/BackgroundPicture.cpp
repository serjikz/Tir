#include "stdafx.h"
#include "BackgroundPicture.h"

BackgroundPicture::BackgroundPicture() {
	_tex = Core::resourceManager.Get<Render::Texture>("Background");
};
void BackgroundPicture::draw() {
	_tex->Draw();
}