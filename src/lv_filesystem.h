/**
 * @file lv_filesystem.h
 *
 */

#ifndef LV_FILESYSTEM_H
#define LV_FILESYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void lv_fs_spiffs_init(char letter = 'P');
void lv_fs_ffat_init(char letter = 'F');
void lv_fs_sd_init(char letter = 'S');
void lv_fs_init();

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_FILESYSTEM_H*/
