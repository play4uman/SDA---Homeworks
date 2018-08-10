#pragma once
#include "LevelData.h"

#include "../rapidjson/filereadstream.h"
#include "Player.h"
#include "NormalArcher.h"
#include "SpreeArcher.h"
#include "MagicArcher.h"
#include "GameFactory.h"
#include "../Base/VisualComponent.h"
#include "../Base/vec2.h"

#include <cstdio>

LevelData::LevelData(PlayState* parentState):
    m_parentState(parentState),
    m_tileWidth(0),
    m_tileHeight(0),
    m_widthInTiles(0),
    m_heightInTiles(0)
{

}
void LevelData::load(const std::string& fileName)
{
    m_cells.clear();

    FILE* fp = 0;
    errno_t err  = fopen_s(&fp, fileName.c_str(), "rb");
    if( err == 0 )
    {
        char readBuffer[256];
        rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
        m_document.ParseStream(is);

        readWorldSize(m_document["WorldSize"]);
        readDefaultCellData(m_document["DefaultCell"]);
        readCellsData(m_document["Cells"]);
        readGameObjectsData(m_document["GameObjects"]);

        fclose(fp);
    }
}

void LevelData::readWorldSize(rapidjson::Value& value)
{
   m_widthInTiles  = value["WidthInTiles"].GetInt();
   m_heightInTiles = value["HeightInTiles"].GetInt();
   m_tileWidth = value["TileWidth"].GetInt();
   m_tileHeight = value["TileHeight"].GetInt();

   m_cells.resize(m_widthInTiles*m_heightInTiles);
}

void LevelData::readTemplates(rapidjson::Value& value)
{
}

void LevelData::readDefaultCellData(rapidjson::Value& value)
{
    m_defaultCellData.TemplateIndex = value["TemplateIndex"].GetUint();
    for(TileInfo& info : m_cells)
    {
        info = m_defaultCellData;
    }
}

void LevelData::readCellsData(rapidjson::Value& value)
{
    for (rapidjson::SizeType i = 0; i < value.Size(); i++)
    {
        readCellData(value[i]);
    }
}

void LevelData::readCellData(rapidjson::Value& value)
{
    int tileX = value["TileX"].GetInt();
    int tileY = value["TileY"].GetInt();
    getTileInfo(tileX, tileY).TemplateIndex = value["TemplateIndex"].GetUint();
}


void LevelData::readGameObjectsData(rapidjson::Value& value)
{
    for (rapidjson::SizeType i = 0; i < value.Size(); i++)
    {
        readGameObjectData(value[i]);
    }
}

void LevelData::readGameObjectData(rapidjson::Value& value)
{
    GameObjectInfo info;
    info.X = value["X"].GetInt();
    info.Y = value["Y"].GetInt();
    if (value.HasMember("TemplateIndex"))
        info.TemplateIndex = value["TemplateIndex"].GetUint();
    else
        info.TemplateIndex = getTemplateIndex(value["TemplateID"].GetString());
    m_gameObjects.push_back(info);
}

rapidjson::SizeType LevelData::getTemplateIndex(const std::string& templateID)
{
    rapidjson::Value& value = m_document["Templates"];
    for (rapidjson::SizeType i = 0; i < value.Size(); i++)
    {
        rapidjson::Value& templateData = value[i];
        if(templateData["TemplateID"].GetString() == templateID)
            return i;
    }
    return (rapidjson::SizeType)-1;
}

BaseObject* LevelData::createBaseObjectFromTemplateID(const std::string& templateID, unsigned X, unsigned Y)
{
    rapidjson::SizeType ind = getTemplateIndex(templateID);
    return createBaseObjectFromTemplateIndex(ind, X, Y);
}

BaseObject* LevelData::createBaseObjectFromTemplateIndex(unsigned int index, unsigned X, unsigned Y)
{
    rapidjson::Value& value = m_document["Templates"];
    if (index > value.Size())
        return nullptr;
    return GameFactory::createBaseObjectFromJson(value[index], m_parentState, vec2(X, Y));
}