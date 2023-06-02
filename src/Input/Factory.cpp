#include"Factory.h"
ClassFactory::ClassFactory()
{
}

void* ClassFactory::getClassByName(string className) {
	map<string, CreateObject>::const_iterator iter;
	iter = m_classMap.find(className);
	if (iter == m_classMap.end())
		return NULL;
	else
		return iter->second();
}

void ClassFactory::registClass(string name, CreateObject method) {
	m_classMap.insert(pair<string, CreateObject>(name, method));
}

ClassFactory& ClassFactory::getInstance() {
	static ClassFactory sLo_factory;
	return sLo_factory;
}

ClassFactory::~ClassFactory()
{
}

RegisterAction::RegisterAction(string className, CreateObject ptrCreateFn)
{
	ClassFactory::getInstance().registClass(className, ptrCreateFn);
}

RegisterAction::~RegisterAction()
{
}