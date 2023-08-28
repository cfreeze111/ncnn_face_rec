#include <iostream>
#include <sstream>

#include "utils.h"

namespace utils {

static inline void* alignedMalloc(size_t size, int align)
{
  void*          tmp = malloc(size + align + sizeof(unsigned long));
  unsigned long* ret =
    (unsigned long*)(((unsigned long)tmp + align) & ~((unsigned long)(align - 1)));
  *(ret - 1) = (unsigned long)tmp;
  return (void*)ret;
}

static inline void alignedFree(void* ptr)
{
  unsigned long* pptr     = (unsigned long*)ptr;
  void*          real_ptr = (void*)(*(pptr - 1));
  free(real_ptr);
}

unsigned long stoulHex(std::string& s)
{
  unsigned long val = 0;
  for (unsigned int i = 0; i < s.length(); i++) {
    char c = s[i];
    if (isalpha(c)) {
      switch (c) {
      case 'a':
      case 'A': val = val * 16 + 10; break;
      case 'b':
      case 'B': val = val * 16 + 11; break;
      case 'c':
      case 'C': val = val * 16 + 12; break;
      case 'd':
      case 'D': val = val * 16 + 13; break;
      case 'e':
      case 'E': val = val * 16 + 14; break;
      case 'f':
      case 'F': val = val * 16 + 15; break;
      }
    }
    else {
      val = val * 16 + c - '0';
    }
  }
  return val;
}

unsigned long stoulDec(std::string& s)
{
  unsigned long val = 0;
  for (unsigned int i = 0; i < s.length(); i++) {
    char c = s[i];
    val    = val * 10 + c - '0';
  }
  return val;
}

unsigned char* float2char(float f, unsigned char* s)
{
  union change
  {
    float         d;
    unsigned char dat[4];
  } r1;

  r1.d     = f;
  *s       = r1.dat[0];
  *(s + 1) = r1.dat[1];
  *(s + 2) = r1.dat[2];
  *(s + 3) = r1.dat[3];
  return s;
}

float char2float(unsigned char* s)
{
  float f;
  union change
  {
    float         d;
    unsigned char dat[4];
  } r1;

  r1.dat[0] = *s;
  r1.dat[1] = *(s + 1);
  r1.dat[2] = *(s + 2);
  r1.dat[3] = *(s + 3);
  f         = r1.d;
  return f;
}

char* readFile(const std::string& path)
{
  FILE* pfile;
  char* data;

  pfile = fopen(path.c_str(), "rb");
  if (pfile == NULL) {
    return NULL;
  }
  fseek(pfile, 0, SEEK_END);
  int length = ftell(pfile);
  data       = (char*)malloc((length + 1) * sizeof(char));
  rewind(pfile);
  length       = fread(data, 1, length, pfile);
  data[length] = '\0';
  fclose(pfile);

  return data;
}

}   // namespace utils
