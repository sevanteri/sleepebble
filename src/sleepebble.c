#include <pebble.h>

static Window *s_window;

static void start_worker() {
    AppWorkerResult res = APP_WORKER_RESULT_NOT_RUNNING;
    res = app_worker_launch();
    
    switch(res) {
        case APP_WORKER_RESULT_SUCCESS:
            APP_LOG(APP_LOG_LEVEL_INFO, "Worker launched");
            break;
        case APP_WORKER_RESULT_ALREADY_RUNNING:
            APP_LOG(APP_LOG_LEVEL_INFO, "Worker already running");
            break;
        default:
            APP_LOG(APP_LOG_LEVEL_ERROR, "Can't launch worker: %d", (int)res);
            break;
    }
}

static void stop_worker() {
    AppWorkerResult res = app_worker_kill();
    
    switch(res) {
        case APP_WORKER_RESULT_SUCCESS:
            APP_LOG(APP_LOG_LEVEL_INFO, "Worker killed");
            break;
        default:
            APP_LOG(APP_LOG_LEVEL_ERROR, "Can't kill worker: %d", (int)res);
            break;
    }
}

static void up_click_handler(ClickRecognizerRef recognizer, void *ctx) {
    start_worker();
}

static void down_click_handler(ClickRecognizerRef recognizer, void *ctx) {
    stop_worker();
}

static void click_config_provider(void *ctx) {
    window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
    window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void init(void) {
    s_window = window_create();
    window_stack_push(s_window, true);

    // Initialize AppMessage inbox and outbox buffers with a suitable size
    //const int inbox_size = 128;
    //const int outbox_size = 128;
    //app_message_open(inbox_size, outbox_size);
    
    window_set_click_config_provider(s_window, 
                                     click_config_provider);
    
    start_worker();
}

static void deinit(void) {
    window_destroy(s_window);
}

int main( void ) {
    init();
    app_event_loop();
    deinit();
}
