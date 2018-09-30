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

bool MapConfig::IsBlockGrid(int32_t x_grid, int32_t y_grid)
{
    int32_t tmp_x = x_grid, tmp_y = y_grid;
    if (x_grid < 0)
    {
        tmp_x = 0;
    }
    else if (x_grid >= m_map_info.grid_col)
    {
        tmp_x = m_map_info.grid_col - 1;
    }
    if (y_grid < 0)
    {
        tmp_y = 0;
    }
    else if (y_grid >= m_map_info.grid_row)
    {
        tmp_y = m_map_info.grid_row - 1;
    }

    return !(m_map_info.grid_infos[tmp_x][tmp_y] == T_FREE_AREA);
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
