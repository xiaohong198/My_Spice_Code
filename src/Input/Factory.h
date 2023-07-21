#pragma once
#include <map>
#include <iostream>
#include <string>

// 类注册实例化类宏定义
#define REGISTER(ClassName) 											\
	ClassName* ObjectCreator##ClassName(){     							\
        return new ClassName;                                         	\
    }                                                                  	\
    RegisterAction G_CreatorRegister##ClassName(                        \
		#ClassName,(CreateObject)ObjectCreator##ClassName)

using namespace std;

typedef void* (*CreateObject)(void);

// 类注册工厂类
class ClassFactory {
private:
	ClassFactory(); //构造函数私有化
	~ClassFactory();

	// 类注册表
	map<string, CreateObject> m_class_compare_;

public:
	// 通过类名获取类指针
	void* GetClassByName(string);
	// 注册进map
	void RegistClass(string, CreateObject);
	// 通过工厂类实例
	static ClassFactory& GetInstance();
};

// 类注册实例化类
class RegisterAction {
public:
	RegisterAction(string, CreateObject);
	~RegisterAction();
};