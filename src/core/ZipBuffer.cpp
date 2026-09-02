#include "core/ZipBuffer.h"
#include "core/Log.h"

#include <filesystem>

using namespace SolAR;
namespace fs = std::filesystem;

ZipBuffer::ZipBuffer()
{
    try {
        // Create a working directory for zip/unzip features
        fs::path wp(m_workingPath);
        if (!fs::exists(wp)) {
            if (!fs::create_directories(wp)) {
                LOG_ERROR("Error while creating the working directory for zip/unzip features: {}", m_workingPath);
            }
            LOG_DEBUG("Working directory created for zip/unzip features: {}", m_workingPath);
        }
    }
    catch (const fs::filesystem_error & e) {
        LOG_ERROR("The following exception has been caught {}", e.what());
    }
}

ZipBuffer::~ZipBuffer()
{
    try {
        // Delete the working directory
        fs::remove_all(m_workingPath);
    }
    catch (const fs::filesystem_error & e) {
        LOG_ERROR("The following exception has been caught {}", e.what());
    }
}

bool ZipBuffer::zipToBuffer(const std::string & originalPath,
                            std::vector<unsigned char> & compressedZipBuffer)
{
    try {
        // Check working directory
        fs::path wp(m_workingPath);
        if (!fs::is_directory(wp)) {
            LOG_ERROR("Can not find the working directory: {}", m_workingPath);
            return false;
        }

        // Check original path
        fs::path op(originalPath);
        if (!fs::is_directory(op)) {
            LOG_ERROR("The original path is not a directory: {}", originalPath);
            return false;
        }
        if (fs::is_empty(op)) {
            LOG_ERROR("The original path is empty: {}", originalPath);
            return false;
        }

        // Copy data to zip in the working directory
        const auto copyOptions = fs::copy_options::recursive;
        fs::copy(op, wp, copyOptions);
    }
    catch (const fs::filesystem_error & e) {
        LOG_ERROR("The following exception has been caught {}", e.what());
        cleanWorkingDirectory();
        return false;
    }

    bool result = [&]() {
        // Try to zip the working directory content
        std::string command = "cd " + m_workingPath + ";zip -r data.zip .";
        if  (std::system(command.c_str()) != 0) {
            LOG_ERROR("Error occured while trying to zip the working directory content: {}", m_workingPath);
            return false;
        }

        // Open the resulting zip file
        std::string zipFile = m_workingPath + "/data.zip";
        std::ifstream file(zipFile, std::ios::binary);
        if (!file.is_open()) {
            LOG_ERROR("Cannot open the zip binary file: {}", zipFile);
            return false;
        }

        // Get its size
        file.seekg(0, std::ios::end);
        std::streampos fileSize = file.tellg();
        file.seekg(0, std::ios::beg);
        if (fileSize == 0) {
            LOG_ERROR("Empty zip binary file: {}", zipFile);
            return false;
        }
        LOG_DEBUG("Zip file size ({}): {}", zipFile, fmt::streamed(fileSize));

        // Read the data and put it in the output buffer
        compressedZipBuffer.resize(fileSize);
        file.read(reinterpret_cast<char*>(compressedZipBuffer.data()), compressedZipBuffer.size());

        return true;
    }();

    cleanWorkingDirectory();

    return result;
}

bool ZipBuffer::bufferToUnzip(const std::vector<unsigned char> & compressedZipBuffer,
                              std::string & destinationPath)
{
    if (compressedZipBuffer.empty()) {
        LOG_ERROR("Empty input buffer");
        return false;
    }

    try {
        fs::path wp(m_workingPath);
        fs::path dp(destinationPath);

        // Check working directory
        if (!fs::is_directory(wp)) {
            LOG_ERROR("Can not find the working directory: {}", m_workingPath);
            return false;
        }

        // Check destination path
        if (!fs::is_directory(dp)) {
            LOG_ERROR("The destination path is not a directory: {}", destinationPath);
            return false;
        }

        bool result = [&]() {
            // Create the zip file from the input buffer
            std::string zipFile = m_workingPath + "/data.zip";
            std::ofstream file(zipFile, std::ios::out | std::ios::binary);
            if (!file.is_open()) {
                LOG_ERROR("Cannot create/open zip file: {}", zipFile);
                return false;
            }

            // Write the compressed data
            file.write(reinterpret_cast<const char*>(compressedZipBuffer.data()), compressedZipBuffer.size());
            file.close();

            // Try to unzip the file content
            std::string command = "cd " + m_workingPath + "; unzip data.zip";
            if  (std::system(command.c_str()) != 0) {
                LOG_ERROR("Error occured while trying to unzip the compressed data file: {}", zipFile);
                return false;
            }

            // Delete the zip file
            fs::remove(zipFile);

            // Copy unzipped data in the destination directory
            const auto copyOptions = fs::copy_options::recursive;
            fs::copy(wp, dp, copyOptions);

            return true;
        } ();

        cleanWorkingDirectory();

        return result;
    }
    catch (const fs::filesystem_error & e) {
        LOG_ERROR("The following exception has been caught {}", e.what());
        cleanWorkingDirectory();
        return false;
    }
}

// private

void ZipBuffer::cleanWorkingDirectory()
{
    fs::path wp(m_workingPath);
    for (auto& path: fs::directory_iterator(wp)) {
        fs::remove_all(path);
    }
}