#include <generate.h>
#include <time.h>
#include <stdlib.h>

bool structures_overlay_check(world *wrl, landscape_structure structure, coord zone_start_coord, int zone_max_long_x, int zone_max_long_y, int l, int g)
{
    if (wrl->map[cell_id_in_map((zone_start_coord.x + l), (zone_start_coord.y + g), wrl->map_size.x)].land_type.game_id != wrl->world_landscapes[0].game_id)
    { // Overlay check

        return true;
    }

    return false;
}

void generate_structure(world *wrl)
{
    landscape_structure structure;
    coord rm_borders;

    if (rand() % 20 > 11) // Landscapes choice
    {                     // Water
        structure.landscape = wrl->world_landscapes[1];
        structure.second_landscape = wrl->world_landscapes[2];
        rm_borders.x = 2;
        rm_borders.y = 1;
    }
    else
    { // Mountains have slightly larger chance than water
        structure.landscape = wrl->world_landscapes[3];
        structure.second_landscape = wrl->world_landscapes[4];
        rm_borders.x = 5;
        rm_borders.y = 2;
    }

    int pond = 0;
    int pond_step = 30; // If step larger - structure more solid; if less - structure more thin

    coord size_val = (coord){wrl->map_size.x / 20, wrl->map_size.y / 15};
    coord skeleton_x_size = (coord){size_val.x + rand() % size_val.x, size_val.x + rand() % size_val.x}; // Size borders of structure skeleton
    coord skeleton_y_size = (coord){size_val.y + rand() % size_val.y, size_val.y + rand() % size_val.y};

    coord zone_center_coord = (coord){skeleton_x_size.x + rand() % (wrl->map_size.x - ((skeleton_x_size.y) * 2)), skeleton_y_size.x + rand() % (wrl->map_size.y - ((skeleton_y_size.y) * 2))}; // Center of structure generation

    for (int a = zone_center_coord.x - skeleton_x_size.x; a < zone_center_coord.x + skeleton_x_size.y; a++)
    { // Generation by x
        wrl->map[cell_id_in_map(a, zone_center_coord.y, wrl->map_size.x)].land_type = structure.landscape;

        if (a < zone_center_coord.x)
        {
            pond += pond_step;
        }
        else
        {
            pond -= pond_step * 0.75;
        }

        if (rand() % 100 < pond)
        {
            wrl->map[cell_id_in_map(a, zone_center_coord.y - 1 - (rand() % rm_borders.x), wrl->map_size.x)].land_type = structure.landscape;
            wrl->map[cell_id_in_map(a, zone_center_coord.y + 1 + (rand() % rm_borders.x), wrl->map_size.x)].land_type = structure.landscape;
        }

        if (50 + rand() % 100 < pond)
        {
            wrl->map[cell_id_in_map(a, zone_center_coord.y - 1, wrl->map_size.x)].land_type = structure.landscape;
            wrl->map[cell_id_in_map(a, zone_center_coord.y + 1, wrl->map_size.x)].land_type = structure.landscape;

            wrl->map[cell_id_in_map(a, zone_center_coord.y, wrl->map_size.x)].land_type = structure.second_landscape;
        }
    }

    for (int b = zone_center_coord.y - skeleton_y_size.x; b < zone_center_coord.y + skeleton_y_size.y; b++)
    { // Generation by y
        wrl->map[cell_id_in_map(zone_center_coord.x, b, wrl->map_size.x)].land_type = structure.landscape;

        if (b < zone_center_coord.y)
        {
            pond += pond_step;
        }
        else
        {
            pond -= pond_step * 0.75;
        }

        if (rand() % 100 < pond)
        {
            wrl->map[cell_id_in_map(zone_center_coord.x - 1 - (rand() % rm_borders.x), b, wrl->map_size.x)].land_type = structure.landscape;
            wrl->map[cell_id_in_map(zone_center_coord.x + 1 + (rand() % rm_borders.x), b, wrl->map_size.x)].land_type = structure.landscape;
        }

        if (50 + rand() % 100 < pond)
        {
            wrl->map[cell_id_in_map(zone_center_coord.x - 1, b, wrl->map_size.x)].land_type = structure.landscape;
            wrl->map[cell_id_in_map(zone_center_coord.x + 1, b, wrl->map_size.x)].land_type = structure.landscape;

            wrl->map[cell_id_in_map(zone_center_coord.x, b, wrl->map_size.x)].land_type = structure.second_landscape;
        }
    }
}

void generate_world_structures(world *wrl, world_params_data_lord *world_params_data)
{
    for (int x = 0; x < world_params_data->structures_number; x++)
    {
        generate_structure(wrl);
    }

    return;
}