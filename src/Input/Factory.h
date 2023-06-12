#pragma once
#include <map>
#include <iostream>
#include <string>

// 类注册实例化类宏定义
#define REGISTER(className) 											\
	className* objectCreator##className(){     							\
        return new className;                                         	\
    }                                                                  	\
    RegisterAction g_creatorRegister##className(                        \
		#className,(CreateObject)objectCreator##className)

using namespace std;

typedef void* (*CreateObject)(void);

// 类注册工厂类
class ClassFactory {
private:
	ClassFactory(); //构造函数私有化
	~ClassFactory();

	// 类注册表
	map<string, CreateObject> m_classMap;

public:
	// 通过类名获取类指针
	void* getClassByName(string className);
	// 注册进map
	void registClass(string name, CreateObject method);
	// 通过工厂类实例
	static ClassFactory& getInstance();
};

// 类注册实例化类
class RegisterAction {
public:
	RegisterAction(string className, CreateObject ptrCreateFn);
	~RegisterAction();
};