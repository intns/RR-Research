#include <bigfile.hpp>
#include <bitset>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    std::ifstream stream("RxN.$hd$.bik.bf");
    util::fstream_reader reader(stream);

    BigFile file;
    file.read(reader);

    for (u32 i = 0; i < 255; i++) {
        const auto& user = file.mt_Header.at_Users[i];
        if (user.az_User[0] == '\0') {
            break;
        }

        for (u32 j = 0; j < 12; j++) {
            if (user.az_User[j] == '\0') {
                memset((void*)&user.az_User[j], ' ', 1);
            }
        }

        std::cout << "USER: " << user.az_User << " RIGHTS:\T" << std::hex << user.u32_Rights << std::dec << std::endl;
    }

    std::cout << "FAT FILES" << std::endl;
    for (u32 i = 0; i < file.mt_Header.u32_NumFatFiles; i++) {
        BIG_tt_File_& fatFile = file.mdt_FatFiles[i];

        reader.setPosition(fatFile.i64_Pos.Low);

        s8* file = new s8[fatFile.u32_LengthDisk];
        reader.read_buffer(file, fatFile.u32_LengthDisk);

        std::ofstream out(fatFile.az_Name);
        out.write((const char*)file, fatFile.u32_LengthDisk);
        out.close();

        delete[] file;

        std::cout << "FILENAME: " << fatFile.az_Name << std::endl;
        std::cout << "FILESIZE: " << fatFile.u32_LengthDisk << std::endl
                  << std::endl;
    }

    return EXIT_SUCCESS;
}