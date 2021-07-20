#ifndef _BIGFILE_HPP
#define _BIGFILE_HPP

#include <types.hpp>
#include <util/fstream_reader.hpp>

struct BigFile {
    BigFile() = default;
    ~BigFile() = default;

    class Header {
    public:
        u32 m_magic;
        u32 m_unk04;
        u32 m_unk08;
        u32 m_unk0C;

        u64 m_unk10;
        u64 m_tableOffset;

        u32 m_unk20;
        u32 m_unk24;
        u32 m_unk28;
        u32 m_fileCount;
        u32 m_unk30;

        u8 m_unk34[0xC]; // all 0xFF

        u32 m_unk40;
        u16 m_unk44;
        u16 m_unk46;

        Header();
        ~Header() = default;

        void read(util::fstream_reader& reader);
    }; // sizeof is 0x48

    void read(util::fstream_reader& reader);

private:
    Header m_header;
};

#endif