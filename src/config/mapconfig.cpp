#include <algorithm>

#include "../include/config/mapconfig.h"
#include "../include/common/common_func.h"

bool MapConfig::ParseConfigFile(const std::string &file_name)
{
    Json::Value msg;
    if (CommonFuncs::ParseJsonFile(file_name, msg))
    {
        CommonFuncs::ParseIntByKey(msg, "version", m_version);
        if (!msg["contents"].isNull())
        {
            return ParseJsonVal(msg["contents"]);
        }
    }
    return false;
}

void MapConfig::PrintConfigs() const
{
    printf("MapID[%d], StartPos[%.2f,%.2f] SceneType[%d]\n",
           m_map_id, m_map_info.start_pos.x, m_map_info.start_pos.y, m_setting_info.scene_type);
}

const MapInfo &MapConfig::GetMapInfo() const
{
    return m_map_info;
}

bool MapConfig::ParseJsonVal(Json::Value &msg)
{
    if (msg["MapInfo"].isNull() || msg["SettingInfo"].isNull())
    {
        return false;
    }

    if (!ParsseMapInfo(msg["MapInfo"]))
        return false;

    if (!ParseSettingInfo(msg["SettingInfo"]))
        return false;

    CommonFuncs::ParseIntByKey(msg, "ID", m_map_id);
    return true;
}

bool MapConfig::ParseSettingInfo(Json::Value &msg)
{
    CommonFuncs::ParseIntByKey(msg, "SceneType", m_setting_info.scene_type);
    CommonFuncs::ParseIntByKey(msg, "PKType", m_setting_info.pk_type);
    CommonFuncs::ParseIntByKey(msg, "TeamType", m_setting_info.team_type);
    return true;
}

bool MapConfig::ParsseMapInfo(Json::Value &msg)
{
    CommonFuncs::ParseIntByKey(msg, "VisionSize", m_map_info.vision_size);
    std::vector<double> tmp;
    CommonFuncs::ParseDoubleVectorByKey(msg, "StartPos", tmp);
    m_map_info.start_pos.x = tmp[0];
    m_map_info.start_pos.y = tmp [1];
    tmp.clear();
    CommonFuncs::ParseDoubleVectorByKey(msg, "EndPos", tmp);
    m_map_info.end_pos.x = tmp[0];
    m_map_info.end_pos.y = tmp[1];

    std::vector<std::string> grids_vec;
    CommonFuncs::ParseStringVectorByKey(msg, "GridInfo", grids_vec);

    int32_t col = abs(m_map_info.end_pos.x - m_map_info.start_pos.x);
    int32_t row = abs(m_map_info.end_pos.y - m_map_info.start_pos.y);
    if (grids_vec.empty() || (int32_t)grids_vec.size() != row)
    {
        std::cout << (grids_vec.empty() ? "Emtpy" : "Not Empty") << std::endl;
        std::cout << "Row " << row << ", size: " << grids_vec.size() << std::endl;
        return false;
    }

    m_map_info.grid_infos = new int8_t*[row];
    for (int32_t i = 0; i < row; ++i)
    {
        m_map_info.grid_infos[i] = new int8_t[col];
    }

    for (int32_t i = 0; i < row; ++i)
    {
        auto& line = grids_vec[i];
        if ((int32_t)line.length() != col)
            continue;
        for (int j = 0; j < col; ++j)
        {
            if ('1' == line[j])
            {
                m_map_info.grid_infos[i][j] = T_FREE_AREA;
            }
            else if ('2' == line[j])
            {
                m_map_info.grid_infos[i][j] = T_SHADOW_AREA;
            }
            else
            {
                m_map_info.grid_infos[i][j] = T_FORBID_AREA;
            }
        }
    }

    for (int i = 0; i < row; ++i )
    {
        for (int j = 0; j < col; ++j)
        {
            printf("%d", m_map_info.grid_infos[i][j]);
        }
        std::cout << std::endl;
    }
    return true;
}
