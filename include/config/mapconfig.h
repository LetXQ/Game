#pragma once
#include "../include/common/singleton.h"
#include "../include/json/json.h"
#include "../include/common/world_pos.h"

struct SettingInfo
{
    int32_t scene_type = 0;
    int32_t pk_type = 0;
    int32_t team_type = 0;
};

enum AreaType
{
    T_FORBID_AREA = 0x00,
    T_FREE_AREA = 0x01,
    T_SHADOW_AREA = 0x08,
};
struct MapInfo
{
    int32_t vision_size = 0;
    int32_t grid_col = 0;
    int32_t grid_row = 0;
    Point start_pos;
    Point end_pos;
    int8_t** grid_infos;
};

class MapConfig : public Singleton<MapConfig>
{
public:
    bool ParseConfigFile(const std::string& file_name);
    void PrintConfigs() const;
    const MapInfo& GetMapInfo() const;
    bool IsBlockGrid(int32_t x_grid, int32_t y_grid);
private:
    bool ParseJsonVal(Json::Value& msg);
    bool ParseSettingInfo(Json::Value& msg);
    bool ParsseMapInfo(Json::Value& msg);
private:
    std::string m_file_name = "";
    int32_t m_version = 0;
    int32_t m_map_id = 0;

    SettingInfo m_setting_info;
    MapInfo m_map_info;
};
