#ifndef FILEWRITER_H
#define FILEWRITER_H
#include <filesystem>
#include <time.h>
#include <string>
#include <vector>
#include <chrono>
#include <iostream>
#include <fstream>


class FileWriter {
    public:
        FileWriter() {};
        static bool saveAsImage (std::string image);
};

#endif // FILEWRITER_H
