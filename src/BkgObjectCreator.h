#pragma once

// Базоый класс создателя элемента фона (Фабричный метод)
class BkgObjectCreator
{
private:
	BkgObject::HardPtr _obj;
protected:
	virtual BkgObject::HardPtr createObject() = 0;
public:
	BkgObjectCreator() {};
	BkgObject::HardPtr getObject() {
		if (!_obj) {
			_obj = createObject();
		}
		return _obj;
	};
	typedef boost::shared_ptr<BkgObjectCreator> HardPtr;
};