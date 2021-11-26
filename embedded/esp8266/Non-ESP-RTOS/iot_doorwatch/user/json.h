/*
              UNKNOWN PUBLIC LICENSE

 Copyright (C) 2019 Wira S.T. M.T.

 Currently no license applied because author liv in
 Indonesia, a country which doesn't really concern
 about digital content copyright.

 */

/**
 * @file    json.h
 * @brief   JSON String Builder header.
 *
 * @addtogroup Webserver
 * @{
 */

#ifndef JSON_H
#define JSON_H

/**
 * @brief Global Standard for JSON response length
 */
#define JSON_RESP_LEN   256

/**
 * @brief JSON start string "{"
 * @param[in] String buffer
 */
void json_open(char* strJSON);

/**
 * @brief JSON close string "}"
 * @param[in] String buffer
 */
void json_close(char* strJSON);

/**
 * @brief JSON body string
 * @param[in] String buffer
 * @param[in] String field
 * @param[in] String value
 */
void json_string(char* strJSON, char* field, char* value);

/**
 * @brief JSON body string
 * @param[in] String buffer
 * @param[in] String field
 * @param[in] Boolean value
 */
void json_boolean(char* strJSON, char* field, uint8 value);

/**
 * @brief JSON information
 * @param[out] String JSON contain all informations
 */
void json_infoall(char* strJSON);

#endif // JSON_H
/** @} */
