#include <algorithm>

#include "../include/config/mapconfig.h"
#include "../include/common/common_json_func.h"

bool MapConfig::ParseConfigFile(const std::string &file_name)
{
    Json::Value msg;
    if (CommonJsonFunc::ParseJsonFile(file_name, msg))
    {
        CommonJsonFunc::ParseIntByKey(msg, "version", m_version);
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

bool MapConfig::IsBlockGrid(int32_t x_grid, int32_t y_grid)
{
    //std::cout << "row: " << m_map_info.grid_row << ", col: " << m_map_info.grid_col << std::endl;
    if (!IsGridValid(x_grid, y_grid))
        return true;

    return !(m_map_info.grid_infos[y_grid][x_grid] == T_FREE_AREA);
}

bool MapConfig::IsGridValid(int32_t x_grid, int32_t y_grid)
{
    return (x_grid >= 0) && (x_grid < m_map_info.grid_col) && (y_grid >= 0) && (y_grid < m_map_info.grid_row);
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

    CommonJsonFunc::ParseIntByKey(msg, "ID", m_map_id);
    return true;
}

bool MapConfig::ParseSettingInfo(Json::Value &msg)
{
    CommonJsonFunc::ParseIntByKey(msg, "SceneType", m_setting_info.scene_type);
    CommonJsonFunc::ParseIntByKey(msg, "PKType", m_setting_info.pk_type);
    CommonJsonFunc::ParseIntByKey(msg, "TeamType", m_setting_info.team_type);
    return true;
}

bool MapConfig::ParsseMapInfo(Json::Value &msg)
{
    CommonJsonFunc::ParseIntByKey(msg, "VisionSize", m_map_info.vision_size);
    std::vector<double> tmp;
    CommonJsonFunc::ParseDoubleVectorByKey(msg, "StartPos", tmp);
    m_map_info.start_pos.x = tmp[0];
    m_map_info.start_pos.y = tmp [1];
    tmp.clear();
    CommonJsonFunc::ParseDoubleVectorByKey(msg, "EndPos", tmp);
    m_map_info.end_pos.x = tmp[0];
    m_map_info.end_pos.y = tmp[1];

    std::vector<std::string> grids_vec;
    CommonJsonFunc::ParseStringVectorByKey(msg, "GridInfo", grids_vec);

    m_map_info.grid_col = abs(m_map_info.end_pos.x - m_map_info.start_pos.x) / 100;
    m_map_info.grid_row = abs(m_map_info.end_pos.y - m_map_info.start_pos.y) / 100;
    if (grids_vec.empty() || (int32_t)grids_vec.size() != m_map_info.grid_row)
    {
        std::cout << (grids_vec.empty() ? "Emtpy" : "Not Empty") << std::endl;
        std::cout << "Row " << m_map_info.grid_row << ", size: " << grids_vec.size() << std::endl;
        return false;
    }

    m_map_info.grid_infos = new int8_t*[m_map_info.grid_row];
    for (int32_t i = 0; i < m_map_info.grid_row; ++i)
    {
        m_map_info.grid_infos[i] = new int8_t[m_map_info.grid_col];
    }

    for (int32_t i = 0; i < m_map_info.grid_row; ++i)
    {
        auto& line = grids_vec[i];
        if ((int32_t)line.length() != m_map_info.grid_col)
            continue;
        for (int j = 0; j < m_map_info.grid_col; ++j)
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

    for (int i = 0; i < m_map_info.grid_row; ++i )
    {
        for (int j = 0; j < m_map_info.grid_col; ++j)
        {
            printf("%d", m_map_info.grid_infos[i][j]);
        }
        std::cout << std::endl;
    }
    return true;
}
