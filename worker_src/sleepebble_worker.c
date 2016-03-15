#include <pebble_worker.h>

#define TIMESTAMP_LOG 1

static DataLoggingSessionRef s_session_ref;

const int value = 16;
const uint32_t num_values = 1;

static void tick_handler(struct tm *tick_time, TimeUnits changed) {
    /*
    DataLoggingResult res = data_logging_log(s_session_ref, 
                                             &value, 
                                             num_values);
    
    if (res != DATA_LOGGING_SUCCESS) {
        APP_LOG(APP_LOG_LEVEL_ERROR, "Error logging data: %d", (int)res);
    }
    */
    
    worker_launch_app();
}

static void init() {
    //s_session_ref = data_logging_create(TIMESTAMP_LOG,
    //                                    DATA_LOGGING_INT,
    //                                    sizeof(int),
    //                                    true);
    tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit() {
    //data_logging_finish(s_session_ref);
    tick_timer_service_unsubscribe();
}

int main(void) {
  init();
  worker_event_loop();
  deinit();
}