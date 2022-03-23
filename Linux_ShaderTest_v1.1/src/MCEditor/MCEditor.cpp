#include "MCEditor.h"
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <set>
#include <cstring>
#include "globals.h"

using namespace std;
//extern int old_idx;
//extern int old_sec_no;
//extern node *old_T;
//extern node *old_sec_root;

extern int first;
extern int toggle3();
extern int toggle2();
inline bool in_region(int x, int z, int y,   int x1, int z1, int y1,  int x2, int z2, int y2) {
    return x1 <= x && x < x2 && z1 <= z && z < z2 && y1 <= y && y < y2;
}

MCRegion::MCRegion(int r_x,int r_z, int x0, int z0, int y0,
                   int xl, int zl, int yl)
{
    A  	    =   (BlockInfo***)      calloc(xl ,	        sizeof(BlockInfo**));
    A[0]    =   (BlockInfo**)	    calloc(xl*zl,	    sizeof(BlockInfo*));
    for(int i=0; i<xl; i++)
        A[i] = (*A+zl*i);

    A[0][0] =   (BlockInfo*)        calloc(xl*zl*yl,	sizeof(BlockInfo));
    for(int i=0; i<xl; i++)
        for(int j=0; j<zl; j++) {
            A[i][j] = (*A[0]+zl*i*yl+yl*j);
            memset(A[i][j], 0, yl * sizeof(BlockInfo));
        }

    B  	    =   (BlockEntity****)   calloc(xl ,	        sizeof(BlockEntity***));
    B[0]    =   (BlockEntity***)	calloc(xl*zl,	    sizeof(BlockEntity**));
    for(int i=0; i<xl; i++)
        B[i] = (*B+zl*i);

    B[0][0] =   (BlockEntity**)     calloc(xl*zl*yl,	sizeof(BlockEntity*));
    memset(B[0][0], 0, xl*yl*zl*sizeof(BlockEntity*));
    for(int i=0; i<xl; i++) {
        for(int j=0; j<zl; j++) {
            B[i][j] = (*B[0]+zl*i*yl+yl*j);
            memset(B[i][j], 0, yl * sizeof(BlockEntity*));
        }
    }

    x_len = xl, z_len = zl, y_len = yl;
    x_ori = x0, z_ori = z0, y_ori = y0;
    region_x=r_x;
    region_z=r_z;
}

MCRegion::~MCRegion()
{
    free(A[0][0]);
    free(A[0]);
    free(A);
    for (int i = 0; i < x_len; i++)
        for (int j = 0; j < z_len; j++)
            for (int k = 0; k < y_len; k++)
                if (B[i][j][k]) delBlockEntity(B[i][j][k]);
    free(B[0][0]);
    free(B[0]);
    free(B);
}

void MCRegion::delBlockEntity(BlockEntity* entity)
{
    if (!entity) return;

    string id = entity->entity_id;
    if (id == "minecraft:noteblock") {
        delete ((BlockEntityNote*)entity);
    } else if (id == "minecraft:teglowstone") {
        delete ((BlockEntityGlowColor*)entity);
    } else {
        delete entity;
    }
    entity=NULL;
}

