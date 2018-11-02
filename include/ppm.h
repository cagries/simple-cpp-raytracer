#ifndef __ppm_h__
#define __ppm_h__

namespace ppm {

void write_ppm(const char* filename, unsigned char* data, unsigned int width, unsigned int height);

} // namespace ppm

#endif // __ppm_h__
