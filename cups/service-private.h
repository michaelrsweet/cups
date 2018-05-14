/*
 * Private CUPS service definitions.
 *
 * Copyright © 2007-2018 by Apple Inc.
 *
 * Licensed under Apache License v2.0.  See the file "LICENSE" for more
 * information.
 */

#ifndef _CUPS_SERVICE_PRIVATE_H_
#  define _CUPS_SERVICE_PRIVATE_H_

/*
 * Include necessary headers...
 */

#include "service.h"
#include "thread-private.h"


/*
 * C++ magic...
 */

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */


/*
 * Constants...
 */

/* Maximum number of resources per job/printer */
#  define CUPSS_RESOURCES_MAX				100

/* Maximum lease duration value from RFC 3995 - 2^26-1 seconds or ~2 years */
#  define CUPSS_NOTIFY_LEASE_DURATION_MAX		67108863
/* But a value of 0 means "never expires"... */
#  define CUPSS_NOTIFY_LEASE_DURATION_FOREVER		0
/* Default duration is 1 day */
#  define CUPSS_NOTIFY_LEASE_DURATION_DEFAULT		86400

/* ippget event lifetime is 5 minutes */
#  define CUPSS_IPPGET_EVENT_LIFE			300

/* URL schemes and DNS-SD types for IPP and web resources... */
#  define CUPSS_IPP_SCHEME "ipp"
#  define CUPSS_IPP_TYPE "_ipp._tcp"
#  define CUPSS_IPPS_SCHEME "ipps"
#  define CUPSS_IPPS_TYPE "_ipps._tcp"
#  define CUPSS_IPPS_3D_TYPE "_ipps-3d._tcp"
#  define CUPSS_WEB_TYPE "_http._tcp"
#  define CUPSS_HTTP_SCHEME "http"
#  define CUPSS_HTTPS_SCHEME "https"

/* Access scopes */
#  define CUPSS_SCOPE_ADMIN	"admin"
#  define CUPSS_SCOPE_ALL	"all"
#  define CUPSS_SCOPE_DEFAULT	"default"
#  define CUPSS_SCOPE_NONE	"none"
#  define CUPSS_SCOPE_OWNER	"owner"

/* Group constants */
#  define CUPSS_GROUP_NONE	(gid_t)-1
#  define CUPSS_GROUP_WHEEL	(gid_t)0



/*
 * Types and structures...
 */

struct _cupss_client_s			/**** Client (Connection) Object ****/
{
  int			number;		/* Client number */
  http_t		*http;		/* HTTP connection */
  ipp_t			*request,	/* IPP request */
			*response;	/* IPP response */
  time_t		start;		/* Request start time */
  http_state_t		operation;	/* Request operation */
  ipp_op_t		operation_id;	/* IPP operation-id */
  char			uri[1024],	/* Request URI */
			*options;	/* URI options */
  http_addr_t		addr;		/* Client address */
  char			hostname[256],	/* Client hostname */
			username[32];	/* Client authenticated username */
  cupss_printer_t	*printer;	/* Printer */
  cupss_job_t		*job;		/* Current job, if any */
  int			fetch_compression,
					/* Compress file? */
			fetch_file;	/* File to fetch */
};


typedef struct _cupss_device_s		/**** Output Device data ****/
{
  _cups_rwlock_t	rwlock;		/* Printer lock */
  char			*name,		/* printer-name (mapped to output-device) */
			*uuid;		/* output-device-uuid */
  ipp_t			*attrs;		/* All printer attributes */
  ipp_pstate_t		state;		/* printer-state value */
  cupss_preason_t	reasons;	/* printer-state-reasons values */
} _cupss_device_t;

struct _cupss_document_s		/**** Document Object ****/
{
};


typedef struct _cupss_filter_s		/**** Attribute filter ****/
{
  cups_array_t		*ra;		/* Requested attributes */
  cups_array_t		*pa;		/* Private attributes */
  ipp_tag_t		group_tag;	/* Group to copy */
} _cupss_filter_t;


