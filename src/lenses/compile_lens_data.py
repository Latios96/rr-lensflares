import csv
import glob

FILE_TEMPLATE = """
#ifndef RR_LENSFLARES_SRC_LENSES_H_
#define RR_LENSFLARES_SRC_LENSES_H_

#include "LensSystem.h"

std::vector<LensSystem> getAvailableLensSystems() {
    return {
        LENSES_PLACEHOLDER
    };
}

#endif //RR_LENSFLARES_SRC_LENSES_H_

"""
NAME_MAPPING = {

}

FOCAL_LENGTH_MAPPING = {

}
if __name__ == '__main__':
    lens_texts = []
    lens_files = glob.glob("*.txt")
    for lens_file in sorted(lens_files):
        with open(lens_file) as file:
            lens_text = ""
            line = file.readline()
            lens_name = line.replace('"', '')
            lens_text+=f'{{"{lens_name.strip()}", {{'
            while "#" in line:
                line = file.readline()
            tsv_file = csv.reader(file, delimiter="\t")
            for line in tsv_file:
                lens_text+=f"{{{line[0]}, {line[1]}, {line[2]}, {float(line[3])/2.0}}},"
            lens_text+="}}"
            lens_texts.append(lens_text)

    with open("../LensSystems.h", "w") as f:
        f.write(FILE_TEMPLATE.replace("LENSES_PLACEHOLDER", ", ".join(lens_texts)))
