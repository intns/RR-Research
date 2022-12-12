#include <bigfile.hpp>
#include <iostream>
#include <string>

template<typename T>
constexpr auto DATA_TO_U32(T x) { return (*((u32*)x)); }

template <typename T>
constexpr auto DATA_TO_U16(T x) { return (*((u16*)x)); }


BigFile::BigFile()
{
    std::memset(&mt_TmpBufComp, 0, sizeof(mt_TmpBufComp));
    std::memset(&mt_TmpBufDict, 0, sizeof(mt_TmpBufDict));
    std::memset(&maz_Name, 0, sizeof(maz_Name));
    std::memset(&mt_Header, 0, sizeof(mt_Header));
    mpo_KeyToPos = 0;
    mdt_FatFiles = 0;
    mdt_FatDirs = 0;
    mdt_FatDescFiles = 0;
    mdt_FatDescDirs = 0;
    mb_readonly = false;
    mLS = 0;
    mu32_Flags = 0;
}

void BigFile::read(util::fstream_reader& reader)
{
    // Read header
    reader.read_buffer((s8*)&mt_Header, sizeof(mt_Header));
    if (mt_Header.u32_Mark != 'EBA') {
        return;
    }

    // Read fat files
    mpo_KeyToPos = new TOOsarray();
    mpo_KeyToPos->create(12, mt_Header.u32_MaxFiles, true);

    mdt_FatFiles = new BIG_tt_File_[mt_Header.u32_MaxFiles];
    std::memset(mdt_FatFiles, 0, sizeof(BIG_tt_File_) * mt_Header.u32_MaxFiles);

    mdt_FatDescFiles = new BIG_tt_Fat_[mt_Header.u32_NumFatFiles];
    mdt_FatDescDirs = new BIG_tt_Fat_[mt_Header.u32_NumFatDirs];

    readFATFiles(reader);
}

void BigFile::readFATFiles(util::fstream_reader& reader)
{
    constexpr u32 MAX_FILE_SIZE = 102400;
    s8* fileData = new s8[MAX_FILE_SIZE];
    std::memset(fileData, 0, MAX_FILE_SIZE);

    i64_ filePosition = mt_Header.i64_PosFirstFatFiles;
    s32 fileCount = mt_Header.u32_NumFiles;
    u32 folderFileIndex = 0;

    for (u32 i = 0; i < mt_Header.u32_NumFatFiles; i++) {
        reader.setPosition(filePosition);
        reader.read_buffer((s8*)&mdt_FatDescFiles[i], sizeof(BIG_tt_Fat_));

        BIG_tt_Fat_& curFileDesc = mdt_FatDescFiles[i];
        u32 fileSize = std::min(curFileDesc.u32_Size, (u32)fileCount);

        for (u32 j = 0; j < fileSize;) {
            u32 readAmt = std::min(512u, fileSize - j);

            reader.read_buffer(fileData, 200 * readAmt);
            BIG_tt_File_* currFiles = &mdt_FatFiles[folderFileIndex + j];

            u32 internalPos = 0;
            for (u32 k = 0; k < readAmt; k++) {
                BIG_tt_File_& currFile = currFiles[k];
                s8* fileDataPos = &fileData[internalPos];

                // Copy file name
                std::strncpy(currFile.az_Name, fileDataPos, 64);
                currFile.az_Name[63] = '\0';

                currFile.u32_LengthDisk = DATA_TO_U32(&fileDataPos[88]);
                currFile.h_Key = DATA_TO_U32(&fileDataPos[100]);
                currFile.i64_Pos.High = DATA_TO_U32(&fileDataPos[104]);
                currFile.i64_Pos.Low = DATA_TO_U32(&fileDataPos[108]);
                currFile.u16_PermanentFlags = DATA_TO_U16(&fileDataPos[112]);

                internalPos += 200;
            }

            j += readAmt;
        }

        fileCount -= curFileDesc.u32_Size;
        folderFileIndex += curFileDesc.u32_Size;
        filePosition = curFileDesc.i64_NextFatPos;
    }
}
