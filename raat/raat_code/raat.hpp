#ifndef _RAAT_H_
#define _RAAT_H_

#ifndef BEHAVETESTS
#include <Arduino.h>
#endif

#include "raat-defs.hpp"
#include "raat-nv.hpp"
#include "raat-serial.hpp"
#include "raat-logging.hpp"
#include "raat-util.hpp"
#include "device.hpp"
#include "parameter.hpp"
#include "raat-interface.hpp"
#include "raat-messages.hpp"
#include "protocol.hpp"
#include "raat-application.hpp"

#include "raat-callbacks.hpp"

#define inrange(n, lo, hi) ((lo <= n) && (hi >= n))

#define lastinloop(i, loopmax) ((i == (loopmax - 1)))

#define incrementwithrollover(var, max) (var = (var < max) ? var + 1 : 0)
#define decrementwithrollover(var, max) (var = (var > 0) ? var - 1 : max)

#define incrementwithlimit(var, lim) (var = (var < lim) ? var + 1 : lim)
#define decrementwithlimit(var, lim) (var = (var > lim) ? var - 1 : lim)

#endif
