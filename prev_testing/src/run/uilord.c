#include "uilord.h"
#include "draw.h"
#include <raylib.h>

ui_lord *initialize_ui_lord(prog_params_data_lord *prog_params_data, int default_font_size)
{
    Color ui_pannels_back = (Color){0, 0, 0, 185};

    gui_pannel mouse_info = {.start_coords.x = 0, .start_coords.y = 0, .canv_size_coords.x = 400, .canv_size_coords.y = 150, .background_color = ui_pannels_back};

    gui_text mouse_coords_text = {.text = (char *)calloc(prog_params_data->text_buffer_size, 1), .start_coords.x = mouse_info.start_coords.x + 15, .start_coords.y = mouse_info.start_coords.y + 25, .font_size = default_font_size, .font_color = RED};

    gui_pannel selected_cells_info = {.start_coords.y = 0, .canv_size_coords.x = 300, .canv_size_coords.y = 210, .background_color = ui_pannels_back};
    selected_cells_info.start_coords.x = prog_params_data->window_size.x - selected_cells_info.canv_size_coords.x;

    gui_text selected_cells_text = {.text = (char *)calloc(prog_params_data->text_buffer_size, 1), .start_coords.x = selected_cells_info.start_coords.x + 15, .start_coords.y = selected_cells_info.start_coords.y + 25, .font_size = default_font_size, .font_color = GOLD};
    gui_text world_save_text = {.text = (char *)calloc(prog_params_data->text_buffer_size, 1), .start_coords.x = selected_cells_info.start_coords.x + 15, .start_coords.y = selected_cells_text.start_coords.y + 140, .font_size = default_font_size - 5, .font_color = RED};

    gui_pannel dwarves_info = {.start_coords.x = 0, .canv_size_coords.x = 350, .canv_size_coords.y = 700, .background_color = ui_pannels_back};
    dwarves_info.start_coords.y = prog_params_data->window_size.y - dwarves_info.canv_size_coords.y;

    gui_text dwarves_number_text = {.text = (char *)calloc(prog_params_data->text_buffer_size, 1), .start_coords.x = dwarves_info.start_coords.x + 5, .start_coords.y = dwarves_info.start_coords.y + 25, .font_size = default_font_size, .font_color = GREEN};
    gui_text dwarves_selected_text = {.text = (char *)calloc(prog_params_data->text_buffer_size, 1), .start_coords.x = dwarves_info.start_coords.x + 5, .start_coords.y = dwarves_info.start_coords.y + 60, .font_size = default_font_size, .font_color = GREEN};

    gui_pannel frame_info = {.start_coords.x = prog_params_data->window_size.x - 200, .start_coords.y = prog_params_data->window_size.y - 150, .canv_size_coords.x = 200, .canv_size_coords.y = 150, .background_color = ui_pannels_back};

    gui_text frame_info_text = {.text = (char *)calloc(prog_params_data->text_buffer_size, 1), .start_coords.x = frame_info.start_coords.x + 5, .start_coords.y = frame_info.start_coords.y + 25, .font_size = default_font_size - 5, .font_color = RED};

    gui_text dwarves_selected_list_text = {.text = (char *)calloc(prog_params_data->text_buffer_size, 10), .start_coords.x = dwarves_selected_text.start_coords.x, .start_coords.y = dwarves_selected_text.start_coords.y + 40, .font_size = default_font_size - 13, .font_color = WHITE};

    gui_button selecting_mode_switch_button = {.start_coords.x = 200, .start_coords.y = 25, .canv_size_coords.x = 120, .canv_size_coords.y = 20, .background_color = BLUE, .text = (char *)calloc(prog_params_data->text_buffer_size, 1), .font_color = WHITE, .font_size = default_font_size - 5, .is_downed = false};
    gui_button pause_switch_button = {.start_coords.x = frame_info.start_coords.x + 5, .start_coords.y = frame_info.start_coords.y + 75, .canv_size_coords.x = 120, .canv_size_coords.y = 20, .background_color = BLUE, .text = (char *)calloc(prog_params_data->text_buffer_size, 1), .font_color = WHITE, .font_size = default_font_size - 5, .is_downed = false};
    gui_button dwarves_selected_list_switch_button = {.start_coords.x = dwarves_selected_text.start_coords.x, .start_coords.y = dwarves_selected_text.start_coords.y + 5, .canv_size_coords.x = 12, .canv_size_coords.y = 16, .background_color = BLUE, .text = (char *)calloc(prog_params_data->text_buffer_size, 1), .font_color = WHITE, .font_size = default_font_size - 4, .is_downed = false};

    ui_lord *uil = malloc(sizeof(ui_lord));
    uil->all_gui_pannels = malloc(sizeof(gui_pannel) * 10);
    uil->all_gui_text = malloc(sizeof(gui_text) * 10);
    uil->all_gui_buttons = malloc(sizeof(gui_button) * 10);

    uil->all_gui_pannels[0] = mouse_info;
    uil->all_gui_pannels[1] = selected_cells_info;
    uil->all_gui_pannels[2] = dwarves_info;
    uil->all_gui_pannels[3] = frame_info;

    uil->all_gui_text[0] = mouse_coords_text;
    uil->all_gui_text[1] = selected_cells_text;
    uil->all_gui_text[2] = dwarves_number_text;
    uil->all_gui_text[3] = frame_info_text;
    uil->all_gui_text[4] = dwarves_selected_text;
    uil->all_gui_text[5] = world_save_text;
    uil->all_gui_text[7] = dwarves_selected_list_text;

    uil->all_gui_buttons[0] = selecting_mode_switch_button;
    uil->all_gui_buttons[1] = pause_switch_button;
    uil->all_gui_buttons[2] = dwarves_selected_list_switch_button;

    return uil;
}

