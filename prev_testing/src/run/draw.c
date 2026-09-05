#include "draw.h"
#include <raylib.h>

void draw_gui_pannel(gui_pannel guip) // Draw pannel
{
    DrawRectangle(guip.start_coords.x, guip.start_coords.y, guip.canv_size_coords.x, guip.canv_size_coords.y, guip.background_color);

    DrawRectangle(guip.start_coords.x + (guip.canv_size_coords.x / 50), (guip.start_coords.y + guip.canv_size_coords.y) - (guip.canv_size_coords.y / 30), guip.canv_size_coords.x - ((guip.canv_size_coords.x / 50) * 2), 1, (Color){255, 255, 255, 120});
    DrawRectangle(guip.start_coords.x + (guip.canv_size_coords.x / 50), (guip.start_coords.y + guip.canv_size_coords.y) - (guip.canv_size_coords.y / 30) + 2, guip.canv_size_coords.x - ((guip.canv_size_coords.x / 50) * 2), 1, (Color){255, 255, 255, 120});

    DrawRectangle(guip.start_coords.x + (guip.canv_size_coords.x / 50), guip.start_coords.y + (guip.canv_size_coords.y / 30), guip.canv_size_coords.x - ((guip.canv_size_coords.x / 50) * 2), 1, (Color){255, 255, 255, 120});
    DrawRectangle(guip.start_coords.x + (guip.canv_size_coords.x / 50), guip.start_coords.y + (guip.canv_size_coords.y / 30) + 2, guip.canv_size_coords.x - ((guip.canv_size_coords.x / 50) * 2), 1, (Color){255, 255, 255, 120});
}

void draw_gui_text(gui_text guitx) // Draw text
{
    DrawText(guitx.text, guitx.start_coords.x, guitx.start_coords.y, guitx.font_size, guitx.font_color);
}

void draw_dwarf(world *wrl, dwarf dw, prog_params_data_lord *prog_params_data) // Draw dwarf(ASCII)
{
    DrawText(dw.char_value, dw.coords.x * prog_params_data->rect_size.x + 1, dw.coords.y * prog_params_data->rect_size.y - 1, prog_params_data->rect_size.y * 1.3, dw.drawing_color);

    char *dw_hunger_text = malloc(prog_params_data->text_buffer_size);
    sprintf(dw_hunger_text, "%.2f", dw.hunger);
    DrawText(dw_hunger_text, dw.coords.x * prog_params_data->rect_size.x - (sizeof(dw_hunger_text) / sizeof(char)), dw.coords.y * prog_params_data->rect_size.y - 10, 11, YELLOW);

    free(dw_hunger_text);
}

void draw_item(item i, prog_params_data_lord *prog_params_data) // Draw item(ASCII)
{
    DrawText(i.char_value, i.coords.x * prog_params_data->rect_size.x + 1, i.coords.y * prog_params_data->rect_size.y - 1, prog_params_data->rect_size.y * 1.3, YELLOW);

    char *im_num_text = malloc(prog_params_data->text_buffer_size);
    sprintf(im_num_text, "%.0f", i.number);
    DrawText(im_num_text, i.coords.x * prog_params_data->rect_size.x, i.coords.y * prog_params_data->rect_size.y - 10, 10, RED);

    free(im_num_text);
}

void draw_world_graphics(world *wrl, prog_params_data_lord *prog_params_data, world_params_data_lord *world_params_data)
{
    for (int x = 0; x < wrl->map_size.x; x++) // Drawing map
    {
        for (int y = 0; y < wrl->map_size.y; y++)
        {
            if (wrl->map[cell_id_in_map(x, y, wrl->map_size.x)].is_selected == true) // If cell is selected
            {
                DrawRectangle(x * prog_params_data->rect_size.x, y * prog_params_data->rect_size.y, prog_params_data->rect_size.x + 1, prog_params_data->rect_size.y + 1, GOLD);
            }

            DrawRectangle(x * prog_params_data->rect_size.x + 1, y * prog_params_data->rect_size.y + 1, prog_params_data->rect_size.x - 1, prog_params_data->rect_size.y - 1, wrl->map[cell_id_in_map(x, y, wrl->map_size.x)].land_type.draw_color);
        }
    }

    for (int x = 0; x < world_params_data->food_exists; x++) // Draw items
    {
        draw_item(wrl->items[x], prog_params_data);
    }

    for (int x = 0; x < world_params_data->start_dwarves_number; x++) // Draw dwarves
    {
        draw_dwarf(wrl, wrl->dwarves[x], prog_params_data);
    }
}