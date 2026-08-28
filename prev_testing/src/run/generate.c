#include <generate.h>
#include <time.h>
#include <stdlib.h>

bool structures_overlay_check(world *wrl, landscape_structure structure, coord zone_start_coord, int zone_max_long_x, int zone_max_long_y, int l, int g) {
    if (wrl->map[cell_id_in_map((zone_start_coord.x + l), (zone_start_coord.y + g), wrl->map_size.x)].land_type.game_id != wrl->world_landscapes[0].game_id) { // Overlay check

        return true;
    }

    return false;
}

void generate_structure(world *wrl)
{
    // landscape_structure structure;

    // float pond = rand() % 100 + rand() % 15; // Randomization parameters
    // float pond_increment_step = 1 + rand () % 3;
    // int pond_border = 200 + rand() % 100;

    // if (rand() % 10 > 5) // Landscapes choice
    // {
    //     structure.landscape = wrl->world_landscapes[1];
    //     structure.second_landscape = wrl->world_landscapes[2];
    // }
    // else
    // {
    //     structure.landscape = wrl->world_landscapes[3];
    //     structure.second_landscape = wrl->world_landscapes[4];
    // }

    // coord zone_start_coord = (coord){rand() % wrl->map_size.x, rand() % wrl->map_size.y};

    // int zone_max_long_x = 25 + (wrl->map_size.x / (1 + rand() % 25)); // Size of structure
    // int zone_max_long_y = 25 + (wrl->map_size.y / (1 + rand() % 25));

    // printf("SIZE: %d, %d\n", zone_max_long_x, zone_max_long_y);

    // int j = 0;

    // while ((zone_start_coord.x + zone_max_long_x) > wrl->map_size.x && (zone_start_coord.y + zone_max_long_y) > wrl->map_size.y) // Coords of structure
    // {
    //     zone_start_coord.x = abs((wrl->map_size.x - zone_max_long_x) - (1 + rand() % 10));
    //     zone_start_coord.y = abs((wrl->map_size.y - zone_max_long_y) - (1 + rand() % 10));
    //     printf("x:%d y:%d\n", zone_start_coord.x, zone_start_coord.y);
    // }

    // for (int l = 0; l < zone_max_long_x; l++) // Generation
    // {
    //     for (int g = 0; g < zone_max_long_y; g++)
    //     {
    //         if (!(structure.landscape.game_id == LAND_MOUNTAINS)) // Water
    //         {
    //             if (structures_overlay_check(wrl, structure, zone_start_coord, zone_max_long_x, zone_max_long_y, l, g)) {
    //                 return;
    //             }

    //             if ((zone_max_long_y/2) + (rand() % pond_border)/2 >= pond) {
    //                 wrl->map[cell_id_in_map((zone_start_coord.x + l), (zone_start_coord.y + g), wrl->map_size.x)].land_type = structure.second_landscape;
    //             } else {
    //                 wrl->map[cell_id_in_map((zone_start_coord.x + l), (zone_start_coord.y + g), wrl->map_size.x)].land_type = structure.landscape;
    //             } // So ugly generation
                
    //             j++;
    //         }
    //         else // Mountains
    //         {
    //             if (((rand() % pond_border) - 20) > pond)
    //             {
    //                 if (structures_overlay_check(wrl, structure, zone_start_coord, zone_max_long_x, zone_max_long_y, l, g)) {
    //                     return;
    //                 }

    //                 if (((rand() % pond_border + pond/2))/2 >= pond) {
    //                     wrl->map[cell_id_in_map((zone_start_coord.x + l), (zone_start_coord.y + g), wrl->map_size.x)].land_type = structure.second_landscape;
    //                 } else {
    //                     wrl->map[cell_id_in_map((zone_start_coord.x + l), (zone_start_coord.y + g), wrl->map_size.x)].land_type = structure.landscape;
    //                 }

    //                 j++;
    //             }
    //         }

    //         pond += pond_increment_step;
    //     }
    // }

    landscape_structure structure;
    coord rm_borders;

    if (rand() % 20 > 11) // Landscapes choice
    { // Water
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
    int pond_step = 22; // If step larger - structure more solid; if less - structure more thin

    coord size_val = (coord) {wrl->map_size.x / 20, wrl->map_size.y / 15};
    coord skeleton_x_size = (coord) {size_val.x + rand() % size_val.x, size_val.x + rand() % size_val.x}; // Size borders of structure skeleton
    coord skeleton_y_size = (coord) {size_val.y + rand() % size_val.y, size_val.y + rand() % size_val.y};

    coord zone_center_coord = (coord) {skeleton_x_size.x + rand() % (wrl->map_size.x - ((skeleton_x_size.y)*2)), skeleton_y_size.x + rand() % (wrl->map_size.y - ((skeleton_y_size.y)*2))}; // Center of structure generation

    for (int a = zone_center_coord.x - skeleton_x_size.x; a < zone_center_coord.x + skeleton_x_size.y; a ++) { // Generation by x
        wrl->map[cell_id_in_map(a, zone_center_coord.y, wrl->map_size.x)].land_type = structure.landscape;

        if (a < zone_center_coord.x) {
            pond += pond_step;
        } else {
            pond -= pond_step*0.75;
        }

        if (rand() % 100 < pond) {
            wrl->map[cell_id_in_map(a, zone_center_coord.y - 1 - (rand() % rm_borders.x), wrl->map_size.x)].land_type = structure.landscape;
            wrl->map[cell_id_in_map(a, zone_center_coord.y + 1 + (rand() % rm_borders.x), wrl->map_size.x)].land_type = structure.landscape;
        }

        if (50 + rand() % 100 < pond) {
            wrl->map[cell_id_in_map(a, zone_center_coord.y - 1 - (rand() % rm_borders.y), wrl->map_size.x)].land_type = structure.landscape;
            wrl->map[cell_id_in_map(a, zone_center_coord.y + 1 + (rand() % rm_borders.y), wrl->map_size.x)].land_type = structure.landscape;

            wrl->map[cell_id_in_map(a, zone_center_coord.y, wrl->map_size.x)].land_type = structure.second_landscape;
        }
    }

    for (int b = zone_center_coord.y - skeleton_y_size.x; b < zone_center_coord.y + skeleton_y_size.y; b ++) { // Generation by y
        wrl->map[cell_id_in_map(zone_center_coord.x, b, wrl->map_size.x)].land_type = structure.landscape;

        if (b < zone_center_coord.y) {
            pond += pond_step;
        } else {
            pond -= pond_step*0.75;
        }

        if (rand() % 100 < pond) {
            wrl->map[cell_id_in_map(zone_center_coord.x - 1 - (rand() % rm_borders.x), b, wrl->map_size.x)].land_type = structure.landscape;
            wrl->map[cell_id_in_map(zone_center_coord.x + 1 + (rand() % rm_borders.x), b, wrl->map_size.x)].land_type = structure.landscape;
        }

        if (60 + rand() % 100 < pond) {
            wrl->map[cell_id_in_map(zone_center_coord.x - 1 - (rand() % rm_borders.y), b, wrl->map_size.x)].land_type = structure.landscape;
            wrl->map[cell_id_in_map(zone_center_coord.x + 1 + (rand() % rm_borders.x), b, wrl->map_size.x)].land_type = structure.landscape;

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