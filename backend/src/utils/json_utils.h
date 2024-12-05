#ifndef JSON_UTILS_H
#define JSON_UTILS_H

#include <cjson/cJSON.h>

typedef struct
{
    char key[256];
    char value[256];
} KeyValuePair;

int parse_json(const char *json_str, KeyValuePair *pairs, int max_pairs);

#endif // JSON_UTILS_H