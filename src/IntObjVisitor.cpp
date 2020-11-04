#pragma once
#include "stdafx.h"

void ScorePanelVisitor::visitScorePanel(ScorePanel* panel) {
	panel->setStatisticsMsg(_msg);
}