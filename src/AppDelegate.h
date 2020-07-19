#ifndef __APPDELEGATE_H__
#define __APPDELEGATE_H__

#pragma once

class AppDelegate : public Core::EngineAppDelegate {
public:
	AppDelegate();

	virtual void GameContentSize(int deviceWidth, int deviceHeight, int &width, int &height) override;
	virtual void ScreenMode(DeviceMode &mode) override;

	virtual void RegisterTypes() override;

	virtual void LoadResources() override;
	virtual void OnResourceLoaded() override;

	virtual void OnPostDraw() override;
};

#endif // __APPDELEGATE_H__
