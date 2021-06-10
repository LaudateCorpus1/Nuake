#pragma once
#include <string>
#include <map>
struct WrenVM;
class ScriptModule
{
private:
	std::map<std::string, void*> Methods = std::map<std::string, void*>();

	std::string WrenAPI;
public:
	std::string ModuleName;
	virtual void RegisterModule(WrenVM*) = 0;
	virtual std::string GetModuleName() = 0;

	void RegisterMethod(const std::string& signature, void* ptr)
	{
		Methods[signature] = ptr;
	}

	void* GetMethodPointer(const std::string& signature)
	{
		return Methods[signature];
	}

	
};