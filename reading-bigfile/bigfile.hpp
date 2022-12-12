#ifndef _BIGFILE_HPP
#define _BIGFILE_HPP

#include <types.hpp>
#include <util/fstream_reader.hpp>

struct i64_ {
    i64_() {
        High = 0;
        Low = 0;
    }

    operator uint64_t() {
        return (((uint64_t)High) << 32) | ((uint64_t)Low);
    }

    int High;
    int Low;
};

struct TOOarray {
    void* md_Array;
    unsigned int mu32_SizeElem;
    unsigned int mu32_GranArray;
    unsigned int mu32_NumElem;
    unsigned int mu32_MaxElem;

    void create(u32 sizeOfElem, u32 maxElem, bool assignArray)
    {
        mu32_SizeElem = sizeOfElem;
        mu32_GranArray = maxElem;
        mu32_NumElem = 0;
        mu32_MaxElem = 0;

        if (assignArray) {
            if (maxElem != 0) {
                mu32_MaxElem = maxElem;
                md_Array = malloc(sizeOfElem * maxElem);
            } else {
                mu32_GranArray = 10;
                md_Array = nullptr;
            }
        } else {
            md_Array = nullptr;
        }
    }
};

struct TOOsarray : TOOarray {
    unsigned int mb_FastMode;
    unsigned int mb_FloatMode;
};

struct BIG_tt_Connect_ {
    char az_User[16];
    unsigned int u32_Rights;
};

struct BIG_tt_Header_ {
    unsigned int u32_Mark;
    unsigned int u32_Version;
    unsigned int u32_Tick;
    unsigned int u32_NumFatFiles;
    unsigned int u32_NumFatDirs;
    i64_ i64_PosFirstFatFiles;
    i64_ i64_PosFirstFatDirs;
    unsigned int u32_MaxFiles;
    unsigned int u32_MaxDirs;
    unsigned int u32_NumFiles;
    unsigned int u32_NumDirs;
    unsigned int h_FirstFreeFile;
    unsigned int h_FirstFreeDir;
    i64_ i64_FirstFreePos;
    unsigned int u32_Param1;
    unsigned int u32_Param2;
    unsigned int u32_Param3;
    unsigned int u32_Param4;
    BIG_tt_Connect_ at_Users[255];
    char az_PerforceClientName[130];
    char az_PerforceClientLastAccessTime[20];
};

struct BIG_tt_File_ {
    BIG_tt_File_() {  }

    char az_Name[64];
    unsigned int u32_LengthDisk;
    unsigned int h_Key;
    i64_ i64_Pos;
    unsigned __int16 u16_PermanentFlags;
};

struct BIG_tt_Dir_ {
    char az_Name[64];
    unsigned int h_ParentDir;
    unsigned int h_FirstSubDir;
    unsigned int h_NextDir;
    unsigned int h_FirstFile;
    unsigned __int16 u16_PermanentFlags;
    unsigned __int16 u16_VolatileFlags;
    unsigned int u32_Revision;
    unsigned int u32_DUMMY;
    unsigned int u32_RevisionDC;
    unsigned int u32_DUMMY1;
};

struct BIG_tt_Fat_ {
    unsigned int u32_Size;
    i64_ i64_NextFatPos;
};

struct BIG_tt_TmpBuffer_ {
    void* p_Buf;
    unsigned int u32_Len;
    unsigned int u32_Size;
};

struct THR_LocalStorage {
    unsigned int mu32_Index;
};

struct BIG_tt_BigAccess_ {
    unsigned int mb_IsUsed;
    int mh_Handle;
    BIG_tt_TmpBuffer_* mt_TmpBufRead;
    BIG_tt_TmpBuffer_* mt_TmpBufWrite;
    BIG_tt_TmpBuffer_* mt_TmpBufRef;
};

struct BIG {
    char maz_Name[1024];
    unsigned int mu32_Flags;
    TOOsarray* mpo_KeyToPos;
    BIG_tt_Header_ mt_Header;
    BIG_tt_File_* mdt_FatFiles;
    BIG_tt_Dir_* mdt_FatDirs;
    BIG_tt_Fat_* mdt_FatDescFiles;
    BIG_tt_Fat_* mdt_FatDescDirs;
    BIG_tt_TmpBuffer_ mt_TmpBufComp;
    BIG_tt_TmpBuffer_ mt_TmpBufDict;
    THR_LocalStorage* mLS;
    BIG_tt_BigAccess_ mat_ThreadBigAccess[5];
    unsigned int mb_readonly;
};

struct BigFile : public BIG {
    BigFile();
    ~BigFile() = default;

    void read(util::fstream_reader& reader);
    void readFATFiles(util::fstream_reader& reader);
};

#endif