﻿#include "ProxyMapManager.h"
#include <fstream>
#include "json/json.h"

ProxyMapManager* ProxyMapManager::_instance = nullptr;

ProxyMapManager * ProxyMapManager::instance()
{
	if (_instance == nullptr)
	{
		_instance = new ProxyMapManager();
	}
	return _instance;
}

ProxyMapManager::ProxyMapManager()
{
    load();
}

std::string ProxyMapManager::hash(int uid)
{
	int key = uid % _map.size();
	std::map<char, std::string>::iterator it = _map.begin();
	for (int i = 0; i < key ; ++i, ++it);
    std::string host =  it->second;
	return host;
}

void ProxyMapManager::update(char key, std::string proxy)
{
	_map[key] = proxy;
}

void ProxyMapManager::remove(char key)
{
	std::map<char, std::string>::iterator it = _map.find(key);
	if (it != _map.end())
	{
		_map.erase(it);
	}
}

void ProxyMapManager::load()
{
	std::ifstream cfg_file;
	cfg_file.open("ProxyMap.json",std::ios::binary);

	if (!cfg_file.is_open())
	{ 
		return;
	}

	Json::Reader Reader;
	Json::Value Root;

	if (Reader.parse(cfg_file,Root))
	{
		Json::Value proxy_info = Root["ProxyMap"];
		Json::Value::Members proxy_key = proxy_info.getMemberNames();
		
		for(Json::Value::Members::iterator iter = proxy_key.begin(); iter != proxy_key.end(); ++iter)
		{
			std::string key = *iter;
			std::string value = proxy_info[key].asString();
			_map[key.at(0)] = value;
		}
	}
	
	cfg_file.close();
}