struct _cupss_job_s 			/**** Job Object ****/
{
  int			id;		/* job-id */
  _cups_rwlock_t	rwlock;		/* Job lock */
  const char		*name,		/* job-name */
			*username,	/* job-originating-user-name */
			*format;	/* document-format */
  int			priority;	/* job-priority */
  char			*dev_uuid;	/* output-device-uuid-assigned */
  ipp_jstate_t		state,		/* job-state value */
			dev_state;	/* output-device-job-state value */
  cupss_jreason_t	state_reasons,	/* job-state-reasons values */
  			dev_state_reasons;
		      			/* output-device-job-state-reasons values */
  char			*dev_state_message;
					/* output-device-job-state-message value */
  time_t		hold_until,	/* job-hold-until time */
			created,	/* time-at-creation value */
			processing,	/* time-at-processing value */
			completed;	/* time-at-completed value */
  int			impressions,	/* job-impressions value */
			impcompleted;	/* job-impressions-completed value */
  ipp_t			*attrs;		/* Attributes */
  int			cancel;		/* Non-zero when job canceled */
  char			*filename;	/* Print file name */
  int			fd;		/* Print file descriptor */
  int			transform_pid;	/* Transform process ID, if any */
  cupss_printer_t	*printer;	/* Printer */
  int			num_resources,	/* Number of job resources */
			resources[CUPSS_RESOURCES_MAX];
					/* Job resource IDs */
};


typedef struct _cupss_lang_s		/**** Localization data ****/
{
  char			*lang,		/* Language code */
			*filename;	/* Strings file */
} _cupss_lang_t;


typedef struct _cupss_listener_s	/**** Listener data ****/
{
  int			fd;		/* Listener socket */
  char			host[256];	/* Hostname, if any */
  int			port;		/* Port number */
} _cupss_listener_t;


struct _cupss_printer_s			/**** Printer (Service) Object ****/
{
  int			id;		/* Printer ID */
  cupss_type_t		type;		/* Type of printer/service */
  _cups_rwlock_t	rwlock;		/* Printer lock */
  cupss_srv_t		ipp_ref,	/* Bonjour IPP service */
#ifdef HAVE_SSL
			ipps_ref,	/* Bonjour IPPS service */
#endif /* HAVE_SSL */
			http_ref,	/* Bonjour HTTP(S) service */
			printer_ref;	/* Bonjour LPD service */
  cupss_loc_t		geo_ref;	/* Bonjour geo-location */
  char			*default_uri,	/* Default/first URI */
			*dnssd_name,	/* printer-dnssd-name */
			*name,		/* printer-name */
			*resource;	/* Resource path */
  size_t		resourcelen;	/* Length of resource path */
  cupss_pinfo_t	pinfo;		/* Printer information */
  cups_array_t		*devices;	/* Associated devices */
  ipp_t			*dev_attrs;	/* Current device attributes */
  time_t		start_time;	/* Startup time */
  time_t		config_time;	/* printer-config-change-time */
  char			is_accepting,	/* printer-is-accepting-jobs value */
			is_deleted,	/* Is the printer being deleted? */
			is_shutdown;	/* Is the printer shutdown? */
  ipp_pstate_t		state,		/* printer-state value */
			dev_state;	/* Current device printer-state value */
  cupss_preason_t	state_reasons,	/* printer-state-reasons values */
			dev_reasons;	/* Current device printer-state-reasons values */
  time_t		state_time;	/* printer-state-change-time */
  cups_array_t		*jobs,		/* Jobs */
			*active_jobs,	/* Active jobs */
			*completed_jobs;/* Completed jobs */
  cupss_job_t		*processing_job;/* Current processing job */
  int			next_job_id;	/* Next job-id value */
  cupss_identify_t	identify_actions;
					/* identify-actions value, if any */
  char			*identify_message;
					/* Identify-Printer message value, if any */
  int			num_resources,	/* Number of printer resources */
			resources[CUPSS_RESOURCES_MAX];
					/* Printer resource IDs */
  ipp_t			*attrs;		/* Printer attributes */
  cups_array_t		*strings;	/* Strings (resource) files */
  gid_t			print_group,	/* Print group, if any */
			proxy_group;	/* Proxy group, if any */
  void			*user_data;	/* User data pointer */
};


