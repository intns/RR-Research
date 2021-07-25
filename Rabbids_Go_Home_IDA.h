typedef unsigned long long u64;
typedef unsigned long u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef signed long long s64;
typedef signed long s32;
typedef signed short s16;
typedef signed char s8;

typedef float f32;
typedef double f64;

struct TOOarray
{
	u32* m_elements; // 0
	u32 m_elemSize; // 4
	u32 m_unk8; // 8
	u32 m_elemCount; // C
	u32 m_maxElems; // 10, guessed name
};

struct TOOsarray : public TOOarray
{
	// should be 0x1C in size
	u32 m_fastMode; // 14, fastmode
	u32 m_sortOrder; // 18, decides which qsort comparison to use (if non-zero, greater than, if zero, less than)
};

struct K3D_VisualInstance {};

struct BIG_tt_FileHeader_ {};
struct BIG_tt_DynAccess {};

struct BIG_VTBL
{
	void (*Destructor)(void);
	void (*Destroy)(void);
	bool (*b_IOCreateBigFile)(char*);
	bool (*b_IOOpenBigFile)(char*, u32);
	void (*IOCloseBigFile)(void);
	bool (*b_IOReadBigFile)(void*, u32);
	void (*b_IOReadBigFileAsync)(void*, u32, s64, void*, void*);
	void (*b_IOWriteBigFile)(void*, u32);
	void (*i64_IOSeekBigFile)(s64, u32);
	bool (*b_IOLockBigFile)(s64, u32, u32);
	bool (*b_IOUnlockBigFile)(s64, u32);
	void (*IOGetTime64BigFile)(u32*);
	bool (*i32_IOCompareTime64BigFile)(u32*, u32*);
	s64 (*i64_IOGetFileLength)(void);
	void (*ReadFileHeader)(s64, BIG_tt_FileHeader_*);
	void (*b_ReadFileHeaderAsync)(s64, BIG_tt_FileHeader_*, void*);
	void (*b_ReadFileShortcutPriv)(BIG_tt_FileHeader_*, void*, void*);
	void (*b_ReadFilePriv)(BIG_tt_FileHeader_*, void*, void*);
	void (*u32_TestSpecific4)(u32, u32, u32);
	void (*u32_SetSnP)(u32);
	void (*UseIt)(K3D_VisualInstance*, u32);
	void (*b_ReadDynAccess)(BIG_tt_DynAccess*, void*, u32, u32);
	void (*b_ReadDynAccessAsyncWait)(BIG_tt_DynAccess*, void*, u32, u32, void*);
	void (*b_ReadDynAccessAsyncNoWait)(BIG_tt_DynAccess*, void*, u32, u32, void*, void*);
	void (*b_Read)(void);
	void (*RegisterThread)(void);
	void (*UnregisterThread)(void);
	void (*GetBigAccess)(void);
};

struct BIG
{
	BIG_VTBL* m_vtbl; // 0
	u8 m_padding4[1024]; // 400
	u32 m_fileFlags; // 404
	TOOsarray* m_keys; // 408
	u32 m_fileMagic; // 40C
	u32 m_unk410;
	u32 m_unk414;
	u32 m_unk418;
	u32 m_unk41C;
	u32 m_unk420;
	u32 m_unk424;
	u32 m_unk428;
	u32 m_unk42C;
	u32 m_unk430;
	u8 m_padding434[5296]; // 14B0
	u32 m_unk18E4;
	u32 m_unk18E8;
	u32 m_unk18EC;
	u32 m_unk18F0;
	u8 m_unk18F4[12];
	u8 m_unk1900[12];
	u32 m_unk190C;
	u8 m_unk1910[100];
	u32 m_unk1974;
};

struct BIG_S_P4 : public BIG
{
	u32 m_threads[50]; // 1978
	u32 m_threadCount; // 197C
};