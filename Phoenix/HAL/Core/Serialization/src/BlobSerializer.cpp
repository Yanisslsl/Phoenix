#include "Core/Serialization/include/BlobSerializer.h"
#include <fstream>
#include "Base/Base.h"
#include "Log/include/Log.h"
#include <filesystem>
#include "Core/Serialization/include/SerializerSubsystem.h"


namespace Phoenix
{
    BlobSerializer::BlobSerializer(Mode mode, std::string filePath)
    {
        m_mode = mode;
        if(!std::filesystem::exists(filePath))
        {
            std::string directoryPath = filePath.substr(0, filePath.find_last_of("\\"));
            std::filesystem::create_directories(directoryPath);
        }
        if(mode == Mode::Write)
        {
            m_writeFile = new std::ofstream(filePath);
            if(!m_writeFile->is_open())
            {
                PX_CORE_ASSERT(false, "Could not open file!");
            }
        } else
        {
            m_readFile = new std::ifstream(filePath);
            if (!m_readFile->is_open())
            {
                PX_CORE_ASSERT(false, "Could not open file!");
            }
        }
    }
    
    void BlobSerializer::Write( const void* data, size_t size)
    {
        m_writeFile->write((char*)data, size);
    }

    void BlobSerializer::WriteString(const std::string& data)
    {
        size_t size = data.size();
        m_writeFile->write((char*)&size, sizeof(size_t));
        m_writeFile->write(data.c_str(), size);
    }

    void BlobSerializer::Read(void* data, size_t size)
    {
        m_readFile->read((char*)data, size);
    }

    void BlobSerializer::ReadString(std::string& data)
    {
        size_t dataSize;
        m_readFile->read((char*)&dataSize, sizeof(size_t));
        data.resize(dataSize);
        m_readFile->read(data.data(), dataSize);
    }

    void BlobSerializer::WriteHeader(SerializableType type, uint32_t version)
    {
        m_writeFile->write((char*)&type, sizeof(type));
        m_writeFile->write((char*)&version, sizeof(version));
    }

    BlobHeader BlobSerializer::ReadHeader()
    {
        BlobHeader header;
        m_readFile->read((char*)&header.type, sizeof(header.type));
        m_readFile->read((char*)&header.version, sizeof(header.version));
        return header;
    }

    void BlobSerializer::Flush()
    {
        m_writeFile->flush();
    }

    BlobSerializer::~BlobSerializer()
    {
        if(m_mode == Mode::Write)
        {
            m_writeFile->close();
            delete m_writeFile;
        } else
        {
            m_readFile->close();
            delete m_readFile;
        }
    }

    bool BlobSerializer::HasData()
    {
        return m_readFile->peek() != EOF;
    }
}   
