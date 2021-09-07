#ifndef __FFSUPPORT_H
#define __FFSUPPORT_H

#include <Arduino.h>
#include <lvgl.h>

#define FT_FILE     lv_fs_file_t
#define ft_fclose   ffsupport_fclose
#define ft_fopen    ffsupport_fopen
#define ft_fread    ffsupport_fread
#define ft_fseek    ffsupport_fseek
#define ft_ftell    ffsupport_ftell
#define ft_sprintf  sprintf

lv_fs_file_t* ffsupport_fopen(const char* src, const char* mode);
void ffsupport_fclose(lv_fs_file_t* lv_file);
size_t ffsupport_fread(void* ptr, size_t size, size_t nmemb, lv_fs_file_t* lv_file);
int ffsupport_fseek(lv_fs_file_t* lv_file, long int offset, int whence);
long int ffsupport_ftell(lv_fs_file_t* lv_file);

#endif