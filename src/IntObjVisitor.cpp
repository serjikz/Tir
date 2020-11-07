#pragma once
#include "stdafx.h"

void ScorePanelMsgVisitor::visitScorePanel(ScorePanel* panel) {
	panel->setStatisticsMsg(_msg);
}

void TimePanelVisitor::visitTimePanel(TimePanel* panel) {
	_t = panel->getTime();
}

int TimePanelVisitor::getTime() {
	return _t;
}

void MissilesPanelVisitor::visitMissilesPanel(MissilesPanel* panel) {
	panel->decreaseMissiles();
}

void ScorePanelVisitorMouseMove::visitScorePanel(ScorePanel* panel) {
	panel->mouseMove(_mousePos);
}

void ScorePanelVisitorMouseDown::visitScorePanel(ScorePanel* panel) {
	panel->mouseDown(_mousePos);
}