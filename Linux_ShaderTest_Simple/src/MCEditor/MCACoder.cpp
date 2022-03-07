#include "MCACoder.h"
//#include "MCEditor.h"
#include <cstring>
#include <cstdlib>
#include <queue>
#include <algorithm>
#include "globals.h"
using namespace std;

//string file_name_MCA;

extern int toggle();
extern int toggle2();
extern int toggle3();

void MCACoder::saveModification() {
//    current_filename_mca=file_name_MCA;
    if (!modification_saved)
        writeMCA();
    for (int i = 0; i < K1; i++)
    {
        nbt_coder.Clear(Chunk[i]);
        Chunk[i] = 0;
    }
    current_filename_mca = "";
    modification_saved = true;
}

void MCACoder::clearModification() {
    for (int i = 0; i < K1; i++)
    {
        nbt_coder.Clear(Chunk[i]);
        Chunk[i] = 0;
    }
    current_filename_mca = "";
    modification_saved = true;
}

//extern int chunk_offsetx;
//extern int chunk_offsetz;

void MCACoder::setPOSITIONS() {
    for (int x=0; x<32; x++) {
        for (int z=0; z<32; z++) {
            node *chunk_root = Chunk[x+z*32];
            if (!(chunk_root==0)) {
                node *level_root = chunk_root->childWithName("Level");
                if (!(level_root==0)) {
                    node *pos=level_root->childWithName("xPos");
                    if (!(pos==0)) {
                        pos->tag.vi=chunk_offsetx+x;
                    }
                    pos=level_root->childWithName("zPos");
                    if (!(pos==0)) {
                        pos->tag.vi=chunk_offsetz+z;
                    }
                }
            }
        }
    }
}

void MCACoder::setBlock(const Pos &position, const BlockInfo &info) {
    int x = position.x, z = position.z, y = position.y;

    int chunk_x = x >> 4, chunk_z = z >> 4;
    int region_x = chunk_x >> 5, region_z = chunk_z >> 5;

    int idx = (chunk_x & 31) + 32 * (chunk_z & 31);
    node *chunk_root = Chunk[idx];

    if (!chunk_root) { return; }

    modification_saved = false;

    int sec_no = y >> 4;

    node *level_root;
    node *sec_root;
    node *T;

    if (old_idx==idx && old_sec_no==sec_no && !old_T==0 && !old_sec_root==0) {
        sec_root=old_sec_root;
        T=old_T;
    } else {
        if (!(old_sec_root==0) && idx==old_idx) {
            sec_root=old_sec_root;
        } else {
            level_root = chunk_root->childWithName("Level");
            sec_root = level_root->childWithName("Sections");
        }
        if (old_idx==idx && old_sec_root==sec_root && sec_no==old_sec_no && (!(old_T==0)))
            T = old_T;
        else
            T = sectionNodeWithY(sec_root, sec_no);
    }

    if (!T) { T = newSectionNodeWithY(sec_no); sec_root->addChild(T); }

    node *u;
    int block_x = (x & 15), block_z = (z & 15), block_y = (y & 15);
    int block_pos = block_y * 16 * 16 + block_z * 16 + block_x;

    static node *old_u_blocks=0;

    if (old_T==T && !(old_u_blocks==0)) {
        u=old_u_blocks;
    } else {
        u = T->childWithName("Blocks");
        old_u_blocks=u;
    }
    nbt_coder.setByteInArrayContent(u, block_pos, (uc)info.id);

    static node *old_u_add=0;

    if (!(old_T==T)) {
        u = T->childWithName("Add");
        old_u_add=u;
    } else {
        u=old_u_add;
    }

    if (u || info.add)
    {
        if (!u)
        {
            u = new node(TAG_BYTE_ARRAY, "Add");
            u->tag.va.resize(K2);
            T->addChild(u);
            old_u_add=u;
        }
        nbt_coder.setHalfByteInArrayContent(u, block_pos, info.add);
    }

    static node *old_u_data=0;

    if (old_T==T && !(old_u_data==0)) {
        u=old_u_data;
    } else {
        u = T->childWithName("Data");
        old_u_data=u;
    }
    nbt_coder.setHalfByteInArrayContent(u, block_pos, info.data);

    static node *old_u_blocklight=0;

    if (old_T==T && !(old_u_blocklight==0)) {
        u=old_u_blocklight;
    } else {
        u = T->childWithName("BlockLight");
        old_u_blocklight=u;
    }
    nbt_coder.setHalfByteInArrayContent(u, block_pos, info.block_light);

    static node *old_u_skylight=0;

    if (old_T==T && !(old_u_skylight==0)) {
        u=old_u_skylight;
    } else {
        u = T->childWithName("SkyLight");
        old_u_skylight=u;
    }
    nbt_coder.setHalfByteInArrayContent(u, block_pos, info.sky_light);

    old_idx=idx;
    old_sec_no=sec_no;
    old_T=T;
    old_sec_root=sec_root;
}

