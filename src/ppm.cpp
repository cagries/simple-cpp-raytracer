#include <fstream>
#include <stdexcept>

#include "ppm.h"

namespace ppm {

void 
write_ppm(const std::string& filename, const std::vector<unsigned char>& data,
        unsigned int width, unsigned int height)
{
    std::ofstream outfile {filename, std::ios_base::out};

    if (!outfile.is_open()) {
        throw std::runtime_error("[ppm]: The ppm file cannot be opened for writing.");
    }

    outfile << "P3" << '\n'
            << width << " " << height << '\n'
            << 255 << '\n';


    std::size_t index = 0;
    for (std::size_t i = 0; i < height; i++) {
        for (std::size_t j = 0; j < width; j++, index += 4) {
            outfile << static_cast<int>(data[index]) << ' '
                    << static_cast<int>(data[index + 1]) << ' '
                    << static_cast<int>(data[index + 2]);
            if (j != width - 1) {
                outfile << ' ';
            }
        }
        outfile << '\n';
    }
}

} // namespace ppm
