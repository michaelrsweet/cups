/*
 * CUPS service definitions.
 *
 * Copyright © 2007-2018 by Apple Inc.
 *
 * Licensed under Apache License v2.0.  See the file "LICENSE" for more
 * information.
 */

#ifndef _CUPS_SERVICE_H_
#  define _CUPS_SERVICE_H_

/*
 * Include necessary headers...
 */

#include <cups/cups.h>


/*
 * C++ magic...
 */

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */


/*
 * Constants...
 */

enum cupss_event_e			/**** notify-events bit values ****/
{
  CUPSS_EVENT_DOCUMENT_COMPLETED = 0x00000001,
					/* document-completed */
  CUPSS_EVENT_DOCUMENT_CONFIG_CHANGED = 0x00000002,
					/* document-config-changed */
  CUPSS_EVENT_DOCUMENT_CREATED = 0x00000004,
					/* document-created */
  CUPSS_EVENT_DOCUMENT_FETCHABLE = 0x00000008,
					/* document-fetchable */
  CUPSS_EVENT_DOCUMENT_STATE_CHANGED = 0x00000010,
					/* document-state-changed */
  CUPSS_EVENT_DOCUMENT_STOPPED = 0x00000020,
					/* document-stopped */

  CUPSS_EVENT_JOB_COMPLETED = 0x00000040,
					/* job-completed */
  CUPSS_EVENT_JOB_CONFIG_CHANGED = 0x00000080,
					/* job-config-changed */
  CUPSS_EVENT_JOB_CREATED = 0x00000100,	/* job-created */
  CUPSS_EVENT_JOB_FETCHABLE = 0x00000200,
					/* job-fetchable */
  CUPSS_EVENT_JOB_PROGRESS = 0x00000400,
					/* job-progress */
  CUPSS_EVENT_JOB_STATE_CHANGED = 0x00000800,
					/* job-state-changed */
  CUPSS_EVENT_JOB_STOPPED = 0x00001000,	/* job-stopped */

  CUPSS_EVENT_PRINTER_CONFIG_CHANGED = 0x00002000,
					/* printer-config-changed */
  CUPSS_EVENT_PRINTER_FINISHINGS_CHANGED = 0x00004000,
					/* printer-finishings-changed */
  CUPSS_EVENT_PRINTER_MEDIA_CHANGED = 0x00008000,
					/* printer-media-changed */
  CUPSS_EVENT_PRINTER_QUEUE_ORDER_CHANGED = 0x00010000,
					/* printer-queue-order-changed */
  CUPSS_EVENT_PRINTER_RESTARTED = 0x00020000,
					/* printer-restarted */
  CUPSS_EVENT_PRINTER_SHUTDOWN = 0x00040000,
					/* printer-shutdown */
  CUPSS_EVENT_PRINTER_STATE_CHANGED = 0x00080000,
					/* printer-state-changed */
  CUPSS_EVENT_PRINTER_STOPPED = 0x00100000,
					/* printer-stopped */

  CUPSS_EVENT_RESOURCE_CANCELED = 0x00200000,
					/* resource-canceled */
  CUPSS_EVENT_RESOURCE_CONFIG_CHANGED = 0x00400000,
					/* resource-config-changed */
  CUPSS_EVENT_RESOURCE_CREATED = 0x00800000,
					/* resource-created */
  CUPSS_EVENT_RESOURCE_INSTALLED = 0x01000000,
					/* resource-installed */
  CUPSS_EVENT_RESOURCE_STATE_CHANGED = 0x02000000,
					/* resource-state-changed */

  CUPSS_EVENT_PRINTER_CREATED = 0x04000000,
					/* printer-created */
  CUPSS_EVENT_PRINTER_DELETED = 0x08000000,
					/* printer-deleted */

  CUPSS_EVENT_SYSTEM_CONFIG_CHANGED = 0x10000000,
					/* system-config-changed */
  CUPSS_EVENT_SYSTEM_STATE_CHANGED = 0x20000000,
					/* system-state-changed */
  CUPSS_EVENT_SYSTEM_STOPPED = 0x40000000,
					/* system-stopped */

