#include "stumpless/target.h"
#include <stddef.h>

#include <stumpless.h>

struct stumpless_target *targets[] = {NULL};
size_t targets_no = sizeof(targets) / sizeof(struct stumpless_target *);

void init_targets(void) {
  targets[0] = stumpless_open_stdout_target("console logger");
}

void destroy_targets(void) {
  size_t i;

  for (i = 0; i < targets_no; i++) {
    stumpless_close_target(targets[i]);
  }

  stumpless_free_all();
}

void _log_info(char *msg, char *msg_id);

void log_info(char *msg_id, char *fmt, ...) {
  char local_log_entry[255]; // this should really be sized appropriately
                             // possibly in response to a call to vsnprintf()
  va_list vl;
  va_start(vl, fmt);

  vsnprintf(local_log_entry, sizeof(local_log_entry), fmt, vl);

  va_end(vl);

  _log_info(local_log_entry, msg_id);
}

void _log_info(char *msg, char *msg_id) {
  struct stumpless_entry *entry;
  size_t i;
  entry = stumpless_new_entry(STUMPLESS_FACILITY_USER, STUMPLESS_SEVERITY_INFO,
                              "project-name", msg_id, msg);

  for (i = 0; i < targets_no; i++) {
    stumpless_add_entry(targets[i], entry);
  }
}
