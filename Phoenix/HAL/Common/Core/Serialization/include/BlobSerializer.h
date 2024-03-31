// BlobSerializer.h

#pragma once
#include <cstdint>
#include "Core.h"
#include "Utils/FileSystem.h"


namespace Phoenix
{
    struct BlobHeader
    {
        uint32_t type;
        uint32_t version;
    };

    enum class Mode : uint32_t
    {
        Read = 0,
        Write
    };
    
    class PHOENIX_API BlobSerializer
    {
    public:
        BlobSerializer() = delete;
        BlobSerializer(Mode mode, std::string filePath);
        ~BlobSerializer();
        void Write(const void* data, size_t size);
        void WriteString(const std::string& data);
        void Read(void* data, size_t size);
        void ReadString(std::string& data);
        void WriteHeader(uint32_t type, uint32_t version = 1.0);
        bool HasData();
        BlobHeader ReadHeader();
        void Flush();
    private:
        std::ofstream* m_writeFile;
        std::ifstream* m_readFile;
        Mode m_mode;
    };
}