  /* "Wildcard" values... */
  CUPSS_EVENT_NONE = 0x00000000,	/* No events */
  CUPSS_EVENT_DOCUMENT_ALL = 0x0000003f,/* All document events */
  CUPSS_EVENT_DOCUMENT_STATE_ALL = 0x00000037,
					/* All document state events */
  CUPSS_EVENT_JOB_ALL = 0x00001fc0,	/* All job events */
  CUPSS_EVENT_JOB_STATE_ALL = 0x00001940,
					/* All job state events */
  CUPSS_EVENT_PRINTER_ALL = 0x001fe000,	/* All printer events */
  CUPSS_EVENT_PRINTER_CONFIG_ALL = 0x0000e000,
					/* All printer configuration events */
  CUPSS_EVENT_PRINTER_STATE_ALL = 0x001e0000,
					/* All printer state events */
  CUPSS_EVENT_ALL = 0x7fffffff		/* All events */
};
typedef unsigned int cupss_event_t;	/**** notify-events bitfield type ****/

enum cupss_identify_e			/* identify-actions bit values */
{
  CUPSS_IDENTIFY_NONE = 0x00,		/* none */
  CUPSS_IDENTIFY_DISPLAY = 0x01,	/* display */
  CUPSS_IDENTIFY_SOUND = 0x02		/* sound */
};
typedef unsigned int cupss_identify_t;	/* identify-actions bitfield type */

enum cupss_jreason_e			/* job-state-reasons bit values */
{
  CUPSS_JREASON_NONE = 0x00000000,	/* none */
  CUPSS_JREASON_ABORTED_BY_SYSTEM = 0x00000001,
					/* aborted-by-system */
  CUPSS_JREASON_COMPRESSION_ERROR = 0x00000002,
					/* compression-error */
  CUPSS_JREASON_DOCUMENT_ACCESS_ERROR = 0x00000004,
					/* document-access-error */
  CUPSS_JREASON_DOCUMENT_FORMAT_ERROR = 0x00000008,
					/* document-format-error */
  CUPSS_JREASON_DOCUMENT_PASSWORD_ERROR = 0x00000010,
					/* document-password-error */
  CUPSS_JREASON_DOCUMENT_PERMISSION_ERROR = 0x00000020,
					/* document-permission-error */
  CUPSS_JREASON_DOCUMENT_SECURITY_ERROR = 0x00000040,
					/* document-security-error */
  CUPSS_JREASON_DOCUMENT_UNPRINTABLE_ERROR = 0x00000080,
					/* document-unprintable-error */
  CUPSS_JREASON_ERRORS_DETECTED = 0x00000100,
					/* errors-detected */
  CUPSS_JREASON_JOB_CANCELED_AT_DEVICE = 0x00000200,
					/* job-canceled-at-device */
  CUPSS_JREASON_JOB_CANCELED_BY_USER = 0x00000400,
					/* job-canceled-by-user */
  CUPSS_JREASON_JOB_COMPLETED_SUCCESSFULLY = 0x00000800,
					/* job-completed-successfully */
  CUPSS_JREASON_JOB_COMPLETED_WITH_ERRORS = 0x00001000,
					/* job-completed-with-errors */
  CUPSS_JREASON_JOB_COMPLETED_WITH_WARNINGS = 0x00002000,
					/* job-completed-with-warnings */
  CUPSS_JREASON_JOB_DATA_INSUFFICIENT = 0x00004000,
					/* job-data-insufficient */
  CUPSS_JREASON_JOB_FETCHABLE = 0x00008000,
					/* job-fetchable */
  CUPSS_JREASON_JOB_HOLD_UNTIL_SPECIFIED = 0x00010000,
					/* job-hold-until-specified */
  CUPSS_JREASON_JOB_INCOMING = 0x00020000,
					/* job-incoming */
  CUPSS_JREASON_JOB_PASSWORD_WAIT = 0x00040000,
					/* job-password-wait */
  CUPSS_JREASON_JOB_PRINTING = 0x00080000,
					/* job-printing */
  CUPSS_JREASON_JOB_QUEUED = 0x00100000,
					/* job-queued */
  CUPSS_JREASON_JOB_SPOOLING = 0x00200000,
					/* job-spooling */
  CUPSS_JREASON_JOB_STOPPED = 0x00400000,
					/* job-stopped */
  CUPSS_JREASON_JOB_TRANSFORMING = 0x00800000,
					/* job-transforming */
  CUPSS_JREASON_PRINTER_STOPPED = 0x01000000,
					/* printer-stopped */
  CUPSS_JREASON_PRINTER_STOPPED_PARTLY = 0x02000000,
					/* printer-stopped-partly */
  CUPSS_JREASON_PROCESSING_TO_STOP_POINT = 0x04000000,
					/* processing-to-stop-point */
  CUPSS_JREASON_QUEUED_IN_DEVICE = 0x08000000,
					/* queued-in-device */
  CUPSS_JREASON_WARNINGS_DETECTED = 0x10000000
					/* warnings-detected */
};
typedef unsigned int cupss_jreason_t;	/* job-state-reasons bitfield type */