void MCEditor::setRegion(const MCRegion &R)
{
    mca_coder.region_xxx=R.region_x;
    mca_coder.region_zzz=R.region_z;
    mca_coder.chunk_offsetx=R.region_x*32;
    mca_coder.chunk_offsetz=R.region_z*32;

    x_len = R.x_len, z_len = R.z_len, y_len = R.y_len;
    x_ori = R.x_ori, z_ori = R.z_ori, y_ori = R.y_ori;
    block_entities = R.B;

    initArrays(x_len , z_len , y_len);

    printf(" initBlocks\b\b\b\b\b\b\b\b\b\b\b");
    initBlocks(R);

    printf(" computeBlockLight\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    computeBlockLight(R);

    printf(" computeSkyLight   \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    computeSkyLight(R);

    printf(" updateMCA\b\b\b\b\b\b\b\b\b\b");

    mca_coder.modification_saved = false;

    updateMCA_FAST(R);

    clearArrays(x_len , z_len , y_len);
}

void MCEditor::initArrays(int l1, int l2, int l3)
{
    blocks = new3DUIArray(l1, l2, l3);
    blockdata = new3DUIArray(l1, l2, l3);
    blocklight = new3DUIArray(l1, l2, l3);
    skylight = new3DUIArray(l1, l2, l3);
}

void MCEditor::clearArrays(int l1, int l2, int l3)
{
    del3DUIArray(blocks, l1, l2, l3);
    del3DUIArray(blockdata, l1, l2, l3);
    del3DUIArray(blocklight, l1, l2, l3);
    del3DUIArray(skylight, l1, l2, l3);
}


void MCEditor::initBlocks(const MCRegion &R)
{
    BlockInfo*** AX=R.A;

    printf("Computing: ");
//    for (int i = 0; i < 512; i++) {
    for (int i = 0; i < R.x_len; i++) {
        BlockInfo** AZ=AX[i];
        ui** AZ_blockdata=blockdata[i];
        ui** AZ_blocks=blocks[i];
        ui** AZ_blocklight=blocklight[i];
//        for (int j = 0; j < 512; j++) {
        for (int j = 0; j < R.z_len; j++) {
            toggle2();
            BlockInfo* AY=AZ[j];
            ui* AY_blockdata=AZ_blockdata[j];
            ui* AY_blocks=AZ_blocks[j];
            ui* AY_blocklight=AZ_blocklight[j];
//            for (int k = 0; k < 256; k++) {
            for (int k = 0; k < R.y_len; k++) {
                BlockInfo bi = AY[k];
                ui id = bi.id | (bi.add << 8);
                AY_blocks[k] = id;
                AY_blockdata[k] = bi.data;
//noumoe
//                AY_blocklight[k] = bi.block_light;
                AY_blocklight[k] = 0;
            }
        }
    }
//    int x0 = x_ori , x1 = x_ori + x_len , z0 = z_ori , z1 = z_ori + z_len ,  y0 = 0, y1 = 256;
    int x0 = x_ori , x1 = x_ori + x_len , z0 = z_ori , z1 = z_ori + z_len ,  y0 = y_ori, y1 = y_ori+y_len;
}

void MCEditor::computeBlockLight(const MCRegion &R)
{
//    for (int x = 0; x < 512;  x++) {
    for (int x = 0; x < R.x_len;  x++) {
        ui** AZ_blocklight=blocklight[x];
        ui** AZ_blocks=blocks[x];
        toggle2();
//        for (int z = 0; z < 512; z++) {
        for (int z = 0; z < R.z_len; z++) {
            ui* AY_blocklight=AZ_blocklight[z];
            ui* AY_blocks=AZ_blocks[z];
//            for (int y = 0; y < 256; y++) {
            for (int y = 0; y < R.y_len; y++) {
                    ui bl = get_block_light(AY_blocks[y]);
                    if (bl > AY_blocklight[y]) AY_blocklight[y]=bl;
            }
        }
    }
    lightPropagate(blocklight);
}

void MCEditor::computeSkyLight(const MCRegion &R) {
//    for (int x = 0; x < 512; x++) {
    for (int x = 0; x < R.x_len; x++) {
        ui** AZ_skylight=skylight[x];
        toggle2();
//        for (int z = 0; z < 512; z++) {
        for (int z = 0; z < R.z_len; z++) {
            ui* AY_skylight=AZ_skylight[z];
//            memset(AZ_skylight[z], 0, 256 * sizeof(ui));
            memset(AZ_skylight[z], 0, R.y_len * sizeof(ui));
        }
    }

//    for (int x = 0; x < 512; x++) {
    for (int x = 0; x < R.x_len; x++) {
        ui** AZ_skylight=skylight[x];
        ui** AZ_blocks=blocks[x];
        toggle2();
//        for (int z = 0; z < 512; z++) {
        for (int z = 0; z < R.z_len; z++) {
            ui* AY_skylight=AZ_skylight[z];
            ui* AY_blocks=AZ_blocks[z];
//            for (int y = 255; y >= 0; y--) {
            for (int y = y_len-1; y >= 0; y--) {
                if (get_opacity(AY_blocks[y]) <= 1) AY_skylight[y] = 15;
                else break;
            }
        }
    }

    lightPropagate(skylight);
}

void MCEditor::updateMCA_FAST(const MCRegion &R)
{
    printf("- Packing: ");

    int x0 = x_ori , z0 = z_ori ;

    BlockInfo*** AX=R.A;

//    for (int x = 0; x < 512 ; x+=16) {
    for (int x = 0; x < R.x_len ; x+=16) {
//        for (int z = 0; z < 512 ; z+=16) {
        for (int z = 0; z < R.z_len ; z+=16) {
            toggle2();
//            for (int y = 0; y < 256; y+=16) {
            for (int y = 0; y < R.y_len; y+=16) {
                for (int x_inner = 0; x_inner < 16 ; x_inner++) {
                    BlockInfo** AZ=AX[x+x_inner];

                    ui** AZ_skylight=skylight[x+x_inner];
                    ui** AZ_blocks=blocks[x+x_inner];
                    ui** AZ_blocklight=blocklight[x+x_inner];
                    ui** AZ_blockdata=blockdata[x+x_inner];

                    for (int z_inner = 0; z_inner < 16 ; z_inner++) {
                        BlockInfo* AY=AZ[z+z_inner];

                        ui* AY_skylight=AZ_skylight[z+z_inner];
                        ui* AY_blocks=AZ_blocks[z+z_inner];
                        ui* AY_blocklight=AZ_blocklight[z+z_inner];
                        ui* AY_blockdata=AZ_blockdata[z+z_inner];

                        for (int y_inner = 0; y_inner < 16 ; y_inner++) {
                            int y_tot=y+y_inner;

                            ui id = AY_blocks[y_tot] & (ui)0xFF;
                            ui add = (AY_blocks[y_tot] >> 8) & 0xF;
                            ui data = AY_blockdata[y_tot];
                            AY[y_tot] = BlockInfo(id, add, data, AY_blocklight[y_tot], AY_skylight[y_tot]);
                        }
                    }
                }
            }
        }
    }

    printf("1");

    mca_coder.setBlock_FAST(R);

    printf("2");

    for (int x = 00; x < x_len + 00; x++) {
        ui** AZ_skylight=skylight[x];
        for (int z = 00; z < z_len + 00; z++) {
            ui* AY_skylight=AZ_skylight[z];
            toggle2();
//            for (int y = 0; y < 256; y++) {
            for (int y = 0; y < y_len; y++) {
                if (AY_skylight[y] == 15) {
                    mca_coder.setHeightMap(x + x_ori, z + z_ori, y);  break;
                }
            }
        }
    }

    printf("3");

    printf(" Save modification: ");
    mca_coder.saveModification();
    printf(" Saved.");
}


void MCEditor::updateMCA()
{
    printf("- Packing: ");
    vector<Pos> VP;
    for (int x = 0; x < x_len; x++) {
        toggle2();
        for (int z = 0; z < z_len; z++) {
            for (int y = 0; y < y_len; y++) {
                VP.push_back(Pos(x + x_ori, z + z_ori, y + y_ori));
            }
        }
    }
    printf("-");
    if (mca_coder.remove_block_entities)
        for (auto position : VP) {  toggle3();   mca_coder.removeBlockEntity(position);  }
    printf("-");

    vector<Block> VB;

    int x0 = x_ori , z0 = z_ori ;

//    for (int x = 0; x < 512 ; x+=16) {
    for (int x = 0; x < x_len ; x+=16) {
//        for (int z = 0; z < 512 ; z+=16) {
        for (int z = 0; z < z_len ; z+=16) {
            toggle2();
//            for (int y = 0; y < 256; y+=16) {
            for (int y = 0; y < y_len; y+=16) {
                for (int x_inner = 0; x_inner < 16 ; x_inner++) {
                    ui** AZ_skylight=skylight[x+x_inner];
                    ui** AZ_blocks=blocks[x+x_inner];
                    ui** AZ_blocklight=blocklight[x+x_inner];
                    ui** AZ_blockdata=blockdata[x+x_inner];

                    for (int z_inner = 0; z_inner < 16 ; z_inner++) {
                        ui* AY_skylight=AZ_skylight[z+z_inner];
                        ui* AY_blocks=AZ_blocks[z+z_inner];
                        ui* AY_blocklight=AZ_blocklight[z+z_inner];
                        ui* AY_blockdata=AZ_blockdata[z+z_inner];

                        for (int y_inner = 0; y_inner < 16 ; y_inner++) {
                            int y_tot=y+y_inner;
                            Pos position = Pos(x + x_inner, z + z_inner, y_tot);

                            ui id = AY_blocks[y_tot] & (ui)0xFF;
                            ui add = (AY_blocks[y_tot] >> 8) & 0xF;
                            ui data = AY_blockdata[y_tot];
                            BlockInfo info = BlockInfo(id, add, data, AY_blocklight[y_tot], AY_skylight[y_tot]);
                            VB.push_back(Block(position, info));
                        }
                    }
                }
            }
        }
    }
    printf("-");

    mca_coder.old_idx=0;
    mca_coder.old_sec_no=0;
    mca_coder.old_T=0;
    mca_coder.old_sec_root=0;

    for (Block u : VB) {  mca_coder.setBlock(u.position, u.info);/*  toggle3();*/  }
    printf("-");

    mca_coder.old_idx=0;
    mca_coder.old_sec_no=0;
    mca_coder.old_T=0;
    mca_coder.old_sec_root=0;
    for (int x = 00; x < x_len + 00; x++) {
        ui** AZ_skylight=skylight[x];
        for (int z = 00; z < z_len + 00; z++) {
            ui* AY_skylight=AZ_skylight[z];
            toggle2();
//            for (int y = 0; y < 256; y++) { if (AY_skylight[y] == 15) { mca_coder.setHeightMap(x + x_ori, z + z_ori, y);  break; } }
            for (int y = 0; y < y_len; y++) { if (AY_skylight[y] == 15) { mca_coder.setHeightMap(x + x_ori, z + z_ori, y);  break; } }
        }
    }
    printf("-");
    vector<pair<Pos, BlockEntity*> > VE;
    for (int x = 0; x < x_len; x++) {
        BlockEntity*** AZ_block_entities=block_entities[x];
        for (int z = 0; z < z_len; z++) {
            BlockEntity** AY_block_entities=AZ_block_entities[z];
            toggle2();
            for (int y = 0; y < y_len; y++) { VE.push_back(make_pair(Pos(x + x_ori, z + z_ori, y + y_ori), AY_block_entities[y])); }
        }
    }
    printf("-");

    for (auto u : VE) { mca_coder.insertBlockEntity(u.first, u.second);  toggle3(); }

    printf("Save modification: ");
    mca_coder.saveModification();
    printf(" Saved.");
}

void MCEditor::lightPropagate(ui*** light)
{
    queue<Pos> Q;

    for (int x = 0; x < x_len; x++) {
        ui** AZ_light=light[x];
        for (int z = 0; z < z_len; z++) {
            ui* AY_light=AZ_light[z];
            toggle2();
            for (int y = 255; y >= 0; y--) {
                if (AY_light[y]) {
                    Q.push(Pos(x, z, y));
                    while (!Q.empty()) {
                        Pos u = Q.front();
                        Q.pop();
                        for (int d = 0; d < 6; d++) {
                            int vx = u.x + DX[d],   vz = u.z + DZ[d],     vy = u.y + DY[d];
                            if (vx<0 || vx>=x_len || vz<0 || vz>=z_len || vy<0 || vy>=y_len) continue;
//                            if (vx<0 || vx>=512 || vz<0 || vz>=512 || vy<0 || vy>=256) continue;

                            int dec = get_opacity(blocks[vx][vz][vy]);
                            int vlight = (int)light[u.x][u.z][u.y] - dec;
                            if (vlight <= 0) continue;
                            ui* L=&light[vx][vz][vy];

                            if (*L < vlight) {
                                *L = vlight;
                                Q.push(Pos(vx, vz, vy));
                            }
                        }
                    }
                }
            }
        }
    }
}


void MCACoder::getBlock_FAST(const MCRegion &region) {

    int n=0;
    BlockInfo*** AX=region.A;
    int num_blocks=0;
    for (int x_outer = 0; x_outer < 512 ; x_outer+=16) {
        int chunk_x = x_outer >> 4;
        int region_x = chunk_x >> 5;
        for (int z_outer = 0; z_outer < 512 ; z_outer+=16) {
            int chunk_z = z_outer >> 4;
            int region_z = chunk_z >> 5;
            int idx = (chunk_x & 31) + 32 * (chunk_z & 31);
            node *chunk_root = Chunk[idx];
            if (!chunk_root) {
//                for (int y_outer = 0; y_outer < 256; y_outer+=16) {
                for (int y_outer = 0; y_outer < region.y_len; y_outer+=16) {
                    for (int x_inner = 0; x_inner < 16 ; x_inner++) {
                        int x=x_outer + x_inner;
                        BlockInfo** AZ=AX[x];
                        for (int z_inner = 0; z_inner < 16 ; z_inner++) {
                            int z=z_outer + z_inner;
                            BlockInfo* AY=AZ[z];
                            if (!(n++&31)) toggle2();
                            for (int y_inner = 0; y_inner < 16 ; y_inner++) {
                                int y=y_outer + y_inner;
                                AY[y]=BlockInfo();
                            }
                        }
                    }
                }
                continue;
            }
            node *level_root = chunk_root->childWithName("Level");
            node *sec_root = level_root->childWithName("Sections");
            for (int y_outer = 0; y_outer < region.y_len; y_outer+=16) {
//            for (int y_outer = 0; y_outer < y_256; y_outer+=16) {
                int sec_no = y_outer >> 4;
                node *T = sectionNodeWithY(sec_root, sec_no);

                if (!T) {
                    for (int x_inner = 0; x_inner < 16 ; x_inner++) {
                        int x=x_outer + x_inner;
                        BlockInfo** AZ=AX[x];
                        for (int z_inner = 0; z_inner < 16 ; z_inner++) {
                            int z=z_outer + z_inner;
                            BlockInfo* AY=AZ[z];
                            if (!(n++&31)) toggle2();
                            for (int y_inner = 0; y_inner < 16 ; y_inner++) {
                                int y=y_outer + y_inner;
                                AY[y]=BlockInfo();
                            }
                        }
                    }
                    continue;
                }
//                node *u;

                node *old_u_blocks = T->childWithName("Blocks");
                node *old_u_add = T->childWithName("Add");
                node *old_u_data = T->childWithName("Data");
                node *old_u_blocklight=T->childWithName("BlockLight");
                node *old_u_skylight = T->childWithName("SkyLight");

                for (int x_inner = 0; x_inner < 16 ; x_inner++) {
                    int x=x_outer + x_inner;
                    BlockInfo** AZ=AX[x];
                    for (int z_inner = 0; z_inner < 16 ; z_inner++) {
                        int z=z_outer + z_inner;
                        BlockInfo* AY=AZ[z];
                        if (!(n++&31)) toggle2();

                        for (int y_inner = 0; y_inner < 16 ; y_inner++) {
                            int y=y_outer + y_inner;
//                            int block_pos = y_inner * 256 + z_inner * 16 + x_inner;
                            int block_pos = y_inner * region.y_len + z_inner * 16 + x_inner;

                            uc id;
                            if (old_u_blocks) {
                                id = (int)old_u_blocks->tag.va[block_pos];
                            } else id=0;

                            uc res;
                            int add;
                            if (old_u_add) {
                                res = old_u_add->tag.va[block_pos >> 1];
                                add = (block_pos & 1) ? ((res >> 4) & 0xF): (res & 0xF);
                            } else add=0;

                            int data;
                            if (old_u_data) {
                                res = old_u_data->tag.va[block_pos >> 1];
                                data = (block_pos & 1) ? ((res >> 4) & 0xF): (res & 0xF);
                            } else data=0;

                            res = old_u_blocklight->tag.va[block_pos >> 1];
                            int block_light = (block_pos & 1) ? ((res >> 4) & 0xF): (res & 0xF);

                            res = old_u_skylight->tag.va[block_pos >> 1];
                            int sky_light = (block_pos & 1) ? ((res >> 4) & 0xF): (res & 0xF);

                            if (id!=0) {
                                num_blocks++;
                                AY[y]=BlockInfo(id,add,data,block_light,sky_light);
                            } else {
                                AY[y]=BlockInfo(id,add,data,block_light,sky_light);
//                                AY[y]=BlockInfo();
                            }
                        }
                    }
                }
            }
        }
    }
}

extern int region_xxx,region_zzz;

void MCACoder::setBlock_FAST(const MCRegion &region) {

    int totx=region_xxx*512;
    int totz=region_zzz*512;

    int n=0;
    BlockEntity**** BX=region.B;
    BlockInfo*** AX=region.A;
    int num_blocks=0;
    for (int x_outer = 0; x_outer < 512 ; x_outer+=16) {
        int chunk_x = x_outer >> 4;
        int region_x = chunk_x >> 5;
        for (int z_outer = 0; z_outer < 512 ; z_outer+=16) {
            int chunk_z = z_outer >> 4;
            int region_z = chunk_z >> 5;
            int idx = (chunk_x & 31) + 32 * (chunk_z & 31);
            node *chunk_root = Chunk[idx];

            if (!chunk_root) {
                continue;
            }

            node *level_root = chunk_root->childWithName("Level");
            node *sec_root = level_root->childWithName("Sections");

            node *tile_root  = level_root->childWithName("TileEntities");
            if (!tile_root) {  fprintf(stderr,"TileEntities does not exits chunk (%d, %d)\n", chunk_x, chunk_z); }
            else {
                if (remove_block_entities) {
                    for (auto it = tile_root->ch.begin(); it != tile_root->ch.end(); it++)
                    {
                        node *u = *it;
                        nbt_coder.Clear(u);
                    }
                    tile_root->ch.clear();
                }
            }

            bool content_chunk=false;
//            for (int y_outer = 0; y_outer < 256; y_outer+=16) {
            for (int y_outer = 0; y_outer < region.y_len; y_outer+=16) {
                int sec_no = y_outer >> 4;

                node *T = sectionNodeWithY(sec_root, sec_no);

                if (!T) {
                    bool content=false;
                    for (int x_inner = 0; x_inner < 16 ; x_inner++) {
                        int x=x_outer + x_inner;
                        BlockInfo** AZ=AX[x];
                        for (int z_inner = 0; z_inner < 16 ; z_inner++) {
                            int z=z_outer + z_inner;
                            BlockInfo* AY=AZ[z];
                            if (!(n++&31)) toggle2();
                            for (int y_inner = 0; y_inner < 16 ; y_inner++) {
                                int y=y_outer + y_inner;
                                if (AY[y].id!=0) {
                                    content=true;
                                    break;
                                }
                            }
                            if (content) break;
                        }
                        if (content) break;
                    }
                    if (!content) continue;

                    T = newSectionNodeWithY(sec_no);
                    sec_root->addChild(T);
                }

                node *old_u_blocks = T->childWithName("Blocks");
                node *old_u_add = T->childWithName("Add");
                node *old_u_data = T->childWithName("Data");
                node *old_u_blocklight=T->childWithName("BlockLight");
                node *old_u_skylight = T->childWithName("SkyLight");

                bool content_section=false;
                for (int x_inner = 0; x_inner < 16 ; x_inner++) {
                    int x=x_outer + x_inner;
                    BlockInfo** AZ=AX[x];
                    BlockEntity*** BZ=BX[x];

                    for (int z_inner = 0; z_inner < 16 ; z_inner++) {
                        int z=z_outer + z_inner;
                        BlockInfo* AY=AZ[z];
                        BlockEntity** BY=BZ[z];
                        if (!(n++&31)) toggle2();

                        BlockInfo* info;
                        BlockEntity* entity;

                        for (int y_inner = 0; y_inner < 16 ; y_inner++) {
                            int y=y_outer + y_inner;
//                            int block_pos = y_inner * 256 + z_inner * 16 + x_inner;
                            int block_pos = y_inner * region.y_len + z_inner * 16 + x_inner;

                            info=&AY[y];
                            entity=BY[y];

                            if (entity) {
                                tile_root->tag.ch_type = TAG_COMPOUND;
                                tile_root->addChild(newBlockEntityNode(entity));
                            }

                            if (info->id!=0) content_section=true;

                            if (old_u_blocks) {
                                nbt_coder.setByteInArrayContent(old_u_blocks, block_pos, (uc)info->id);
                            }

                            if (old_u_add || info->add)
                            {
                                if (!old_u_add)
                                {
                                    old_u_add = new node(TAG_BYTE_ARRAY, "Add");
                                    old_u_add->tag.va.resize(K2);
                                    T->addChild(old_u_add);
                                }
                                nbt_coder.setHalfByteInArrayContent(old_u_add, block_pos, info->add);
                            }

                            if (old_u_data) {
                                nbt_coder.setHalfByteInArrayContent(old_u_data, block_pos, info->data);
                            };

                            nbt_coder.setHalfByteInArrayContent(old_u_blocklight, block_pos, info->block_light);
                            nbt_coder.setHalfByteInArrayContent(old_u_skylight, block_pos, info->sky_light);
                        }
                    }
                }
            }
        }
    }
}



