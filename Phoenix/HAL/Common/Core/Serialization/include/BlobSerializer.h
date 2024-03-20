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
    
    class PHOENIX_API BlobSerializer
    {
    public:
        BlobSerializer() = delete;
        BlobSerializer(std::string filePath);
        ~BlobSerializer();
        void Write(const void* data, size_t size);
        void Read(void* data, size_t size);
        void WriteHeader(uint32_t type, uint32_t version = 1.0);
        BlobHeader ReadHeader();
        void Flush();
    private:
        std::ofstream* m_writeFile;
        std::ifstream* m_readFile;
    };
}
