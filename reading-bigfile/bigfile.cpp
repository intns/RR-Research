#include <bigfile.hpp>
#include <string>
#include <iostream>

BigFile::Header::Header()
    : m_magic(0)
    , m_unk04(0)
    , m_unk08(0)
    , m_unk0C(0)
    , m_unk10(0)
    , m_tableOffset(0)
    , m_unk20(0)
    , m_unk24(0)
    , m_unk28(0)
    , m_fileCount(0)
    , m_unk30(0)
    , m_unk40(0)
    , m_unk44(0)
    , m_unk46(0)
{
}

void BigFile::Header::read(util::fstream_reader& reader)
{
    m_magic = reader.readU32();
    m_unk04 = reader.readU32();
    m_unk08 = reader.readU32();
    m_unk0C = reader.readU32();

    m_unk10 = reader.readU64();
    m_tableOffset = reader.readU64();

    m_unk20 = reader.readU32();
    m_unk24 = reader.readU32();
    m_unk28 = reader.readU32();
    m_fileCount = reader.readU32();
    m_unk30 = reader.readU32();

    reader.read_buffer((s8*)m_unk34, 0xC);

    m_unk40 = reader.readU32();
    m_unk44 = reader.readU16();
    m_unk46 = reader.readU16();
}

void BigFile::read(util::fstream_reader& reader)
{
    m_header.read(reader);

    if (m_header.m_unk44)
    {
        reader.readU32();

        struct DebugEntry {
            u32 m_unk00;
            u16 m_unk04;
            u16 m_unk06;
            std::string m_string;
        };

        for (int i = 0; i < 10; i++) {
            DebugEntry entry;
            entry.m_unk00 = reader.readU32();
            entry.m_unk04 = reader.readU16();
            entry.m_unk06 = reader.readU16();
            u8 toAdd = reader.readU8();
            while (toAdd) {
                entry.m_string += toAdd;
                toAdd = reader.readU8();
            }

            std::cout << entry.m_string << std::endl;
        }

        // 142
    }
}
