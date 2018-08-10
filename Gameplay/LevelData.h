#pragma once
#include <string>
#include <vector>
#include <map>
#include "../rapidjson/document.h"
#include "../Base/BaseComponent.h"
#include "../Base/BaseObject.h"

#include "GameFactory.h"

struct TileInfo
{
    unsigned TemplateIndex;
};

struct GameObjectInfo
{
    unsigned X;
    unsigned Y;
    unsigned TemplateIndex;
};

class LevelData
{
    LevelData& operator=(const LevelData&);
    LevelData(const LevelData&);
public:
    LevelData(PlayState* parentState);

    void load(const std::string& fileName);

    int getTileWidth() const { return m_tileWidth;}
    int getTileHeight() const { return m_tileHeight;}
    int getWidthInTiles() const { return m_widthInTiles;}
    int getHeightInTiles() const { return m_heightInTiles;}

    std::vector<TileInfo>& getCells() {return m_cells;}
    TileInfo& getTileInfo(unsigned i, unsigned k)
    {
        unsigned index = k*m_widthInTiles + i;
        if( index < m_cells.size())
        {
            return m_cells[index];
        }

        return m_cells[0];
    }

    std::vector<GameObjectInfo>& getGameObjects() { return m_gameObjects;}

    BaseObject* createBaseObjectFromTemplateID(const std::string& templateID, unsigned X, unsigned Y);
    BaseObject* createBaseObjectFromTemplateIndex(unsigned int index, unsigned X, unsigned Y);

private:
    rapidjson::SizeType getTemplateIndex(const std::string& templateID);

    void readWorldSize(rapidjson::Value& value);
    void readDefaultCellData(rapidjson::Value& value);
    void readTemplates(rapidjson::Value& value);
    void readCellData(rapidjson::Value& value);
    void readCellsData(rapidjson::Value& value);
    void readGameObjectsData(rapidjson::Value& value);
    void readGameObjectData(rapidjson::Value& value);


private:
    PlayState* m_parentState;
    rapidjson::Document m_document;
    std::vector<TileInfo> m_cells;
    TileInfo m_defaultCellData;
    std::vector<GameObjectInfo> m_gameObjects;
    int m_tileWidth;
    int m_tileHeight;
    int m_widthInTiles;
    int m_heightInTiles;
};

