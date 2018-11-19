#!/usr/bin/python3

# Cagri Eser
# A very small script to calculate the cosine similarity between
# two different ASCII-encoded PPM files. Please note that the
# resolutions of the two images should be the same for this script
# to work properly
import sys
import numpy

def ppm_to_vector(image_file):
    values = []
    with open(image_file, 'r') as file:
        lines = file.read().split('\n')
        if lines[0] != 'P3':
            print('Not a valid ASCII-encoded PPM image.' +
                    'Quitting.')
            exit(1)
        width, height = lines[1].split(' ')

        # The second line is not important
        for line in lines[3:]:
            split = line.split()
            if split:
                values.extend(map(int, split))
    return numpy.array(values, dtype=float)

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print('Usage: ./cosine <your_image.ppm> <target_image.ppm>')
    im1 = ppm_to_vector(sys.argv[1])
    im2 = ppm_to_vector(sys.argv[2])

    print('Cosine similarity:', im1.dot(im2) / (numpy.linalg.norm(im1) * numpy.linalg.norm(im2)))
