#ifndef __ppm_h__
#define __ppm_h__

#include <string>
#include <vector>

namespace ppm {

void write_ppm(const std::string& filename, 
        const std::vector<unsigned char>& data,
        unsigned int width, unsigned int height);

} // namespace ppm

#endif // __ppm_h__