void MCACoder::reset_block() {
    getblock_old_idx=0;
    getblock_old_sec_no=0;
    getblock_old_T=0;
    getblock_old_sec_root=0;
}

BlockInfo MCACoder::getBlock(int x, int z, int y)
{
    int chunk_x = x >> 4, chunk_z = z >> 4;
    int region_x = chunk_x >> 5, region_z = chunk_z >> 5;

    int idx = (chunk_x & 31) + 32 * (chunk_z & 31);
    node *T;
    node *chunk_root = Chunk[idx];
    node *level_root;
    node *sec_root;

    if (!chunk_root) {  return BlockInfo();  }

    int sec_no = y >> 4;

    if (getblock_old_idx==idx && getblock_old_sec_no==sec_no && !getblock_old_T==0 && !getblock_old_sec_root==0) {
        sec_root=getblock_old_sec_root;
        T=getblock_old_T;
    } else {
        if (!(getblock_old_sec_root==0) && idx==getblock_old_idx) {
            sec_root=getblock_old_sec_root;
        } else {
            level_root = chunk_root->childWithName("Level");
            sec_root = level_root->childWithName("Sections");
        }
        if (getblock_old_idx==idx && getblock_old_sec_root==sec_root && sec_no==getblock_old_sec_no && (!(getblock_old_T==0)))
            T = getblock_old_T;
        else
            T = sectionNodeWithY(sec_root, sec_no);
    }


    if (!T) { return BlockInfo(); }


    node *u;
    int block_x = (x & 15), block_z = (z & 15), block_y = (y & 15);
    int block_pos = block_y * 16 * 16 + block_z * 16 + block_x;

    static node *old_u_blocks=0;

    if (getblock_old_T==T) {
        u=old_u_blocks;
    } else {
        u = T->childWithName("Blocks");
        old_u_blocks=u;
    }
    int id = nbt_coder.getByteInArrayContent(u, block_pos);

    static node *old_u_add=0;

    if (getblock_old_T==T) {
        u=old_u_add;
    } else {
        u = T->childWithName("Add");
        old_u_add=u;
    }
    int add = u ? nbt_coder.getHalfByteInArrayContent(u, block_pos) : 0;


    static node *old_u_data=0;

    if (getblock_old_T==T) {
        u=old_u_data;
    } else {
        u = T->childWithName("Data");
        old_u_data=u;
    }
    int data = u ? nbt_coder.getHalfByteInArrayContent(u, block_pos) : 0;


    static node *old_u_blocklight=0;

    if (getblock_old_T==T) {
        u=old_u_blocklight;
    } else {
        u = T->childWithName("BlockLight");
        old_u_blocklight=u;
    }
    int block_light = nbt_coder.getHalfByteInArrayContent(u, block_pos);

    static node *old_u_skylight=0;

    if (getblock_old_T==T) {
        u=old_u_skylight;
    } else {
        u = T->childWithName("SkyLight");
        old_u_skylight=u;
    }
    int sky_light = nbt_coder.getHalfByteInArrayContent(u, block_pos);

    getblock_old_idx=idx;
    getblock_old_sec_no=sec_no;
    getblock_old_T=T;
    getblock_old_sec_root=sec_root;
    return BlockInfo(id, add, data, block_light, sky_light);
}

