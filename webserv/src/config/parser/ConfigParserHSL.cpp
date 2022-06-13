/**
 * @file ConfigParserHSL.cpp
 * @author Andrei Baidin
 * @brief Routines for parsing configuration directives
 * in http, server and location scopes
 * @version 1.0
 * @date 2022-06-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "ConfigParser.h"

#include <cstring>
#include <cstdlib>
#include <cerrno>

bool ConfigParser::hsl_directives_(const token& t, Config& conf)
{
    if (!std::strncmp(t.str, ROOT, t.size)) {
        return root_(conf);
    }

    if (!std::strncmp(t.str, ERROR_PAGE, t.size)) {
        return error_page_(conf);
    }

    if (!std::strncmp(t.str, CLIENT_MAX_BODY_SIZE, t.size)) {
        return client_max_body_size_(conf);
    }

    if (!std::strncmp(t.str, CLIENT_BODY_TEMP_PATH, t.size)) {
        return client_body_temp_path_(conf);
    }

    if (!std::strncmp(t.str, AUTOINDEX, t.size)) {
        return autoindex_(conf);
    }

    if (!std::strncmp(t.str, INDEX, t.size)) {
        return index_(conf);
    }

    return (false);
}

bool ConfigParser::root_(Config& conf)
{
    token t = ts_.gettoken();

    if ((t.type != REGULAR_TOKEN && t.type != NAME_TOKEN) ||
        ts_.gettoken().type != SEMICOLON ||
        is_field_set(conf.fields_set, E_ROOT))
    {
        return (false);
    }

    conf.root.assign(t.str, t.size);
    conf.fields_set = set_field(conf.fields_set, E_ROOT);
    return (true);
}

// 300 .. 599
bool ConfigParser::error_page_(Config& conf)
{
    token t = ts_.gettoken();

    if (is_field_set(conf.fields_set, E_ERROR_PAGE)) {
        return (false);
    }

    while (t.type == NUMBER) {
        int code = strtocode(t.str);

        if (code == -1) {
            return (false);
        }

        conf.error_page.codes.insert(code);
        t = ts_.gettoken();
    }

    if (t.type != REGULAR_TOKEN) {
        return (false);
    }

    conf.error_page.uri.assign(t.str, t.size);
    conf.fields_set = set_field(conf.fields_set, E_ERROR_PAGE);
    return (ts_.gettoken().type == SEMICOLON);
}

bool ConfigParser::client_max_body_size_(Config& conf)
{
    token t = ts_.gettoken();

    if (t.type != NUMBER ||
        ts_.gettoken().type != SEMICOLON ||
        is_field_set(conf.fields_set, E_CLIENT_MAX_BODY_SIZE))
    {
        return (false);
    }

    conf.client_max_body_size = std::strtol(t.str, NULL, 10);
    conf.fields_set = set_field(conf.fields_set, E_CLIENT_MAX_BODY_SIZE);
    return (errno != ERANGE);
}

bool ConfigParser::client_body_temp_path_(Config& conf)
{
    token t = ts_.gettoken();

    if ((t.type != REGULAR_TOKEN && t.type != NAME_TOKEN) ||
        ts_.gettoken().type != SEMICOLON ||
        is_field_set(conf.fields_set, E_CLIENT_BODY_TEMP_PATH))
    {
        return (false);
    }

    conf.client_body_temp_path.assign(t.str, t.size);
    conf.fields_set = set_field(conf.fields_set, E_CLIENT_BODY_TEMP_PATH);
    return (true);
}

bool ConfigParser::autoindex_(Config& conf)
{
    token t = ts_.gettoken();

    if (t.type != NAME_TOKEN ||
        ts_.gettoken().type != SEMICOLON ||
        is_field_set(conf.fields_set, E_AUTOINDEX))
    {
        return (false);
    }

    if (!std::strncmp(t.str, "on", t.size)) {
        conf.autoindex = true;
    }
    else if (!std::strncmp(t.str, "off", t.size)) {
        conf.autoindex = false;
    }
    else {
        return (false);
    }

    conf.fields_set = set_field(conf.fields_set, E_AUTOINDEX);
    return (true);
}

bool ConfigParser::index_(Config& conf)
{
    token t = ts_.gettoken();

    if (is_field_set(conf.fields_set, E_AUTOINDEX)) {
        return (false);
    }

    conf.index.clear();

    while (t.type == REGULAR_TOKEN || t.type == NAME_TOKEN) {
        conf.index.push_back(std::string(t.str, t.size));
        t = ts_.gettoken();
    }

    conf.fields_set = set_field(conf.fields_set, E_INDEX);
    return (t.type == SEMICOLON);
}

