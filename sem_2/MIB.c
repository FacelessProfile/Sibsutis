#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_NOF_MIB 64

typedef enum {
    scs15or60 = 0,
    scs30or120
} scs_e;

typedef struct {
    uint8_t systemFrameNumber : 6;
    uint8_t subCarrierSpacingCommon : 1;
    uint8_t ssb_SubcarrierOffset : 4;
    uint8_t dmrs_TypeA_Position : 1;
    uint8_t pdcch_ConfigSIB1 : 8;
    uint8_t cellBarred : 1;
    uint8_t intraFreqReselection : 1;
    uint8_t spare : 1;
} MIB_t;

typedef struct {
    int nof_mibs;
    MIB_t mib[MAX_NOF_MIB];
} MIB_LIST_t;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s bin_file\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        printf("Error reading file: %s\n", argv[1]);
        return 1;
    }

    MIB_LIST_t *mib_list = malloc(sizeof(MIB_LIST_t));
    if (!mib_list) {
        printf("Memory allocation failed\n");
        fclose(file);
        return 1;
    }

    // Читаем количество MIB
    if (fread(&mib_list->nof_mibs, sizeof(int), 1, file) != 1) {
        printf("Error reading nof_mibs\n");
        free(mib_list);
        fclose(file);
        return 1;
    }

    if (fread(mib_list->mib, sizeof(MIB_t), mib_list->nof_mibs, file) != mib_list->nof_mibs) {
        printf("Error reading MIB data\n");
        free(mib_list);
        fclose(file);
        return 1;
    }

    fclose(file);

    printf("nof_mibs is %d\n", mib_list->nof_mibs);
    for (int i = 0; i < mib_list->nof_mibs && i < 3; i++) {
        printf("MIB[%d]: SFN=%d, SCSC=%d, SOff=%d\n",
               i,
               mib_list->mib[i].systemFrameNumber,
               mib_list->mib[i].subCarrierSpacingCommon,
               mib_list->mib[i].ssb_SubcarrierOffset);
    }

    free(mib_list);
    return 0;
}
