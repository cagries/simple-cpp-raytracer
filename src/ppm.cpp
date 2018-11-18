#include "ppm.h"
#include <stdexcept>

namespace ppm {

void write_ppm(const char* filename, unsigned char* data, unsigned int width, unsigned int height)
{
    FILE *outfile;

    if ((outfile = fopen(filename, "w")) == NULL) 
    {
        throw std::runtime_error("Error: The ppm file cannot be opened for writing.");
    }

    (void) fprintf(outfile, "P3\n%d %d\n255\n", width, height);

    unsigned char color;
    for (size_t j = 0, idx = 0; j < height; ++j)
    {
        for (size_t i = 0; i < width; ++i)
        {
            for (size_t c = 0; c < 4; ++c, ++idx)
            {
                color = data[idx];

                // Alpha not used in any variant of PPM
                if (c == 3)
                    continue;

                if (i == width - 1 && c == 2)
                {
                    (void) fprintf(outfile, "%d", color);
                }
                else
                {
                    (void) fprintf(outfile, "%d ", color);
                }
            }
        }

        (void) fprintf(outfile, "\n");
    }

    (void) fclose(outfile);
}

} // namespace ppm
