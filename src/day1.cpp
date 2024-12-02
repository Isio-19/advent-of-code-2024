#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <map>

std::vector<std::vector<int>> parseFile(std::filesystem::path filePath, std::string delimiter) {
    std::ifstream fileReader(filePath.relative_path());
    if (!fileReader.is_open()) {
        std::cerr << "An error has occurred while opening the " << filePath.filename() << " file!" << std::endl;
        exit(-1);
    }

    // parse the file
    std::string line;
    size_t pos = 0;

    std::vector<std::vector<int>> returnVector = {{}, {}};

    while (std::getline(fileReader, line)) {
        std::vector<int> tokens;
        // split the line
        while ((pos = line.find(delimiter)) != std::string::npos)  {
            std::string token = line.substr(0, pos);
            tokens.push_back(stoi(token));
            line.erase(0, pos + delimiter.length());
        }

        returnVector[0].push_back(tokens[0]);
        returnVector[1].push_back(stoi(line));
    }

    return returnVector;
}

int main(int argc, char const *argv[])
{
    // part 1
    std::filesystem::path folderPath = std::filesystem::path("data");
    std::filesystem::path filePath = folderPath / "day1.txt";

    std::vector<std::vector<int>> parsedFile = parseFile(filePath, "   ");
    std::vector<int> firstVector = parsedFile[0];
    std::vector<int> secondVector = parsedFile[1];

    // sort the vectors
    std::sort(firstVector.begin(), firstVector.end());
    std::sort(secondVector.begin(), secondVector.end());

    // compute distance
    int sum = 0;
    for (int index = 0; index<firstVector.size(); index++) {
        int firstValue = firstVector[index];
        int secondValue = secondVector[index];
        sum += abs(firstValue - secondValue);
    }

    std::cout << "Part 1: " <<  sum << std::endl;

    // Part 2
    std::map<int, int> similarityVector;
    // init the keys
    for (int i=0; i<firstVector.size(); i++) {
        int firstVectorValue = firstVector[i];
        if (similarityVector.find(firstVectorValue) == similarityVector.end())
            similarityVector.insert(std::make_pair(firstVectorValue, 0));
    }

    // init the values 
    for (int i=0; i<secondVector.size(); i++) {
        int secondVectorValue = secondVector[i];
        if (similarityVector.find(secondVectorValue) == similarityVector.end())
            continue;

        similarityVector[secondVectorValue] = ++similarityVector[secondVectorValue];
    }

    // compute the similarity score
    sum = 0;
    for (auto const& [key, val] : similarityVector) {
        sum += key * val;
    }

    std::cout << "Part 2: " << sum << std::endl;

    return 0;
}
