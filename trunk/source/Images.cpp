#include <ulib/ulib.h>
#include "Images.h"
#include "gfx_creep.h"
#include "gfx_health.h"
#include "gfx_bullet.h"
#include "gfx_select.h"

const T_IMAGE images[] = {
	{ID_CREEP,    (const char*)gfx_creep,  (int)gfx_creep_size,   16, 16, 10},
	{ID_HEALTH,   (const char*)gfx_health, (int)gfx_health_size,  31, 4,  10},
	{ID_BULLET,   (const char*)gfx_bullet, (int)gfx_bullet_size,  8,  8,  10},
	{ID_SELECTOR, (const char*)gfx_select, (int)gfx_select_size,  24, 24, 10},
};

unsigned int getImagesSize() {
	return (sizeof(images)/sizeof(T_IMAGE));
}
