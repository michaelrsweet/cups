/*
 * CUPS service printer object code.
 *
 * Copyright © 2007-2018 by Apple Inc.
 *
 * Licensed under Apache License v2.0.  See the file "LICENSE" for more
 * information.
 */

/*
 * Include necessary headers...
 */

#include "service-private.h"


VAR const char * const server_preasons[20]
VALUE({					/* Strings for bits */
  /* "none" is implied for no bits set */
  "other",
  "cover-open",
  "input-tray-missing",
  "marker-supply-empty",
  "marker-supply-low",
  "marker-waste-almost-full",
  "marker-waste-full",
  "media-empty",
  "media-jam",
  "media-low",
  "media-needed",
  "moving-to-paused",
  "paused",
  "printer-restarted",
  "printer-shutdown",
  "spool-area-full",
  "toner-empty",
  "toner-low",
  "identify-printer-requested",
  "deleting"
});
