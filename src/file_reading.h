#include <fstream>
#include <iterator>
#include <string>
#include <iostream>
#include "file_readingException.h"

std::string readFileContent(const std::string& filePath);
void writeFileContent(const std::string& filePath, const std::string& content);