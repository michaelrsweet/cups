/*
 * CUPS service subscription/notification code.
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


VAR const char * const server_events[31]
VALUE({					/* Strings for bits */
  /* "none" is implied for no bits set */
  "document-completed",
  "document-config-changed",
  "document-created",
  "document-fetchable",
  "document-state-changed",
  "document-stopped",

  "job-completed",
  "job-config-changed",
  "job-created",
  "job-fetchable",
  "job-progress",
  "job-state-changed",
  "job-stopped",

  "printer-config-changed",
  "printer-finishings-changed",
  "printer-media-changed",
  "printer-queue-order-changed",
  "printer-restarted",
  "printer-shutdown",
  "printer-state-changed",
  "printer-stopped",

  "resource-canceled",
  "resource-config-changed",
  "resource-created",
  "resource-installed",
  "resource-changed",

  "printer-created",
  "printer-deleted",

  "system-config-changed",
  "system-state-changed",
  "system-stopped"
});
