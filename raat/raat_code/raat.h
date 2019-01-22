#ifndef _RAAT_H_
#define _RAAT_H_

#include <Arduino.h>

#include "raat-defs.h"
#include "raat-nv.h"
#include "raat-serial.h"
#include "raat-logging.h"
#include "raat-util.h"
#include "device.h"
#include "parameter.h"
#include "raat-interface.h"
#include "raat-messages.h"
#include "protocol.h"
#include "raat-application.h"

#include "raat-callbacks.h"

#define inrange(n, lo, hi) ((lo <= n) && (hi >= n))

#define lastinloop(i, loopmax) ((i == (loopmax - 1)))

#define incrementwithrollover(var, max) (var = (var < max) ? var + 1 : 0)
#define decrementwithrollover(var, max) (var = (var > 0) ? var - 1 : max)

#define incrementwithlimit(var, lim) (var = (var < lim) ? var + 1 : lim)
#define decrementwithlimit(var, lim) (var = (var > lim) ? var - 1 : lim)

#endif
