#include"Factory.h"
ClassFactory::ClassFactory()
{
}

void* ClassFactory::GetClassByName(string className) {
	map<string, CreateObject>::const_iterator iter;
	iter = m_class_compare_.find(className);
	if (iter == m_class_compare_.end())
		return NULL;
	else
		return iter->second();
}

void ClassFactory::RegistClass(string name, CreateObject method) {
	m_class_compare_.insert(pair<string, CreateObject>(name, method));
}

ClassFactory& ClassFactory::GetInstance() {
	static ClassFactory sLo_factory;
	return sLo_factory;
}

ClassFactory::~ClassFactory()
{
}

RegisterAction::RegisterAction(string className, CreateObject ptrCreateFn)
{
	ClassFactory::GetInstance().RegistClass(className, ptrCreateFn);
}

RegisterAction::~RegisterAction()
{
}