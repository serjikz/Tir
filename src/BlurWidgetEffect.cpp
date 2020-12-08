#include "stdafx.h"

BlurWidgetEffect::BlurWidgetEffect()

{
	_targetX = Render::device.CreateRenderTarget(1024, 1024);
	_targetY = Render::device.CreateRenderTarget(1024, 1024);
	_blurShaderX = Core::resourceManager.Get<Render::ShaderProgram>("blurX");
	_blurShaderY = Core::resourceManager.Get<Render::ShaderProgram>("blurY");
}

void BlurWidgetEffect::draw(const Background::HardPtr bkg, const EnemiesController::HardPtr enemiesController, const Tank::HardPtr tank) {
	Render::device.BeginRenderTo(_targetX);
	bkg->draw();
	enemiesController->draw();
	tank->draw();
	Render::device.EndRenderTo();
	Render::device.BeginRenderTo(_targetY);
	_blurShaderX->Bind();
	_targetX->Draw(FPoint(0.0, 0.0));
	_blurShaderX->Unbind();
	Render::device.EndRenderTo();
	_blurShaderY->Bind();
	_targetY->Draw(FPoint(0.0, 0.0));
	_blurShaderY->Unbind();
}