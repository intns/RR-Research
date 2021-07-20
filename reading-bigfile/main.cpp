#include <bigfile.hpp>
#include <fstream>
#include <iostream>

/*
struct BIG_HEADER
{
	u32 m_magic = 0;
	u32 m_unk4 = 0;
	u32 m_unk8 = 0;
	u32 m_unkC = 0;

	u64 m_unk10 = 0;
	u64 m_tableOffset = 0;
	
	void read(std::ifstream& file)
	{
		m_magic = readS32(file);
		m_unk4 = readS32(file);
		m_unk8 = readS32(file);
		m_unkC = readS32(file);

		m_unk10 = readS64(file);
		m_tableOffset = readS64(file);
		std::printf("%d\n%d\n%d\n%d\n%lld\n%lld\n", m_magic, m_unk4, m_unk8, m_unkC, m_unk10, m_tableOffset);
	}
};

int main(int argc, char** argv)
{
	std::ifstream a("rgh.bf", std::ios_base::binary);
	util::fstream_reader reader(a);

	BIG_HEADER header;
	header.read(a);
	if (header.m_magic != 'EBA')
	{
		std::cout << "Incorrect magic\n";
		return EXIT_FAILURE;
	}

	//a.seekg(0x2C, std::ios_base::_Seekbeg);
	//int files = readS32(a);

	return EXIT_SUCCESS;
}*/

int main(int argc, char** argv)
{
    std::ifstream bigfileStream("RGH.BF");
    util::fstream_reader reader(bigfileStream);

	BigFile file;
    file.read(reader);

    return EXIT_SUCCESS;
}