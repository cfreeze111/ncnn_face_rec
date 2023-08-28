#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>

#include <time.h>

namespace utils {
// ��ʱ
typedef struct timeval TIME_T;

#define MARK_TIME(t) gettimeofday(&t, NULL)
#define DIFF_TIME(start, end) \
  ((end.tv_sec - start.tv_sec) * 1e3 + (end.tv_usec - start.tv_usec) * 1e-3)   // ms

/**
 * @brief float��������תchar����
 *
 * @param f
 * @param s
 * @return unsigned char*
 */
unsigned char* float2char(float f, unsigned char* s);

/**
 * @brief char��������תfloat����
 *
 * @param s
 * @return float
 */
float char2float(unsigned char* s);

/**
 * @brief �ַ���תʮ����������
 *
 * @param s ʮ�����������ַ���
 *
 * @return unsigned long ʮ����������
 */
unsigned long stoulHex(std::string& s);

/**
 * @brief �ַ���תʮ��������
 *
 * @param s ʮ���������ַ���
 *
 * @return unsigned long ʮ��������
 */
unsigned long stoulDec(std::string& s);

/**
 * @brief �ַ���ת��
 *
 * @param val
 *
 * @return std::string
 */
std::string to_string(long long val);

/**
 * @brief ��ȡ�ļ�
 *
 * @param path
 * @param length
 * @return char*
 */
char* readFile(const std::string& path);

}   // namespace utils



#endif
