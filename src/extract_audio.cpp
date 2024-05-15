#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "CascLib/src/CascLib.h"

void LogStatus(const std::string &message)
{
    std::ofstream statusLog("casc_status_log.txt", std::ios::app);
    if (statusLog)
    {
        statusLog << message << std::endl;
    }
}

std::string trim(const std::string &str)
{
    auto start = std::find_if_not(str.begin(), str.end(), [](int ch)
                                  { return std::isspace(ch); });
    auto end = std::find_if_not(str.rbegin(), str.rend(), [](int ch)
                                { return std::isspace(ch); })
                   .base();
    return (start < end ? std::string(start, end) : std::string());
}

int main()
{
    std::string storagePath;
    std::string targetDirectory;

    std::cout << "Enter the storage path: ";
    std::getline(std::cin, storagePath);
    storagePath = trim(storagePath); // Trim leading and trailing spaces

    std::cout << "Enter the target directory: ";
    std::getline(std::cin, targetDirectory);
    targetDirectory = trim(targetDirectory); // Trim leading and trailing spaces

    std::__fs::filesystem::create_directories(targetDirectory);

    HANDLE hStorage = NULL;
    HANDLE hFile = NULL;
    CASC_FIND_DATA findData;
    std::vector<std::string> audioExtensions = {".wav", ".mp3", ".ogg"};

    // Open the CASC storage
    if (!CascOpenStorage(storagePath.c_str(), CASC_LOCALE_ALL, &hStorage))
    {
        std::string errorMsg = "Error opening storage: " + std::to_string(GetCascError());
        std::cerr << errorMsg << std::endl;
        LogStatus(errorMsg);
        return 1;
    }
    std::cout << "Storage opened successfully." << std::endl;

    // Find the first file in the storage
    HANDLE hFind = CascFindFirstFile(hStorage, "*", &findData, NULL);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        std::string errorMsg = "Error finding first file: " + std::to_string(GetCascError());
        std::cerr << errorMsg << std::endl;
        LogStatus(errorMsg);
        CascCloseStorage(hStorage);
        return 1;
    }
    std::cout << "First file found successfully." << std::endl;

    // Iterate through the files in the storage
    do
    {
        std::string fileName(findData.szFileName);
        std::cout << "Processing file: " << fileName << std::endl;

        // Check if the file has an audio extension
        for (const std::string &ext : audioExtensions)
        {
            if (fileName.size() >= ext.size() &&
                fileName.compare(fileName.size() - ext.size(), ext.size(), ext) == 0)
            {
                // Open the file in the storage
                if (CascOpenFile(hStorage, fileName.c_str(), CASC_LOCALE_ALL, 0, &hFile))
                {
                    // Create the target file path
                    std::string targetFilePath = targetDirectory + "/" + findData.szPlainName;
                    std::cout << "Opening file: " << targetFilePath << std::endl;

                    // Create output file stream
                    std::ofstream outFile(targetFilePath, std::ios::binary);
                    if (!outFile)
                    {
                        std::string errorMsg = "Error creating file: " + targetFilePath;
                        std::cerr << errorMsg << std::endl;
                        LogStatus(errorMsg);
                        CascCloseFile(hFile);
                        continue;
                    }

                    // Read and write the file content
                    char buffer[0x10000];
                    DWORD bytesRead = 0;
                    do
                    {
                        if (!CascReadFile(hFile, buffer, sizeof(buffer), &bytesRead))
                        {
                            std::string errorMsg = "Error reading file: " + fileName;
                            std::cerr << errorMsg << std::endl;
                            LogStatus(errorMsg);
                            break;
                        }
                        outFile.write(buffer, bytesRead);
                    } while (bytesRead > 0);
                    std::cout << "File written successfully: " << targetFilePath << std::endl;

                    // Close the output file
                    outFile.close();
                    CascCloseFile(hFile);
                }
                else
                {
                    std::string errorMsg = "Error opening file: " + fileName;
                    std::cerr << errorMsg << std::endl;
                    LogStatus(errorMsg);
                }
                break; // Exit the loop as we found the matching extension
            }
        }
    } while (CascFindNextFile(hFind, &findData));

    // Clean up
    CascFindClose(hFind);
    CascCloseStorage(hStorage);
    std::cout << "Operation completed." << std::endl;

    return 0;
}