#include "core/ScopedTempDir.h"
#include <random>

namespace fs = std::filesystem;

using namespace SolAR;
using namespace SolAR::util;

ScopedTempDir::ScopedTempDir()
{
    fs::path base_path = fs::temp_directory_path();

    // Generate a random name for temporary subdirectory
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dis;
    do {
        std::string random_name = "tmp_" + std::to_string(dis(gen));
        m_tempPath = base_path / random_name;
    } while (fs::exists(m_tempPath));

    // Create the temporary subdirectory
    std::error_code ec;
    fs::create_directories(m_tempPath, ec);
}

ScopedTempDir::~ScopedTempDir()
{
    // Delete the temporary directory (and its contents)
    std::error_code ec; fs::remove_all(m_tempPath, ec);
}

const fs::path& ScopedTempDir::getPath() const
{
    return m_tempPath;
}

const std::string ScopedTempDir::getStringPath() const
{
    return m_tempPath.string();
}
