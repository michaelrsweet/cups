/*
 * CUPS service job object code.
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


VAR const char * const server_jreasons[29]
VALUE({					/* Strings for bits */
  /* "none" is implied for no bits set */
  "aborted-by-system",
  "compression-error",
  "document-access-error",
  "document-format-error",
  "document-password-error",
  "document-permission-error",
  "document-security-error",
  "document-unprintable-error",
  "errors-detected",
  "job-canceled-at-device",
  "job-canceled-by-user",
  "job-completed-successfully",
  "job-completed-with-errors",
  "job-completed-with-warnings",
  "job-data-insufficient",
  "job-fetchable",
  "job-hold-until-specified",
  "job-incoming",
  "job-password-wait",
  "job-printing",
  "job-queued",
  "job-spooling",
  "job-stopped",
  "job-transforming",
  "printer-stopped",
  "printer-stopped-partly",
  "processing-to-stop-point",
  "queued-in-device",
  "warnings-detected"
});