void MCACoder::removeBlockEntity(const Pos &position)
{
    int x = position.x, z = position.z, y = position.y;

    int chunk_x = x >> 4, chunk_z = z >> 4;
    int region_x = chunk_x >> 5, region_z = chunk_z >> 5;

    int idx = (chunk_x & 31) + 32 * (chunk_z & 31);
    node *chunk_root = Chunk[idx];
    if (!chunk_root) return;

    node *level_root = chunk_root->childWithName("Level");
    node *T = level_root->childWithName("TileEntities");

    int totx=region_xxx*512;
    int totz=region_zzz*512;

    for (auto it = T->ch.begin(); it != T->ch.end(); it++)
    {
        node *u = *it;
        if (u->ch.empty()) continue;

        node *v;
        v = u->childWithName("x");
        int x = v->tag.vi;
        v = u->childWithName("z");
        int z = v->tag.vi;
        v = u->childWithName("y");
        int y = v->tag.vi;
        if (!(position == Pos(x-totx, z-totz, y))) {
            continue;
        }
        delete u;
        it = T->ch.erase(it);
        modification_saved = false;
        break;
    }
}

void MCACoder::insertEntity(const Pos &position, MobEntity *entity)
{
    if (!entity)
        return;

    int x = position.x, z = position.z, y = position.y;

    node *chunk_root = chunkWithXZ(x, z);
    if (!chunk_root) {  fprintf(stderr,"3) Chunk that contains (%d, ?, %d) is not initialized\n",x, z); return;  }

    node *level_root = chunk_root->childWithName("Level");
    node *T = level_root->childWithName("Entities");
    if (!T) { /* fprintf(stderr,"TileEntities does not exits (%d, %d, %d)\n", x, y, z);*/ return; }

    T->tag.ch_type = TAG_COMPOUND;
    T->addChild(newEntityNode(entity));
    modification_saved = false;
}


void MCACoder::insertBlockEntity(const Pos &position, BlockEntity *entity) {
    if (!entity)
        return;

    int x = position.x, z = position.z, y = position.y;

    node *chunk_root = chunkWithXZ(x, z);
    if (!chunk_root) {  fprintf(stderr,"3) Chunk that contains (%d, ?, %d) is not initialized\n",x, z); return;  }

    node *level_root = chunk_root->childWithName("Level");
    node *T = level_root->childWithName("TileEntities");
    if (!T) {  return; }

    T->tag.ch_type = TAG_COMPOUND;
    T->addChild(newBlockEntityNode(entity));
    modification_saved = false;
}

void MCACoder::setHeightMap(int x, int z, int y) {
    node *chunk_root = chunkWithXZ(x, z);
    if (!chunk_root) return;

    node *level_root = chunk_root->childWithName("Level");
    node *T = level_root->childWithName("HeightMap");

    int block_x = (x & 15), block_z = (z & 15);
    int col_pos = block_z * 16 + block_x;
    int h = min((int)nbt_coder.getByteInArrayContent(T, col_pos), y);
    nbt_coder.setByteInArrayContent(T, col_pos, 0);
}

int MCACoder::loadMCA(const string &file_name_MCA)
{
    if (current_filename_mca == file_name_MCA) return 0;

    printf("Loading %s ", file_name_MCA.c_str());

    if (current_filename_mca != "") saveModification();

    FILE *handle = fopen(file_name_MCA.c_str(), "rb");
    if (!handle) return -1;

    current_filename_mca = file_name_MCA;

    fread(buffer, 1, K4, handle);
    for (int i = 0; i < K4; i += 4)  location[i >> 2] = K4 * byteToInt(buffer, i, 3);

    fread(buffer, 1, K4, handle);

    for (int i = 0; i < K4; i += 4) timestamp[i >> 2] = byteToInt(buffer, i, 4);

    for (int i = 0; i < K1; i++) {
        if (location[i]) {
            fseek(handle, location[i], SEEK_SET);

            fread(buffer, 1, 4, handle);
            int chunk_len = (int)byteToInt(buffer, 0, 4);
            chunk_len--;

            fread(buffer, 1, 1, handle);
            int cmpr_type = byteToInt(buffer, 0, 1);

            if (cmpr_type != 2)
            {
                fprintf(stderr, "Decompression Type Error: %d.\n", cmpr_type);
                exit(0);
            }

            chunk_len = fread(buffer, 1, chunk_len, handle);

            decompress(chunk_buffer, sizeof(chunk_buffer), buffer, chunk_len);

            Chunk[i] = nbt_coder.Decode(chunk_buffer);

        } else {
            Chunk[i] = 0;
        }
    }

    fclose(handle);

    return 0;
}

