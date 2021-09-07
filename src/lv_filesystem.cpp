/**
 * @file lv_filesystem.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#if LV_LVGL_H_INCLUDE_SIMPLE
#include <lvgl.h>
#else
#include "../../lvgl/lvgl.h"
#endif

#include <Arduino.h>
#include <SPIFFS.h>
#include <FFat.h>
#include <SD.h>

#include "lv_filesystem.h"

/*********************
 *      DEFINES
 *********************/

 /**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void* spiffs_open(lv_fs_drv_t* drv, const char* path, lv_fs_mode_t mode);
static void* ffat_open(lv_fs_drv_t* drv, const char* path, lv_fs_mode_t mode);
static void* sd_open(lv_fs_drv_t* drv, const char* path, lv_fs_mode_t mode);
static lv_fs_res_t fs_close(lv_fs_drv_t* drv, void* file_p);
static lv_fs_res_t fs_read(lv_fs_drv_t* drv, void* file_p, void* buf, uint32_t btr, uint32_t* br);
static lv_fs_res_t fs_write(lv_fs_drv_t* drv, void* file_p, const void* buf, uint32_t btw, uint32_t* bw);
static lv_fs_res_t fs_seek(lv_fs_drv_t* drv, void* file_p, uint32_t pos, lv_fs_whence_t whence);
static lv_fs_res_t fs_tell(lv_fs_drv_t* drv, void* file_p, uint32_t* pos_p);
static void* fs_dir_open(lv_fs_drv_t* drv, const char* path);
static lv_fs_res_t fs_dir_read(lv_fs_drv_t* drv, void* dir_p, char* fn);
static lv_fs_res_t fs_dir_close(lv_fs_drv_t* drv, void* dir_p);

 /**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_fs_spiffs_init(char letter) {
  static lv_fs_drv_t fs_drv;
  lv_fs_drv_init(&fs_drv);
  fs_drv.letter = letter;
  fs_drv.open_cb = spiffs_open;
  fs_drv.close_cb = fs_close;
  fs_drv.read_cb = fs_read;
  fs_drv.write_cb = fs_write;
  fs_drv.seek_cb = fs_seek;
  fs_drv.tell_cb = fs_tell;
  lv_fs_drv_register(&fs_drv);
}

void lv_fs_ffat_init(char letter) {
  static lv_fs_drv_t fs_drv;
  lv_fs_drv_init(&fs_drv);
  fs_drv.letter = letter;
  fs_drv.open_cb = ffat_open;
  fs_drv.close_cb = fs_close;
  fs_drv.read_cb = fs_read;
  fs_drv.write_cb = fs_write;
  fs_drv.seek_cb = fs_seek;
  fs_drv.tell_cb = fs_tell;
  fs_drv.dir_open_cb = fs_dir_open;
  fs_drv.dir_read_cb = fs_dir_read;
  fs_drv.dir_close_cb = fs_dir_close;
  lv_fs_drv_register(&fs_drv);
}

void lv_fs_sd_init(char letter) {
  static lv_fs_drv_t fs_drv;
  lv_fs_drv_init(&fs_drv);
  fs_drv.letter = letter;
  fs_drv.open_cb = sd_open;
  fs_drv.close_cb = fs_close;
  fs_drv.read_cb = fs_read;
  fs_drv.write_cb = fs_write;
  fs_drv.seek_cb = fs_seek;
  fs_drv.tell_cb = fs_tell;
  fs_drv.dir_open_cb = fs_dir_open;
  fs_drv.dir_read_cb = fs_dir_read;
  fs_drv.dir_close_cb = fs_dir_close;
  lv_fs_drv_register(&fs_drv);
}

void lv_fs_init() {
  lv_fs_spiffs_init();
  lv_fs_ffat_init();
  lv_fs_sd_init();
}

 /**********************
 *   STATIC FUNCTIONS
 **********************/

static void* spiffs_open(lv_fs_drv_t* drv, const char* path, lv_fs_mode_t mode) {
  char* flag = "r";
  if (mode == LV_FS_MODE_WR) {
    flag = "w";
  } else if (mode == LV_FS_MODE_RD) {
    flag = "r";
  } else if (mode == (LV_FS_MODE_WR | LV_FS_MODE_RD)) {
    flag = "r+";
  }
  File file = SPIFFS.open(path, flag);
//  Serial.printf("lvfs spiffs_open: %s (%s) \n", path, flag);
  if (file) {
//    Serial.printf("lvfs spiffs_open_hit: %s (%s), size: %d \n", path, flag, file.size());
    File* fp  = new File(file);
    return fp;
  }
  return NULL;
}

