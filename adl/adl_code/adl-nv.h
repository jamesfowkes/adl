#ifndef _ADL_NV_H_
#define _ADL_NV_H_

typedef struct _adl_nv_location
{
	uint16_t size;
	ADL_NV_ADDR address;
} ADL_NV_LOCATION;

void adl_nv_alloc(ADL_NV_LOCATION& to_alloc);
void adl_nv_load(void * dst, ADL_NV_LOCATION& load_from);
void adl_nv_save(void * src, ADL_NV_LOCATION& save_to);

#endif

