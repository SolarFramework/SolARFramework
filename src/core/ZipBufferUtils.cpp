#include "core/ZipBufferUtils.h"
#include "core/Log.h"

namespace fs = std::filesystem;

using namespace SolAR;


ScopedTempDir::ScopedTempDir()
{
    m_tempPath = fs::temp_directory_path();
    m_tempPath /= "solar";
    // Create the temporary directory
    std::error_code ec;
    fs::create_directories(m_tempPath, ec);
}

ScopedTempDir::~ScopedTempDir()
{
    // Delete the temporary directory (and its contents)
    std::error_code ec; fs::remove_all(m_tempPath, ec);
}

const fs::path ScopedTempDir::getPath() const
{
    return m_tempPath;
}

const std::string ScopedTempDir::getStringPath() const
{
    return m_tempPath.string();
}


FrameworkReturnCode ZipBufferUtils::compress(const std::string & originalPath,
                                             std::vector<unsigned char> & compressedZipBuffer)
{
    LOG_DEBUG("ZipBufferUtils::compress - Original path: {}", originalPath);

    compressedZipBuffer.clear();

    // Get a temporary working directory
    ScopedTempDir workingDir;

    LOG_DEBUG("ZipBufferUtils::compress - Working temporary path: {}", workingDir.getStringPath());

    fs::path op(originalPath);

    try {
        // Check original path
        if (!fs::is_directory(op)) {
            LOG_ERROR("ZipBufferUtils::compress - The original path is not a directory: {}", originalPath);
            return FrameworkReturnCode::_ERROR_;
        }
        if (fs::is_empty(op)) {
            LOG_WARNING("ZipBufferUtils::compress - The original path is empty: {}", originalPath);
            return FrameworkReturnCode::_SUCCESS;
        }
    }
    catch (const fs::filesystem_error & e) {
        LOG_ERROR("ZipBufferUtils::compress - The following exception has been caught {}", e.what());
        return FrameworkReturnCode::_ERROR_;
    }

    // Try to zip the original path content
    std::string command = "cd " + originalPath +"; zip -r " + workingDir.getStringPath() + "/data.zip .";
    if  (std::system(command.c_str()) != 0) {
        LOG_ERROR("ZipBufferUtils::compress - Error occured while trying to zip the working directory content: {}", workingDir.getStringPath());
        return FrameworkReturnCode::_ERROR_;
    }

    // Open the resulting zip file
    std::string zipFile = workingDir.getStringPath() + "/data.zip";
    std::ifstream file(zipFile, std::ios::binary);
    if (!file.is_open()) {
        LOG_ERROR("ZipBufferUtils::compress - Cannot open the zip binary file: {}", zipFile);
        return FrameworkReturnCode::_ERROR_;
    }

    // Get its size
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    if (fileSize == 0) {
        LOG_ERROR("ZipBufferUtils::compress - Empty zip binary file: {}", zipFile);
        return FrameworkReturnCode::_ERROR_;
    }
    LOG_DEBUG("ZipBufferUtils::compress - Zip file size ({}): {}", zipFile, fmt::streamed(fileSize));

    // Read the data and put it in the output buffer
    compressedZipBuffer.resize(fileSize);
    file.read(reinterpret_cast<char*>(compressedZipBuffer.data()), compressedZipBuffer.size());

    return FrameworkReturnCode::_SUCCESS;
}

FrameworkReturnCode ZipBufferUtils::extract(const std::vector<unsigned char> & compressedZipBuffer,
                                            std::string & destinationPath)
{
    LOG_DEBUG("ZipBufferUtils::extract - Destination path: {}", destinationPath);

    if (compressedZipBuffer.empty()) {
        LOG_WARNING("ZipBufferUtils::extract - Empty input buffer");
        return FrameworkReturnCode::_SUCCESS;
    }

    try {
        fs::path dp(destinationPath);

        // Check destination path
        if (!fs::is_directory(dp)) {
            LOG_ERROR("ZipBufferUtils::extract - The destination path is not a directory: {}", destinationPath);
            return FrameworkReturnCode::_ERROR_;
        }

        // Get a temporary working directory
        ScopedTempDir workingDir;

        LOG_DEBUG("ZipBufferUtils::extract - Working temporary path: {}", workingDir.getStringPath());

        // Create the zip file from the input buffer
        std::string zipFile = workingDir.getStringPath() + "/data.zip";
        std::ofstream file(zipFile, std::ios::out | std::ios::binary);
        if (!file.is_open()) {
            LOG_ERROR("ZipBufferUtils::extract - Cannot create/open zip file: {}", zipFile);
            return FrameworkReturnCode::_ERROR_;
        }

        // Write the compressed data
        file.write(reinterpret_cast<const char*>(compressedZipBuffer.data()), compressedZipBuffer.size());
        file.close();

        // Try to unzip the file content
        std::string command = "unzip " + workingDir.getStringPath() + "/data.zip -d " + destinationPath;
        if  (std::system(command.c_str()) != 0) {
            LOG_ERROR("ZipBufferUtils::extract - Error occured while trying to unzip the compressed data file: {}", zipFile);
            return FrameworkReturnCode::_ERROR_;
        }

        return FrameworkReturnCode::_SUCCESS;
    }
    catch (const fs::filesystem_error & e) {
        LOG_ERROR("ZipBufferUtils::extract - The following exception has been caught {}", e.what());
        return FrameworkReturnCode::_ERROR_;
    }
}
