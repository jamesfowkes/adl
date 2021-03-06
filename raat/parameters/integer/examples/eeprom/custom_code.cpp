#include "raat.hpp"

#include "raat-util-limited-range-int.hpp"
#include "integer-param.hpp"

void raat_custom_setup(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)devices; (void)params;

    params.pMy_Integer->load();
    raat_logln(LOG_APP, "Loaded integer setting %d", params.pMy_Integer->get());
}

void raat_custom_loop(const raat_devices_struct& devices, const raat_params_struct& params)
{
    (void)devices;
    params.pMy_Integer->save();
}
