#include "FileWriter.h"


bool FileWriter::saveAsImage (std::string image) {

    time_t seconds = time (NULL);
    std::string fileName = ("image_" + std::to_string(seconds) + ".ppm");

    std::string folderName = "screenshots";
    std::ofstream outputFile(folderName + fileName);
    //std::ofstream outputFile (fileName);

    std::cout << "\"" << folderName << fileName << "\"" << std::endl;

    if (!outputFile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return false;
    }

    outputFile << image;
    outputFile.close();

    std::cout << "Arquivo gerado com sucesso." << std::endl;
    std::cout << '~' << std::filesystem::current_path().string() << '/' << folderName << fileName << std::endl;
    return true;
}