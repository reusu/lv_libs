# lv_libs
lvgl font render and image decoder libs for esp32

```
#include <lv_filesystem.h>
#include <lv_freetype.h>
#include <lv_bmp.h>
#include <lv_jpeg.h>
#include <lv_png.h>
#include <lv_gif.h>
...
lv_init();
lv_fs_init();
lv_bmp_init();
lv_jpeg_init();
lv_png_init();
...
lv_obj_clean(lv_scr_act());
lv_freetype_init(64, 8, 0);

static lv_ft_info_t wenquanyi32;
wenquanyi32.name = "S:/font/wenquanyi_micro/wenquanyi_micro.ttf";
wenquanyi32.weight = 32;
wenquanyi32.style = FT_FONT_STYLE_NORMAL;
lv_ft_font_init(&wenquanyi32);

boot_label = lv_label_create(lv_scr_act());
lv_obj_set_width(boot_label, 540);
lv_obj_set_style_text_align(boot_label, LV_TEXT_ALIGN_CENTER, 0);
lv_label_set_text(boot_label, "Hello LVGL (Ver8.0.2)");
lv_obj_set_style_text_font(boot_label, wenquanyi32.font, 0);
lv_obj_align_to(boot_label, lv_scr_act(), LV_ALIGN_CENTER, 0, 0);

static lv_ft_info_t microsoft24;
microsoft24.name = "S:/font/microsoft_yahei/microsoft_yahei.ttf";
microsoft24.weight = 24;
microsoft24.style = FT_FONT_STYLE_NORMAL;
lv_ft_font_init(&microsoft24);

lv_obj_t* top_label = lv_label_create(lv_scr_act());
lv_obj_set_width(top_label, 540);
lv_obj_set_style_text_align(top_label, LV_TEXT_ALIGN_CENTER, 0);
lv_label_set_text(top_label, "Hello LVGL (Ver8.0.2)");
lv_obj_set_style_text_font(top_label, microsoft24.font, 0);
lv_obj_align_to(top_label, lv_scr_act(), LV_ALIGN_TOP_MID, 0, 0);

static lv_ft_info_t awesome16;
awesome16.name = "S:/font/font_awesome/fa-solid-900.ttf";
awesome16.weight = 16;
awesome16.style = FT_FONT_STYLE_NORMAL;
lv_ft_font_init(&awesome16);

lv_obj_t* bot_label = lv_label_create(lv_scr_act());
lv_obj_set_width(bot_label, 540);
lv_obj_set_style_text_align(bot_label, LV_TEXT_ALIGN_CENTER, 0);
lv_label_set_text(bot_label, LV_SYMBOL_OK);
lv_obj_set_style_text_font(bot_label, awesome16.font, 0);
lv_obj_align_to(bot_label, lv_scr_act(), LV_ALIGN_BOTTOM_MID, 0, 0);

lv_obj_t* left_top_img = lv_img_create(lv_scr_act());
lv_img_set_src(left_top_img, "S:/01.jpg");
lv_obj_align_to(left_top_img, lv_scr_act(), LV_ALIGN_TOP_LEFT, 0, 0);

lv_obj_t* left_bot_img = lv_img_create(lv_scr_act());
lv_img_set_src(left_bot_img, "S:/01.bmp");
lv_obj_align_to(left_bot_img, lv_scr_act(), LV_ALIGN_BOTTOM_LEFT, 0, 0);

lv_obj_t* right_top_img = lv_img_create(lv_scr_act());
lv_img_set_src(right_top_img, "S:/01.png");
lv_obj_align_to(right_top_img, lv_scr_act(), LV_ALIGN_TOP_RIGHT, 0, 0);

lv_obj_t* right_bot_img = lv_gif_create_from_file(lv_scr_act(), "S:/01.gif");
lv_obj_align_to(right_bot_img, lv_scr_act(), LV_ALIGN_BOTTOM_RIGHT, 0, 0);
  
```

![QQ图片20210907221627](https://user-images.githubusercontent.com/8424240/132360309-907e80dd-abec-4aa5-9c37-61ef7c34bd32.jpg)

