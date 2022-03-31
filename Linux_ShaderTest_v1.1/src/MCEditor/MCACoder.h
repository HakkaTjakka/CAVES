#ifndef MCACoder_h
#define MCACoder_h

#include <string>
#include <cstdlib>
#include "NBTCoder.h"
#include "BlockEntity.h"

class MCRegion
{
public:
    BlockInfo*** A;
    BlockEntity**** B;

    int x_len, z_len, y_len,
        x_ori, z_ori, y_ori;

    int region_x,region_z;
    MCRegion() {};

    MCRegion(int r_x, int r_z, int x0, int z0, int y0,
             int xl, int zl, int yl);

    ~MCRegion();

    void delBlockEntity(BlockEntity* entity);
};

class MCACoder
{
public:
    MCACoder()
    : modification_saved(true), current_filename_mca("")
    {
        memset(Chunk, 0, sizeof(Chunk));
    }

    void setPOSITIONS();

    void saveModification();

    void clearModification();

    void setBlock(const Pos &position, const BlockInfo &info);
//    void setBlock_old(const Pos &position, const BlockInfo &info);

    BlockInfo getBlock(int x, int z, int y);

    void getBlock_FAST(const MCRegion &region);

    void setBlock_FAST(const MCRegion &region);

    void removeBlockEntity(const Pos &position);

    void insertBlockEntity(const Pos &position, BlockEntity* entity);

    void insertEntity(const Pos &position, MobEntity* entity);

    void setHeightMap(int x, int z, int y);

    void writeMCA();

    int loadMCA(const std::string &file_name_MCA);

    std::string current_filename_mca;

    bool modification_saved;

    int remove_block_entities;

    void reset_block(int region_x, int regoin_z);

    int old_idx=0;
    int old_sec_no=0;
    node *old_T=0;
    node *old_sec_root=0;

    int getblock_old_idx=0;
    int getblock_old_sec_no=0;
    node *getblock_old_T=0;
    node *getblock_old_sec_root=0;

    int chunk_offsetx;
    int chunk_offsetz;
    int region_xxx;
    int region_zzz;

private:
    NBTCoder nbt_coder;

    node* Chunk[K1];

    uc buffer[M256], chunk_buffer[M1 << 1];

    int location[K1], timestamp[K1];

    node* chunkWithXZ(int x, int z);

    node* sectionNodeWithY(node* T, int y);

    node* newSectionNodeWithY(int y);

    node* newBlockEntityNode(BlockEntity* entity);

    node *newTileTickRoot();

    node* newBlockTickNode(BlockEntity* entity);

    node* newEntityNode(MobEntity* entity);
};

#endif
