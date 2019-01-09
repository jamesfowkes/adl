#include "adl.h"

#include "adl-util-limited-range-int.h"
#include "integer-param.h"

void adl_custom_setup(const adl_devices_struct& devices, const adl_params_struct& params)
{
    (void)devices; (void)params;

    params.pMy_Integer->load();
    adl_logln(LOG_APP, "Loaded integer setting %d", params.pMy_Integer->get());
}

void adl_custom_loop(const adl_devices_struct& devices, const adl_params_struct& params)
{
    (void)devices;
    params.pMy_Integer->save();
}