void delete_ui_lord(ui_lord *uil)
{
    free(uil->all_gui_pannels);
    free(uil->all_gui_text);
    free(uil);
}

void update_ui_text(world *wrl, ui_lord *uil, world_params_data_lord *world_params_data, prog_params_data_lord *prog_params_data)
{
    sprintf(uil->all_gui_text[7].text, "");

    sprintf(uil->all_gui_text[0].text, "X: %d Y: %d\n\nLmb to start square selecting,\nrmb to deselect cell", prog_params_data->mouse_position.x, prog_params_data->mouse_position.y);

    sprintf(uil->all_gui_text[1].text, "Selected: \nbasic landscape: %d; \nwater: %d; \nmountains: %d; \nrocks: %d; deep water: %d",
            world_params_data->cells_selected[0], world_params_data->cells_selected[1], world_params_data->cells_selected[2], world_params_data->cells_selected[3], world_params_data->cells_selected[4]);
    sprintf(uil->all_gui_text[5].text, "You can find world map \nin prev_testing/worlds/");

    sprintf(uil->all_gui_text[2].text, "Dwarves alive: %d / %d", world_params_data->dwarves_alive, world_params_data->start_dwarves_number);
    sprintf(uil->all_gui_text[4].text, "      selected: %d", world_params_data->dwarves_selected);

    if (!uil->all_gui_buttons[2].is_downed)
    {
        for (int x = 0; x < world_params_data->start_dwarves_number; x++)
        {
            if (wrl->dwarves[x].is_alive == true && wrl->map[cell_id_in_map(wrl->dwarves[x].coords.x, wrl->dwarves[x].coords.y, wrl->map_size.x)].is_selected == true)
            {
                sprintf(uil->all_gui_text[7].text, "%s| #%s %s -- %.1f/%.1f", uil->all_gui_text[7].text, wrl->dwarves[x].game_id, wrl->dwarves[x].game_name, wrl->dwarves[x].hunger, wrl->dwarves[x].die_level_hunger);
                if (wrl->dwarves[x].moving_state == UNTARGET_MOVING)
                {
                    sprintf(uil->all_gui_text[7].text, "%s    [aimless movement]\n", uil->all_gui_text[7].text);
                }
                else if (wrl->dwarves[x].moving_state == TARGETING)
                {
                    sprintf(uil->all_gui_text[7].text, "%s    [movement to target]\n", uil->all_gui_text[7].text);
                }
            }
        }
    }

    sprintf(uil->all_gui_text[3].text, "Frame (from 1 to 60) :\n %d\n\n\nYou can find FPS\n in log files", prog_params_data->timer);
}

void update_ui_buttons(ui_lord *uil, prog_params_data_lord *prog_params_data)
{
    if (uil->all_gui_buttons[0].is_downed)
    {
        prog_params_data->is_selecting_mode_on = true;
        sprintf(uil->all_gui_buttons[0].text, "Selecting on\n");
    }
    else
    {
        prog_params_data->is_selecting_mode_on = false;
        sprintf(uil->all_gui_buttons[0].text, "Selecting off\n");
    }

    if (uil->all_gui_buttons[1].is_downed)
    {
        prog_params_data->is_paused = true;
        sprintf(uil->all_gui_buttons[1].text, "Pause on\n");
    }
    else
    {
        prog_params_data->is_paused = false;
        sprintf(uil->all_gui_buttons[1].text, "Pause off\n");
    }

    if (uil->all_gui_buttons[2].is_downed)
    {
        sprintf(uil->all_gui_buttons[2].text, "-\n");
    }
    else
    {
        sprintf(uil->all_gui_buttons[2].text, "+\n");
    }
}

void update_ui_lord(ui_lord *uil, world_params_data_lord *world_params_data, prog_params_data_lord *prog_params_data, world *wrl)
{
    update_ui_text(wrl, uil, world_params_data, prog_params_data);
    update_ui_buttons(uil, prog_params_data);
}

void draw_ui_lord(ui_lord *uil)
{
    for (int x = 0; x < 4; x++)
    {
        draw_gui_pannel(uil->all_gui_pannels[x]);
    }

    for (int y = 0; y < 8; y++)
    {
        draw_gui_text(uil->all_gui_text[y]);
    }

    for (int z = 0; z < 3; z++)
    {
        draw_gui_button(uil->all_gui_buttons[z]);
    }
}