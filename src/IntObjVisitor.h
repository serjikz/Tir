#pragma once
class ScorePanel;
class TimePanel;
class MissilesPanel;

// Базовый класс - обработчик событий элементов интерфейса (Посетитель)
class InterfaceObjVisitor
{

public:
	virtual void visitScorePanel(ScorePanel* panel) {};
	virtual void visitTimePanel(TimePanel* panel) {};
	virtual void visitMissilesPanel(MissilesPanel* panel) {};
	typedef boost::shared_ptr<InterfaceObjVisitor> HardPtr;
};

class ScorePanelMsgVisitor : public InterfaceObjVisitor {
private:
	std::string _msg;
public:
	ScorePanelMsgVisitor(const std::string& msg)
		: _msg(msg)
	{}

	virtual void visitScorePanel(ScorePanel* panel);
	typedef boost::shared_ptr<ScorePanelMsgVisitor> HardPtr;
};

class TimePanelVisitor : public InterfaceObjVisitor {
private :
	int _t;
public:
	TimePanelVisitor()
		:_t(0)
	{}
	virtual void visitTimePanel(TimePanel* panel);
	int getTime();
	typedef boost::shared_ptr<TimePanelVisitor> HardPtr;
};

class MissilesPanelVisitor : public InterfaceObjVisitor {

public:
	virtual void visitMissilesPanel(MissilesPanel* panel);
	typedef boost::shared_ptr<MissilesPanelVisitor> HardPtr;
};

class ScorePanelVisitorMouseMove : public InterfaceObjVisitor {
private:
	IPoint _mousePos;
public:
	ScorePanelVisitorMouseMove(const IPoint& mouse_pos)
		:_mousePos(mouse_pos)
	{}
	virtual void visitScorePanel(ScorePanel* panel);
	typedef boost::shared_ptr<ScorePanelVisitorMouseMove> HardPtr;
};

class ScorePanelVisitorMouseDown : public InterfaceObjVisitor {
private:
	IPoint _mousePos;
public:
	ScorePanelVisitorMouseDown(const IPoint& mouse_pos)
		:_mousePos(mouse_pos)
	{}
	virtual void visitScorePanel(ScorePanel* panel);
	typedef boost::shared_ptr<ScorePanelVisitorMouseDown> HardPtr;
};