static void* ffat_open(lv_fs_drv_t* drv, const char* path, lv_fs_mode_t mode) {
  char* flag = "r";
  if (mode == LV_FS_MODE_WR) {
    flag = "w";
  } else if (mode == LV_FS_MODE_RD) {
    flag = "r";
  } else if (mode == (LV_FS_MODE_WR | LV_FS_MODE_RD)) {
    flag = "r+";
  }
  File file = FFat.open(path, flag);
//  Serial.printf("lvfs ffat_open: %s (%s) \n", path, flag);
  if (file) {
//    Serial.printf("lvfs ffat_open_hit: %s (%s), size: %d \n", path, flag, file.size());
    File* fp  = new File(file);
    return fp;
  }
  return NULL;
}

static void* sd_open(lv_fs_drv_t* drv, const char* path, lv_fs_mode_t mode) {
  char* flag = "r";
  if (mode == LV_FS_MODE_WR) {
    flag = "w";
  } else if (mode == LV_FS_MODE_RD) {
    flag = "r";
  } else if (mode == (LV_FS_MODE_WR | LV_FS_MODE_RD)) {
    flag = "r+";
  }
  File file = SD.open(path, flag);
//  Serial.printf("lvfs sd_open: %s (%s) \n", path, flag);
  if (file) {
//    Serial.printf("lvfs sd_open_hit: %s (%s), size: %d \n", path, flag, file.size());
    File* fp  = new File(file);
    return fp;
  }
  return NULL;
}

static lv_fs_res_t fs_close(lv_fs_drv_t* drv, void* file_p) {
//  Serial.printf("lvfs fs_close file: %s \n", ((File*) file_p) -> name());
  ((File*) file_p) -> close();
  delete(file_p);
  return LV_FS_RES_OK;
}

static lv_fs_res_t fs_read(lv_fs_drv_t* drv, void* file_p, void* buf, uint32_t btr, uint32_t* br) {
  uint32_t remain = ((File*) file_p) -> size() - ((File*) file_p) -> position();
  ((File*) file_p) -> read((uint8_t*) buf, btr);
  *br = remain >= btr ? btr : remain;
//  Serial.printf("lvfs fs_read file: %s, size: %d, remain: %d \n", ((File*) file_p) -> name(), *br, ((File*) file_p) -> size() - ((File*) file_p) -> position());
//  for (int i = 0 ; i < *br ; i ++) {
//    Serial.printf("%02x ", ((uint8_t*)buf)[i]);
//  }
//  Serial.printf("\n");
  return LV_FS_RES_OK;
}

static lv_fs_res_t fs_write(lv_fs_drv_t* drv, void* file_p, const void* buf, uint32_t btw, uint32_t* bw) {
//  Serial.printf("lvfs fs_write file: %s, size: %d, writed: %d \n", ((File*) file_p) -> name(), btw, *bw);
  *bw = ((File*) file_p) -> write((uint8_t*) buf, btw);
  ((File*) file_p) -> flush();
  return LV_FS_RES_OK;
}

static lv_fs_res_t fs_seek(lv_fs_drv_t* drv, void* file_p, uint32_t pos, lv_fs_whence_t whence) {
//  Serial.printf("lvfs fs_seek file: %s, pos: %d, whence: %d \n", ((File*) file_p) -> name(), pos, whence);
  switch (whence) {
    case LV_FS_SEEK_SET:
      ((File*) file_p) -> seek(pos, SeekSet);
      break;
    case LV_FS_SEEK_CUR:
      ((File*) file_p) -> seek(pos, SeekCur);
      break;
    case LV_FS_SEEK_END:
      ((File*) file_p) -> seek(pos, SeekEnd);
      break;
    default:
      ((File*) file_p) -> seek(pos, SeekSet);
      break;
  }
  return LV_FS_RES_OK;
}

static lv_fs_res_t fs_tell(lv_fs_drv_t* drv, void* file_p, uint32_t* pos_p) {
//  Serial.printf("lvfs fs_tell file: %s \n", ((File*) file_p) -> name());
  *pos_p = ((File*) file_p) -> position();
  return LV_FS_RES_OK;
}

static void* fs_dir_open(lv_fs_drv_t* drv, const char* path) {
  char* flag = "r";
  File file = SPIFFS.open(path, flag);
  if (file) {
    if (file.isDirectory()) {
      File* fp = (File*) lv_mem_alloc(sizeof(File));
      if (fp != NULL) {
        *fp = file;
        return fp;
      }
    }
  }
  return NULL;
}

static lv_fs_res_t fs_dir_read(lv_fs_drv_t* drv, void* dir_p, char* fn) {
  File file = ((File*) dir_p) -> openNextFile();
  if (file) {
    if (file.isDirectory()) {
      sprintf(fn, "/%s", file.name());
    } else {
      strcpy(fn, file.name());
    }
    return LV_FS_RES_OK;
  }
  return LV_FS_RES_UNKNOWN;
}

static lv_fs_res_t fs_dir_close(lv_fs_drv_t* drv, void* dir_p) {
  ((File*) dir_p) -> close();
  delete(dir_p);
  return LV_FS_RES_OK;
}