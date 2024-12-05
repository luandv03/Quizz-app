#include "json_utils.h"
#include <stdio.h>
#include <string.h>

int parse_json(const char *json_str, KeyValuePair *pairs, int max_pairs)
{
    cJSON *json = cJSON_Parse(json_str);
    if (json == NULL)
    {
        fprintf(stderr, "Error parsing JSON\n");
        return 0;
    }

    int pair_count = 0;
    cJSON *item = NULL;
    cJSON_ArrayForEach(item, json)
    {
        if (pair_count >= max_pairs)
        {
            break;
        }

        if (cJSON_IsString(item) && (item->valuestring != NULL))
        {
            strncpy(pairs[pair_count].key, item->string, sizeof(pairs[pair_count].key) - 1);
            strncpy(pairs[pair_count].value, item->valuestring, sizeof(pairs[pair_count].value) - 1);
            pair_count++;
        }
        else if (cJSON_IsNumber(item))
        {
            strncpy(pairs[pair_count].key, item->string, sizeof(pairs[pair_count].key) - 1);
            snprintf(pairs[pair_count].value, sizeof(pairs[pair_count].value), "%lf", item->valuedouble);
            pair_count++;
        }
    }

    cJSON_Delete(json);
    return pair_count;
}