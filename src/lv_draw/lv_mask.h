/**
 * @file lv_mask.h
 *
 */

#ifndef LV_MASK_H
#define LV_MASK_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdbool.h>
#include "../lv_misc/lv_area.h"
#include "../lv_misc/lv_color.h"

/*********************
 *      DEFINES
 *********************/
#define LV_MASK_ID_INV  (-1)

/**********************
 *      TYPEDEFS
 **********************/

enum {
    LV_MASK_RES_FULL_COVER,
    LV_MASK_RES_FULL_TRANSP,
    LV_MASK_RES_CHANGED,
};

typedef uint8_t lv_mask_res_t;


enum {
    LV_LINE_MASK_SIDE_LEFT = 0,
    LV_LINE_MASK_SIDE_RIGHT,
    LV_LINE_MASK_SIDE_TOP,
    LV_LINE_MASK_SIDE_BOTTOM,
};

typedef uint8_t lv_line_mask_side_t;

typedef struct {
    lv_point_t origo;
    /* X / (1024*Y) steepness (X is 0..1023 range). What is the change of X in 1024 Y?*/
    int32_t xy_steep;

    /* Y / (1024*X) steepness (Y is 0..1023 range). What is the change of Y in 1024 X?*/
    int32_t yx_steep;

    /*Helper which stores yx_steep for flat lines and xy_steep for steep (non flat) lines */
    int32_t steep;

    /*Steepness in 1 px in 0..255 range. Used only by flat lines. */
    int32_t spx;

    /*1: It's a flat line? (Neare to horizontal)*/
    uint8_t flat :1;

    /*Which side to keep?*/
    lv_line_mask_side_t side :2;

    /* Invert the mask. The default is: Keep the left part.
     * It is used to select left/right/top/bottom*/
    uint8_t inv:1;
}lv_mask_line_param_t;


typedef struct {
    lv_point_t origo;
    lv_coord_t start_angle;
    lv_coord_t end_angle;
    lv_mask_line_param_t start_line;
    lv_mask_line_param_t end_line;
    uint16_t delta_deg;
}lv_mask_angle_param_t;

typedef struct {
    lv_area_t rect;
    lv_coord_t radius;

    /* Invert the mask. The default is: Keep the are inside.*/
    uint8_t inv:1;
}lv_mask_radius_param_t;


typedef union {
    lv_mask_line_param_t line;
    lv_mask_radius_param_t radius;
    lv_mask_angle_param_t angle;
}lv_mask_param_t;

typedef lv_mask_res_t (*lv_mask_cb_t)(lv_opa_t * mask_buf, lv_coord_t abs_x, lv_coord_t abs_y, lv_coord_t len, lv_mask_param_t * p);

/**********************
 * GLOBAL PROTOTYPES
 **********************/

int16_t lv_mask_add(lv_mask_cb_t mask_cb, lv_mask_param_t * param, void * custom_id);
void lv_mask_remove_id(int16_t id);
void lv_mask_remove_custom(void * custom_id);
uint8_t lv_mask_get_cnt(void);

lv_mask_res_t lv_mask_apply(lv_opa_t * mask_buf, lv_coord_t abs_x, lv_coord_t abs_y, lv_coord_t len);

void lv_mask_line_points_init(lv_mask_param_t * param, lv_coord_t p1x, lv_coord_t p1y, lv_coord_t p2x, lv_coord_t p2y, lv_line_mask_side_t side);
void lv_mask_line_angle_init(lv_mask_param_t * param, lv_coord_t p1x, lv_coord_t p1y, int16_t deg, lv_line_mask_side_t side);
lv_mask_res_t lv_mask_line(lv_opa_t * mask_buf, lv_coord_t abs_x, lv_coord_t abs_y, lv_coord_t len, lv_mask_param_t * param);


void lv_mask_radius_init(lv_mask_param_t * param, const lv_area_t * rect, lv_coord_t radius, bool inv);
lv_mask_res_t lv_mask_radius(lv_opa_t * mask_buf, lv_coord_t abs_x, lv_coord_t abs_y, lv_coord_t len, lv_mask_param_t * param);

void lv_mask_angle_init(lv_mask_param_t * param, lv_coord_t origio_x, lv_coord_t origo_y, lv_coord_t start_angle, lv_coord_t end_angle);
lv_mask_res_t lv_mask_angle(lv_opa_t * mask_buf, lv_coord_t abs_x, lv_coord_t abs_y, lv_coord_t len, lv_mask_param_t * param);


/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_MASK_H*/