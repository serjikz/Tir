#pragma once
class InterfaceObjVisitor
{

public:
	//virtual void visitScorePanel(ScorePanel::HardPtr panel) = 0;
	typedef boost::shared_ptr<InterfaceObjVisitor> HardPtr;
};

class ScorePanelVisitor : public InterfaceObjVisitor {
private:
	std::string _msg;
public:
	ScorePanelVisitor(const std::string& msg)
		: _msg(msg)
	{}

	//virtual void visitScorePanel(ScorePanel::HardPtr panel) {
	//	panel->setStatisticsMsg(_msg);
	//}
};