typedef struct _cupss_privacy_s		/**** Privacy Attributes and Scope ****/
{
  cups_array_t		*public_attrs;	/* Public attributes */
  char			*scope;		/* Who gets to see private attributes */
} _cupss_privacy_t;


struct _cupss_resource_s		/**** Resource Object ****/
{
  int			id;		/* resource-id */
  _cups_rwlock_t	rwlock;		/* Resource lock */
  ipp_t			*attrs;		/* Resource attributes */
  ipp_rstate_t		state;		/* Resource state */
  char			*resource,	/* External resource path */
			*filename,	/* Local filename */
			*format;	/* MIME media type */
  int			use;		/* Use count */
};


struct _cupss_subscription_s		/**** Subscription Object ****/
{
  int			id;		/* notify-subscription-id */
  const char		*uuid;		/* notify-subscription-uuid */
  _cups_rwlock_t	rwlock;		/* Subscription lock */
  cupss_event_t		mask;		/* Event mask */
  cupss_printer_t	*printer;	/* Printer, if any */
  cupss_job_t		*job;		/* Job, if any */
  cupss_resource_t	*resource;	/* Resource, if any */
  ipp_t			*attrs;		/* Attributes */
  const char		*username;	/* notify-subscriber-user-name */
  int			lease;		/* notify-lease-duration */
  int			interval;	/* notify-time-interval */
  time_t		expire;		/* Lease expiration time */
  int			first_sequence,	/* First notify-sequence-number in cache */
			last_sequence;	/* Last notify-sequence-number used */
  cups_array_t		*events;	/* Events (ipp_t *'s) */
  int			pending_delete;	/* Non-zero when the subscription is about to be deleted/canceled */
};


struct _cupss_system_s			/**** System Service Object ****/
{
  _cups_rwlock_t	rwlock;		/* System lock */
  const char		*uuid;		/* system-uuid */

  ipp_t			*attrs;		/* Attributes */
  time_t		start_time,	/* Startup time */
			config_time;	/* Time of last config change */
  int			config_changes;	/* Number of config changes made */

  char			*auth_realm,	/* HTTP authentication realm */
			*auth_scheme;	/* HTTP authentication scheme */

  _cupss_privacy_t	doc_privacy,	/* Document privacy attributes/scope */
			job_privacy,	/* Job privacy attributes/scope */
			sub_privacy;	/* Subscription privacy attributes/scope */
  ipp_t			*privacy_attrs;	/* Privacy attributes for each service */

  cups_array_t		*listeners;	/* Listeners for service */

  cupss_logcb_t		log_cb;		/* Log callback */
  void			*log_data;	/* User data for log callback */
  cupss_loglevel_t	log_level;	/* Log level */

  int			MaxJobs  ,
                        MaxCompletedJobs  ,
                        NextPrinterId  ;
  cups_array_t	*Printers  ;
  int			RelaxedConformance  ;
  char		*ServerName  ;
  char		*SpoolDirectory  ;

#ifdef HAVE_DNSSD
  DNSServiceRef	DNSSDMaster  ;
#elif defined(HAVE_AVAHI)
  AvahiThreadedPoll	*DNSSDMaster  ;
  AvahiClient		*DNSSDClient  ;
#endif /* HAVE_DNSSD */
  char		*DNSSDSubType  ;

  _cups_rwlock_t	ResourcesRWLock  ;
  cups_array_t	*ResourcesById  ;
  cups_array_t	*ResourcesByPath  ;
  int			NextResourceId  ;

  _cups_mutex_t	NotificationMutex  ;
  _cups_cond_t	NotificationCondition  ;
  _cups_rwlock_t	SubscriptionsRWLock  ;
  cups_array_t	*Subscriptions  ;
  int			NextSubscriptionId  ;
};


/*
 * Functions...
 */


#  ifdef __cplusplus
}
#  endif /* __cplusplus */

#endif /* !_CUPSE_SERVICE_PRIVATE_H_ */
