#include "LevelLoader.h"


////////////////////////////////////////////////////////////
void operator >> (const YAML::Node& t_mapBlockNode, mapBlock& t_block)
{
	t_block.block = t_mapBlockNode["map"].as<std::vector<int>>();
}


////////////////////////////////////////////////////////////
void operator >> (const YAML::Node& t_levelNode, LevelData& t_level)
{
	const YAML::Node& mapBlockNode = t_levelNode["map"].as<YAML::Node>();

	int size = mapBlockNode.size();

	for (unsigned i = 0; i < size; ++i)
	{
		mapBlock block;
		mapBlockNode[i] >> block;
		t_level.m_blockType.push_back(block);
	}
}

////////////////////////////////////////////////////////////
void LevelLoader::load(int t_levelNr, LevelData& t_level)
{
	std::string filename = "./recources/levels/level" + std::to_string(t_levelNr) + ".yaml";

	try
	{
		YAML::Node baseNode = YAML::LoadFile(filename);

		if (baseNode.IsNull())
		{
			std::string message("File: " + filename + " not found");
			throw std::exception(message.c_str());
		}

		baseNode >> t_level;
	}
	catch (YAML::ParserException& e)
	{
		std::string message(e.what());
		message = "YAML Parser Error: " + message;
		throw std::exception(message.c_str());
	}
	catch (std::exception& e)
	{
		std::string message(e.what());
		message = "Unexpected Error: " + message;
		throw std::exception(message.c_str());
	}
}

void LevelLoader::loadCustomMap(std::string t_name, LevelData& t_level)
{
	std::string filename = "./CUSTOMMAPS/" + t_name + ".yaml";

	try
	{
		YAML::Node baseNode = YAML::LoadFile(filename);

		if (baseNode.IsNull())
		{
			std::string message("File: " + filename + " not found");
			throw std::exception(message.c_str());
		}

		baseNode >> t_level;
	}
	catch (YAML::ParserException& e)
	{
		std::string message(e.what());
		message = "YAML Parser Error: " + message;
		throw std::exception(message.c_str());
	}
	catch (std::exception& e)
	{
		std::string message(e.what());
		message = "Unexpected Error: " + message;
		throw std::exception(message.c_str());
	}
}
