#include "Common/Core/Serialization/include/BlobSerializer.h"
#include <fstream>

#include "Base/Base.h"
#include "Common/Core/Serialization/include/SerializerSubsystem.h"
#include "Log/include/Log.h"
#include <filesystem>


namespace Phoenix
{
    BlobSerializer::BlobSerializer(Mode mode, std::string filePath)
    {
        m_mode = mode;
        if(!std::filesystem::exists(filePath))
        {
            // get directory path
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

    void BlobSerializer::Read(void* data, size_t size)
    {
        m_readFile->read((char*)data, size);
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

    // serialize header
    // void BlobSerializer::SerializeHeader(int data)
    // {
    //     memcpy(&m_buffer[0], &data, sizeof(data));
    //     m_offset += sizeof(data);
    // }
    // // serialize uint32_t data
    // void BlobSerializer::Serialize(int data)
    // {
    //     memcpy(&m_buffer[0], &data, sizeof(data));
    //     m_offset += sizeof(data);
    // }
    //
    // void BlobSerializer::Deserialize(uint32_t* data)
    // {
    //     memcpy(&data, &m_buffer[m_offset], sizeof(data));
    //     m_offset += sizeof(data);
    // }
    //
    // void BlobSerializer::SerializeTest(int data)
    // {
    //     // SerializeHeader(12);
    //     Serialize(data);
    // }
    //
    // void BlobSerializer::Write()
    // {
    //     auto u = std::filesystem::current_path().string();
    //     std::ofstream file(m_filePath);
    //     if(!file.is_open())
    //     {
    //         PX_CORE_ASSERT(false, "File has not been created!");
    //         // std::ofstream file(m_filePath);
    //         // file << "This is a new file";
    //         // file.close();
    //         return;
    //     }
    //     file.write((char*)&m_buffer, m_offset);
    //     file.close();
    // }
    //
    // void BlobSerializer::Read()
    // {
    //     std::ifstream file(m_filePath);
    //     if(!file.is_open())
    //     {
    //         PX_CORE_ASSERT(false, "Could not open file!");
    //     }
    //     file.read((char*)&m_buffer, 4);
    //     auto s = reinterpret_cast<int*>(m_buffer);
    // }
}   
