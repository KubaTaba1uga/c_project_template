#include <stumpless.h>
void _log_info(char *msg);

void log_info(char *fmt, ...) {
  char local_log_entry[255]; // this should really be sized appropriately
                             // possibly in response to a call to vsnprintf()
  va_list vl;
  va_start(vl, fmt);

  vsnprintf(local_log_entry, sizeof(local_log_entry), fmt, vl);

  va_end(vl);

  _log_info(local_log_entry);
}

void _log_info(char *msg) {

  struct stumpless_target *target;

  target = stumpless_open_stdout_target("console logger");

  stump_i(msg);

  stumpless_close_target(target);
}
