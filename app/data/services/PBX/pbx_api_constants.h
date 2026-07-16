#ifndef PBX_API_CONSTANTS_H
#define PBX_API_CONSTANTS_H

#include <QString>

namespace PbxApi {
const QString TOKEN_ENDPOINT = "/admin/api/api/token";
const QString GQL_ENDPOINT = "/admin/api/api/gql";

const QString AUTHORIZATION_HEADER = "Authorization";
const QString CONTENT_TYPE_FORM = "application/x-www-form-urlencoded";
const QString CONTENT_TYPE_JSON = "application/json";

const QString AUTH_BASIC_PREFIX = "Basic ";
const QString AUTH_BEARER_PREFIX = "Bearer ";

const QString TOKEN_GRANT_TYPE = "grant_type=client_credentials&scope=gql:core:read";

const QString GQL_FETCH_EXTENSIONS_QUERY = "query { fetchAllExtensions { status totalCount extension { extensionId } } }";

namespace JsonKeys {
const QString QUERY = "query";
const QString DATA = "data";
const QString FETCH_ALL_EXTENSIONS = "fetchAllExtensions";
const QString EXTENSION = "extension";
const QString EXTENSION_ID = "extensionId";
const QString ACCESS_TOKEN = "access_token";
const QString EXPIRES_IN = "expires_in";
}
}

#endif // PBX_API_CONSTANTS_H