void MCACoder::writeMCA()
{
    printf("- Saving %s",current_filename_mca.c_str());
    memset(buffer, 0, sizeof(buffer));

    ull offset = K4 << 1;
    for (int i = 0; i < K1; i++)
    {
        if (!Chunk[i])
        {
            intToByte(0, buffer, i << 2, 3);
            intToByte(0, buffer, (i << 2) + 3, 1);
            continue;
        }

        intToByte(offset / K4, buffer, i << 2, 3);

        ull chunk_len = nbt_coder.Encode(Chunk[i], chunk_buffer);
        ull cmpr_len = compress(buffer + offset + 5, sizeof(buffer) - (offset + 5),
                                chunk_buffer, chunk_len);

        cmpr_len++;
        intToByte(cmpr_len, buffer, offset, 4);
        cmpr_len += 4;
        intToByte(2, buffer, offset + 4, 1);

        ull sector_cnt = 0;
        if (cmpr_len % K4 == 0)
            sector_cnt = cmpr_len / K4;
        else
            sector_cnt = cmpr_len / K4 + 1;

        intToByte(sector_cnt, buffer, (i << 2) + 3, 1);
        cmpr_len = sector_cnt * K4; //Pad to a multiple of K4
        offset += cmpr_len;
        toggle2();
    }

    for (int i = 0; i < K1; i++) {
        intToByte(timestamp[i], buffer, K4 + (i << 2), 4);
        toggle2();
    }

    remove(current_filename_mca.c_str());
    FILE *handle = fopen(current_filename_mca.c_str(), "wb");
    fwrite(buffer, 1, offset, handle);
    fclose(handle);
    printf("\n");
}

node *MCACoder::chunkWithXZ(int x, int z) {
    int chunk_x = x >> 4, chunk_z = z >> 4;
    int region_x = chunk_x >> 5, region_z = chunk_z >> 5;

    int idx = (chunk_x & 31) + 32 * (chunk_z & 31);
    return Chunk[idx];
}

node *MCACoder::sectionNodeWithY(node *T, int y)
{
    for (node *u : T->ch)
    {
        node *v = u->childWithName("Y");
        if (v->tag.vi == y)
            return u;
    }
    return 0;
}

node *MCACoder::newSectionNodeWithY(int y) {
    node *u;
    node *T = new node(TAG_COMPOUND, "none");

    u = new node(TAG_BYTE, "Y");
    u->tag.vi = y;
    T->addChild(u);

    u = new node(TAG_BYTE_ARRAY, "Blocks");
    u->tag.va.resize(K4, 0);
    T->addChild(u);

    u = new node(TAG_BYTE_ARRAY, "Data");
    u->tag.va.resize(K2, 0);
    T->addChild(u);

    u = new node(TAG_BYTE_ARRAY, "BlockLight");
    u->tag.va.resize(K2, 0);
    T->addChild(u);

    u = new node(TAG_BYTE_ARRAY, "SkyLight");
    u->tag.va.resize(K2, 0xFF);
    T->addChild(u);

    return T;
}

node *MCACoder::newBlockEntityNode(BlockEntity *entity) {
    node *u;

    node *T = new node(TAG_COMPOUND, "none");

    u = new node(TAG_STRING, "id");
    u->tag.vs = entity->entity_id;
    T->addChild(u);

    u = new node(TAG_INT, "x");
    u->tag.vi = entity->position.x;
    T->addChild(u);

    u = new node(TAG_INT, "y");
    u->tag.vi = entity->position.y;
    T->addChild(u);

    u = new node(TAG_INT, "z");
    u->tag.vi = entity->position.z;
    T->addChild(u);

    if (entity->entity_id == "minecraft:noteblock")
    {
        BlockEntityNote *noteblock = (BlockEntityNote *)entity;

        u = new node(TAG_BYTE, "note");
        u->tag.vi = noteblock->note;
        T->addChild(u);

        u = new node(TAG_BYTE, "powered");
        u->tag.vi = noteblock->powered;
        T->addChild(u);
    }

    if (entity->entity_id == "minecraft:command_block")
    {
        BlockEntityCommand *cmdblock = (BlockEntityCommand*)entity;

        u = new node(TAG_STRING, "Command");
        u->tag.vs = cmdblock->command;
        T->addChild(u);

        u = new node(TAG_INT, "SuccessCount");
        u->tag.vi = 0;
        T->addChild(u);

        u = new node(TAG_STRING, "LastOutput");
        u->tag.vs = "";
        T->addChild(u);

        u = new node(TAG_BYTE, "TrackOutput");
        u->tag.vi = 0;
        T->addChild(u);

        u = new node(TAG_BYTE, "powered");
//        u->tag.vi = 0;
        u->tag.vi = cmdblock->powered;
        T->addChild(u);

        u = new node(TAG_BYTE, "auto");
//        u->tag.vi = 0;
        u->tag.vi = cmdblock->automatic;
        T->addChild(u);

        u = new node(TAG_BYTE, "conditionMet");
        u->tag.vi = 1;
        T->addChild(u);

        u = new node(TAG_BYTE, "UpdateLastExecution");
        u->tag.vi = 1;
        T->addChild(u);

        u = new node(TAG_LONG, "LastExecution");
        u->tag.vi = 0;
        T->addChild(u);
    }

    return T;
}

