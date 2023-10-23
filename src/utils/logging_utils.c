#include <stddef.h>

#include <stumpless.h>

#include "../config.h"
#include "stumpless/severity.h"

struct stumpless_target *loggers[] = {NULL};
size_t loggers_no = sizeof(loggers) / sizeof(struct stumpless_target *);

void init_loggers(void) {
  loggers[0] = stumpless_open_stdout_target("console logger");
}

void destroy_loggers(void) {
  size_t i;

  for (i = 0; i < loggers_no; i++) {
    stumpless_close_target(loggers[i]);
  }

  stumpless_free_all();
}

inline void create_log_entry(char *msg, char *msg_id,
                             // Stumpless data
                             struct stumpless_entry **entry,
                             enum stumpless_severity severity);
inline void log_msg(char *msg, char *msg_id, enum stumpless_severity severity);
inline void emmit_log_entry(struct stumpless_entry *entry);

void log_info(char *msg_id, char *fmt, ...) {
  char local_log_entry[255];

  va_list vl;
  va_start(vl, fmt);

  vsnprintf(local_log_entry, sizeof(local_log_entry), fmt, vl);

  va_end(vl);

  log_msg(local_log_entry, msg_id, STUMPLESS_SEVERITY_INFO);
}

void log_msg(char *msg, char *msg_id, enum stumpless_severity severity) {
  struct stumpless_entry *entry = NULL;

  create_log_entry(msg, msg_id, &entry, severity);

  if (!entry) {
    // TO-DO return error
  }

  emmit_log_entry(entry);

  if (!entry) {
    // TO-DO return error if emmiting has failed
  }
}

void create_log_entry(char *msg, char *msg_id,
                      // Stumpless data
                      struct stumpless_entry **entry,
                      enum stumpless_severity severity) {
  *entry = stumpless_new_entry(STUMPLESS_FACILITY_USER, severity,
                               "project-name", msg_id, msg);
  if (!*entry) {
    // TO-DO return error
  }
}

void emmit_log_entry(struct stumpless_entry *entry) {
  int result;
  size_t i;

  for (i = 0; i < loggers_no; i++) {

    result = stumpless_add_entry(loggers[i], entry);

    if (result < 0) {
      // TO-DO return error
    }
  }
}
