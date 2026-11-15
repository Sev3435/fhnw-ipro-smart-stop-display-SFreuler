#include "net/WifiStore.h"

void WifiStore::load() {
    preferences.begin("wifi", true);
    ssid = preferences.getString("ssid", "");
    pass = preferences.getString("pass", "");
    preferences.end();
}

void WifiStore::save() {
    preferences.begin("wifi", false);
    preferences.putString("ssid", ssid);
    preferences.putString("pass", pass);
    preferences.end();
}

void WifiStore::clear() {
    preferences.begin("wifi", false);
    preferences.clear();
    preferences.end();
    ssid = "";
    pass = "";
}