static ll UUIDLeast=0;

node *MCACoder::newEntityNode(MobEntity *entity) {
    node *u;
    node *u_sub;
    node *T = new node(TAG_COMPOUND, "none");


        u = new node(TAG_STRING, "id");
        u->tag.vs = entity->entity_id;
        T->addChild(u);

        u = new node(TAG_LIST, "Pos");
        u->tag.ch_type=TAG_DOUBLE;
            u_sub = new node(TAG_DOUBLE,"none");
            u_sub->tag.vf = (double)entity->position.x;
            u->addChild(u_sub);

            u_sub = new node(TAG_DOUBLE,"none");
            u_sub->tag.vf = (double)entity->position.y;
            u->addChild(u_sub);

            u_sub = new node(TAG_DOUBLE,"none");
            u_sub->tag.vf = (double)entity->position.z;
            u->addChild(u_sub);
        T->addChild(u);


        u = new node(TAG_LIST, "Motion");
        u->tag.ch_type=TAG_DOUBLE;
            u_sub = new node(TAG_DOUBLE,"none");
            u_sub->tag.vf = 0.0;
            u->addChild(u_sub);

            u_sub = new node(TAG_DOUBLE,"none");
            u_sub->tag.vf = 0.0;
            u->addChild(u_sub);

            u_sub = new node(TAG_DOUBLE,"none");
            u_sub->tag.vf = 0.0;
            u->addChild(u_sub);
        T->addChild(u);


        u = new node(TAG_LIST, "Rotation");
        u->tag.ch_type=TAG_FLOAT;
            u_sub = new node(TAG_FLOAT,"none");
            u_sub->tag.vf = 0.0;
            u->addChild(u_sub);

            u_sub = new node(TAG_FLOAT,"none");
            u_sub->tag.vf = 0.0;
            u->addChild(u_sub);
        T->addChild(u);


        u = new node(TAG_FLOAT, "FallDistance");
        u->tag.vf = 0.0;
        T->addChild(u);


        u = new node(TAG_SHORT, "Fire");
        u->tag.vi = 0;
        T->addChild(u);


        u = new node(TAG_SHORT, "Air");
        u->tag.vi = 300;
        T->addChild(u);


        u = new node(TAG_BYTE, "OnGround");
        u->tag.vi = 0;
        T->addChild(u);


        u = new node(TAG_INT, "Dimension");
        u->tag.vi = 0;
        T->addChild(u);


        u = new node(TAG_BYTE, "Invulnerable");
        u->tag.vi = 0;
        T->addChild(u);


        u = new node(TAG_INT, "PortalCooldown");
        u->tag.vi = 0;
        T->addChild(u);


        u = new node(TAG_LONG, "UUIDMost");
        u->tag.vi = region_xxx+region_zzz*1024;
        T->addChild(u);

        u = new node(TAG_LONG, "UUIDLeast");
        u->tag.vi = UUIDLeast++;
        T->addChild(u);

        u = new node(TAG_STRING, "CustomName");
        char name[100];
        if (entity->entity_id == "minecraft:tropical_fish") {
            int large=0;
            if ((rand()%11)<9) large=1;
            unsigned int Var=(unsigned int) ((large) | ( (rand()%7)*256) | ((rand()%15)*256*256) | ((rand()%15)*256*256*256));
            sprintf(name,"{\"text\":\"Variant_%d\"}",Var);
            u->tag.vs = name;
            T->addChild(u);

            u = new node(TAG_INT, "Variant");
            u->tag.vi = Var;
            T->addChild(u);
        } else {
            sprintf(name,"{\"text\":\"Pacman_Graphics_%d_%d_%d\"}",entity->position.x,entity->position.y,entity->position.z);
            u->tag.vs = name;
            T->addChild(u);
        }
    return T;
}


