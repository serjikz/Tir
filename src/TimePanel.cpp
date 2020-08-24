#include "stdafx.h"
#include "TimePanel.h"

TimePanel::TimePanel(rapidxml::xml_node<>* settings)
	:Panel(settings)
{
	
}

void TimePanel::draw() {
	Panel::draw();
}
