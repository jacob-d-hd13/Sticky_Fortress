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

    if (rand() % 10 > 4) // Landscapes choice
    { // Mountains have slightly larger chance that water
        structure.landscape = wrl->world_landscapes[1];
        structure.second_landscape = wrl->world_landscapes[2];
    }
    else
    { // Water
        structure.landscape = wrl->world_landscapes[3];
        structure.second_landscape = wrl->world_landscapes[4];
    }

    coord zone_center_coord = (coord){ rand() % wrl->map_size.x, rand() % wrl->map_size.y}; // Center of structure generation
}

void generate_world_structures(world *wrl, world_params_data_lord *world_params_data)
{
    for (int x = 0; x < world_params_data->structures_number; x++)
    {
        generate_structure(wrl);
    }

    return;
}