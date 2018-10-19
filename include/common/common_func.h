#ifndef COMMON_FUNC_H
#define COMMON_FUNC_H
#include <iostream>
#include <vector>
#include <string.h>
#include <sys/time.h>

using namespace std;

class CommonFuncs
{
public:
    static void SpiltString(const std::string& src, const std::string& token, std::vector<std::string>& res)
    {
        std::string::size_type pos1 = 0, pos2 = 0;
        pos2 = src.find(token);

        while (std::string::npos != pos2) {
            res.push_back(src.substr(pos1, pos2));

            pos1 = pos2 + token.size();
            pos2 = src.find(token, pos1);
        }

        if (pos1 != src.length())
            res.push_back(src.substr(pos1));
    }

    static void GetLastToken(const std::string& src, std::string& res)
    {
       std::vector<string> token_vec;
       SpiltString(src, ".", token_vec);

        if (2 == (int32_t)token_vec.size())
            res.assign(token_vec[1]);
    }

    static int64_t GetNowMsec()
    {
        struct timeval st;
        gettimeofday(&st, nullptr);
        return ((int64_t)(st.tv_sec * 1000) + st.tv_usec / 1000);
    }

    static int64_t GetNowSec()
    {
        struct timeval st;
        gettimeofday(&st, nullptr);
        return st.tv_sec;
    }
};
#endif // COMMON_FUNC_H
