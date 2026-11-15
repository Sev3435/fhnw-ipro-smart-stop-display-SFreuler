#include "transport/TransportApi.h"
#include <HTTPClient.h>

bool TransportApi::fetch(String& body) const {
    String url = "http://transport.opendata.ch/v1/stationboard?id=" + String(config->stopId) +
                 "&limit=" + String(config->limit) +
                 "&fields[]=stationboard/stop/departure"
                 "&fields[]=stationboard/number"
                 "&fields[]=stationboard/to"
                 "&fields[]=stationboard/passList/station/name"
                 "&fields[]=stationboard/category";
    HTTPClient http;
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode != 200) {
        log_w("http %d", httpCode);
        http.end();
        return false;
    }
    body = http.getString();
    log_i("http 200, body %d bytes", body.length());
    http.end();
    return true;
}
