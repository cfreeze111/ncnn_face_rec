#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>

#include <time.h>

namespace utils {
// 计时
typedef struct timeval TIME_T;

#define MARK_TIME(t) gettimeofday(&t, NULL)
#define DIFF_TIME(start, end) \
  ((end.tv_sec - start.tv_sec) * 1e3 + (end.tv_usec - start.tv_usec) * 1e-3)   // ms

/**
 * @brief float类型数据转char类型
 *
 * @param f
 * @param s
 * @return unsigned char*
 */
unsigned char* float2char(float f, unsigned char* s);

/**
 * @brief char类型数据转float类型
 *
 * @param s
 * @return float
 */
float char2float(unsigned char* s);

/**
 * @brief 字符串转十六进制整数
 *
 * @param s 十六进制整数字符串
 *
 * @return unsigned long 十六进制整数
 */
unsigned long stoulHex(std::string& s);

/**
 * @brief 字符串转十进制整数
 *
 * @param s 十进制整数字符串
 *
 * @return unsigned long 十进制整数
 */
unsigned long stoulDec(std::string& s);

/**
 * @brief 字符串转换
 *
 * @param val
 *
 * @return std::string
 */
std::string to_string(long long val);

/**
 * @brief 读取文件
 *
 * @param path
 * @param length
 * @return char*
 */
char* readFile(const std::string& path);

}   // namespace utils



#endif
