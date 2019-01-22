#ifndef _RAAT_NV_H_
#define _RAAT_NV_H_

typedef struct _raat_nv_location
{
	uint16_t size;
	RAAT_NV_ADDR address;
} RAAT_NV_LOCATION;

void raat_nonvolatile_setup();
void raat_nv_alloc(RAAT_NV_LOCATION& to_alloc);
void raat_nv_load(void * dst, RAAT_NV_LOCATION& load_from);
void raat_nv_save(void * src, RAAT_NV_LOCATION& save_to);

#endif

