#pragma once
#include <cstdint>
#include "Core.h"
#include "Utils/FileSystem.h"


namespace Phoenix
{
    /** 
     * \brief BlobHeader struct
     *        Used to store the header of a serialized class, to be able to read it back
     */
    struct BlobHeader
    {
        uint32_t type;
        uint32_t version;
    };

    /** 
     * \brief Mode enum class
     *        Used to specify the mode of the BlobSerializer
     */
    enum class Mode : uint32_t
    {
        Read = 0,
        Write
    };

    /** 
     * \brief BlobSerializer class
     *        Used to serialize and deserialize data
     */
    class PHOENIX_API BlobSerializer
    {
    public:
        BlobSerializer() = delete;
        /** 
         * \brief Constructor
         * \param mode the mode of the BlobSerializer
         * \param filePath the file path to serialize to or deserialize from
         */
        BlobSerializer(Mode mode, std::string filePath);
        ~BlobSerializer();

        /** 
         * \brief Write data to the file
         * \param data the data to write
         * \param size the size of the data
         */
        void Write(const void* data, size_t size);
        
        /** 
         * \brief Write a string to the file
         * \param data the string to write
         */
        void WriteString(const std::string& data);

        /** 
         * \brief Read data from the file
         * \param data the data to read
         * \param size the size of the data
         */
        void Read(void* data, size_t size);

        /** 
         * \brief Read a string from the file
         * \param data the string to read
         */
        void ReadString(std::string& data);

         /** 
         * \brief Write the header of the file
         * \param type the type of the header
         * \param version the version of the header
         */
        void WriteHeader(uint32_t type, uint32_t version = 1.0);

         /** 
         * \brief Get if the file still has data
         * \return bool whether the file still has data
         */
        bool HasData();

        /**
         * \brief Read header 
         * \return BlobHeader
         */
        BlobHeader ReadHeader();

        /**
         * \brief Flush the file
         */
        void Flush();
    private:
        std::ofstream* m_writeFile;
        std::ifstream* m_readFile;
        Mode m_mode;
    };
}
