#pragma once

//Start TLS error codes
const int SSL_CLIENT_STARTTLS_INITSSLCTX_ERROR = -51;
const int SSL_CLIENT_STARTTLS_BIONEWSSLCONNECT_ERROR = -52;
const int SSL_CLIENT_STARTTLS_WIN_CERTOPENSYSTEMSTORE_ERROR = -53;
const int SSL_CLIENT_STARTTLS_CTX_SET_DEFAULT_VERIFY_PATHS_ERROR = -54;
const int SSL_CLIENT_STARTTLS_BIO_CONNECT_ERROR = -55;
const int SSL_CLIENT_STARTTLS_BIO_HANDSHAKE_ERROR = -56;
const int SSL_CLIENT_STARTTLS_GET_CERTIFICATE_ERROR = -57;
const int SSL_CLIENT_STARTTLS_VERIFY_RESULT_ERROR = -58;

//Init Session error codes
const int SSL_CLIENT_INITSECURECLIENT_ERROR = -59;
const int SSL_CLIENT_INITSECURECLIENT_TIMEOUT = -60;