typedef enum cupss_loglevel_e		/**** Log Level values ****/
{
  CUPSS_LOGLEVEL_ERROR,			/* Error message */
  CUPSS_LOGLEVEL_INFO,			/* Informational message */
  CUPSS_LOGLEVEL_DEBUG			/* Debugging message */
} server_loglevel_t;


enum cupss_preason_e			/* printer-state-reasons bit values */
{
  CUPSS_PREASON_NONE = 0x0000,		/* none */
  CUPSS_PREASON_OTHER = 0x0001,		/* other */
  CUPSS_PREASON_COVER_OPEN = 0x0002,	/* cover-open */
  CUPSS_PREASON_INPUT_TRAY_MISSING = 0x0004,
					/* input-tray-missing */
  CUPSS_PREASON_MARKER_SUPPLY_EMPTY = 0x0008,
					/* marker-supply-empty */
  CUPSS_PREASON_MARKER_SUPPLY_LOW = 0x0010,
					/* marker-supply-low */
  CUPSS_PREASON_MARKER_WASTE_ALMOST_FULL = 0x0020,
					/* marker-waste-almost-full */
  CUPSS_PREASON_MARKER_WASTE_FULL = 0x0040,
					/* marker-waste-full */
  CUPSS_PREASON_MEDIA_EMPTY = 0x0080,	/* media-empty */
  CUPSS_PREASON_MEDIA_JAM = 0x0100,	/* media-jam */
  CUPSS_PREASON_MEDIA_LOW = 0x0200,	/* media-low */
  CUPSS_PREASON_MEDIA_NEEDED = 0x0400,	/* media-needed */
  CUPSS_PREASON_MOVING_TO_PAUSED = 0x0800,
					/* moving-to-paused */
  CUPSS_PREASON_PAUSED = 0x1000,	/* paused */
  CUPSS_PREASON_PRINTER_RESTARTED = 0x2000,
					/* printer-restarted */
  CUPSS_PREASON_PRINTER_SHUTDOWN = 0x4000,
					/* printer-shutdown */
  CUPSS_PREASON_SPOOL_AREA_FULL = 0x8000,
					/* spool-area-full */
  CUPSS_PREASON_TONER_EMPTY = 0x10000,	/* toner-empty */
  CUPSS_PREASON_TONER_LOW = 0x20000,	/* toner-low */
  CUPSS_PREASON_IDENTIFY_PRINTER_REQUESTED = 0x40000,
					/* identify-printer-requested */
  CUPSS_PREASON_DELETING = 0x80000	/* deleting */
};
typedef unsigned int cupss_preason_t;	/**** printer-state-reasons bitfield type ****/

typedef enum cupss_type_e		/**** Service types ****/
{
  CUPSS_TYPE_PRINT,			/* IPP Print service */
  CUPSS_TYPE_PRINT3D,			/* IPP 3D Print service */
  CUPSS_TYPE_FAXOUT			/* IPP FaxOut service */
} cupss_type_t;


/*
 * Types and structures...
 */

typedef struct _cupss_client_s cupss_client_t;
					/**** Client (Connection) Object ****/
typedef struct _cupss_document_s cupss_document_t;
					/**** Document Object ****/
typedef struct _cupss_job_s cupss_job_t;
					/**** Job Object ****/
typedef void (*cupss_logcb_t)(void *user_data, cupss_loglevel_t level, const char *message);
					/**** Logging Callback ****/
typedef struct _cupss_printer_s cupss_printer_t;
					/**** Printer (Service) Object ****/
typedef struct _cupss_resource_s cupss_resource_t;
					/**** Resource Object ****/
typedef struct _cupss_subscription_s cupss_subscription_t;
					/**** Subscription Object ****/
typedef struct _cupss_system_s cupss_system_t;
					/**** System Service Object ****/


/*
 * Functions...
 */


#  ifdef __cplusplus
}
#  endif /* __cplusplus */

#endif /* !_CUPSE_SERVICE_H_ */
