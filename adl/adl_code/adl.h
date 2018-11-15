#ifndef _ADL_H_
#define _ADL_H_

#include <Arduino.h>

#include "adl-defs.h"
#include "adl-nv.h"
#include "adl-logging.h"
#include "adl-util.h"
#include "device.h"
#include "parameter.h"
#include "adl-interface.h"
#include "adl-callbacks.h"
#include "adl-messages.h"
#include "protocol.h"

#define inrange(n, lo, hi) ((lo <= n) && (hi >= n))

#define lastinloop(i, loopmax) ((i == (loopmax - 1)))

#define incrementwithrollover(var, max) (var = (var < max) ? var + 1 : 0)
#define decrementwithrollover(var, max) (var = (var > 0) ? var - 1 : max)

#endif
