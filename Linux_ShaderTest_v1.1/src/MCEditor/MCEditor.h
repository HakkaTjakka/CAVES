#ifndef MCAEditor_h
#define MCAEditor_h

#include "globals.h"
#include "MCACoder.h"
#include "BlockEntity.h"


class MCEditor
{
public:
    void setRegion(const MCRegion &R);

//    MCEditor(int region_x, int region_z);


    MCEditor() {};


    MCEditor(int r_x, int r_z) {};

    int region_x, region_z;

    MCACoder mca_coder;

    BlockEntity**** block_entities;

    void computeSkyLight(const MCRegion &R);

    const int DX[6] = {0, 0, -1, 1, 0, 0},
              DZ[6] = {0, 0, 0, 0, -1, 1},
              DY[6] = {1, -1, 0, 0, 0, 0};

    int x_len, z_len, y_len,
        x_ori, z_ori, y_ori;


    ui ***blocks, ***blockdata,
          ***blocklight, ***skylight;

    void initArrays(int l1, int l2, int l3);

    void clearArrays(int l1, int l2, int l3);

    void initBlocks(const MCRegion &R);

    void computeBlockLight(const MCRegion &R);

    void lightPropagate(ui*** light);

    void updateMCA();
    void updateMCA_FAST(const MCRegion &R);

    private:
};

#endif
