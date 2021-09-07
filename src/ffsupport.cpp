#include "ffsupport.h"

lv_fs_file_t* ffsupport_fopen(const char* src, const char* mode) {
    lv_fs_file_t* f = (lv_fs_file_t*) lv_mem_alloc(sizeof(lv_fs_file_t));
    if (strcmp(mode, "w") == 0) {
        lv_fs_open(f, src, LV_FS_MODE_WR);
    } else if (strcmp(mode, "r+") == 0) {
        lv_fs_open(f, src, (LV_FS_MODE_WR | LV_FS_MODE_RD));
    } else {
        lv_fs_open(f, src, LV_FS_MODE_RD);
    }
    return f;
}
void ffsupport_fclose(lv_fs_file_t* lv_file) {
    lv_fs_close(lv_file);
    lv_mem_free(lv_file);
}
size_t ffsupport_fread(void* ptr, size_t size, size_t nmemb, lv_fs_file_t* lv_file) {
    size_t br;
    lv_fs_read(lv_file, (uint8_t*)ptr, size * nmemb, &br);
    return br;
}
int ffsupport_fseek(lv_fs_file_t* lv_file, long int offset, int whence) {
    if (whence == 0) {
        lv_fs_seek(lv_file, offset, LV_FS_SEEK_SET);
    } else if (whence == 1) {
        lv_fs_seek(lv_file, offset, LV_FS_SEEK_CUR);
    } else if (whence == 2) {
        lv_fs_seek(lv_file, offset, LV_FS_SEEK_END);
    }
    return true;
}
long int ffsupport_ftell(lv_fs_file_t* lv_file) {
    uint32_t pos_p;
    lv_fs_tell(lv_file, &pos_p);
    return (long int) pos_p;
}