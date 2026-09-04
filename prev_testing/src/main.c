#include <stdio.h>
#include <raylib.h>
#include <stdlib.h> // For rand() func
#include <time.h>   // For timestamp and rand() initialize

#include "dwarves.h"
#include "logging.h"
#include "uilord.h"
#include "world.h"
#include "datalord.h"
#include "draw.h"
#include "updatelord.h"

#define VERSION "0.0.2"

#define TARGET_FPS 60

#define LOGS_BARRIERS "---------------------------------------------------------------\n"

int main()
{
    SetTraceLogLevel(LOG_NONE); // For delete all raylib's sys logs

    // Creating data lords
    prog_params_data_lord *prog_params_data = define_prog_params_data_lord();
    world_params_data_lord *world_params_data = define_world_params_data_lord();
    draw_data_lord *draw_data = define_draw_data_lord();
    log_data_lord*log_data = define_log_data_lord();

    srand(time(NULL));

    // Initializing log file
    char *source_log_file_path = malloc(prog_params_data->text_buffer_size);
    initialize_log_file(source_log_file_path, log_data);

    raw_log_to_file(log_data, LOGS_BARRIERS);
    log_to_file(log_data, "PROGRAM STARTED\n");
    raw_log_to_file(log_data, LOGS_BARRIERS);

    coord map_size = {prog_params_data->window_size.x / prog_params_data->rect_size.x, prog_params_data->window_size.y / prog_params_data->rect_size.y};

    // Log start info
    char *init_log_info = malloc(prog_params_data->text_buffer_size);
    sprintf(init_log_info, "%s %d,%d\n\n", "Defined window size", prog_params_data->window_size.x, prog_params_data->window_size.y);
    log_to_file(log_data, init_log_info);

    sprintf(init_log_info, "%s %d,%d\n\n", "Defined cell size", prog_params_data->rect_size.x, prog_params_data->rect_size.y);
    log_to_file(log_data, init_log_info);
    
    sprintf(init_log_info, "Defined map size %d, %d\n", map_size.x, map_size.y);
    log_to_file(log_data, init_log_info);

    raw_log_to_file(log_data, LOGS_BARRIERS);

    // Creating world
    world *wrl = initialize_world(world_params_data, prog_params_data, LOGS_BARRIERS, map_size, log_data, draw_data);

    // Initializing window
    char *window_name = malloc(prog_params_data->text_buffer_size);
    sprintf(window_name, "Sticky Fortress %s", VERSION);

    InitWindow(prog_params_data->window_size.x, prog_params_data->window_size.y, window_name);
    SetTargetFPS(TARGET_FPS);

    SetExitKey(KEY_Q); // If active, window willn't close on ESC button

    Image window_icon = LoadImage("./images/window_icon.png"); // Loading icon
    ImageFormat(&window_icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8); // Formatting icon
    ImageColorReplace(&window_icon, WHITE, BLANK);
    SetWindowIcon(window_icon);

    log_to_file(log_data, "INITIALIZED WINDOW\n");

    // Initialize main UI
    ui_lord *ui_central = initialize_ui_lord(prog_params_data, draw_data->default_font_size);

    raw_log_to_file(log_data,  LOGS_BARRIERS);
    log_to_file(log_data, "STARTED APP\n");
    raw_log_to_file(log_data,  LOGS_BARRIERS);

    while (!WindowShouldClose())
    {
        update_game_running_params(prog_params_data, log_data);

        BeginDrawing();

        ClearBackground(BLACK); // Clear background

        update_game_stats(wrl, world_params_data);
        update_game_objects(wrl, prog_params_data, world_params_data, log_data);

        draw_world_graphics(wrl, prog_params_data, world_params_data);

        update_ui_lord(ui_central, world_params_data, prog_params_data); // Update main UI 
        draw_ui_lord(ui_central); // Draw main UI

        update_selection(wrl, world_params_data, prog_params_data);

        EndDrawing();
    }

    CloseWindow();

    raw_log_to_file(log_data, LOGS_BARRIERS);
    log_to_file(log_data, "APP CORRECTLY CLOSED\n");
    raw_log_to_file(log_data, LOGS_BARRIERS);

    delete_world(wrl, world_params_data, log_data);
    delete_ui_lord(ui_central);

    free(window_name);

    free(source_log_file_path);
    fclose(log_data->source_log_file);

    undefine_all_data_lords(prog_params_data, world_params_data, draw_data, log_data);
}