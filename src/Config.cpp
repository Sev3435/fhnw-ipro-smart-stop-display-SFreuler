#include "Config.h"

void Config::load() {
    preferences.begin("cfg", true);
    stopId = preferences.getUInt ("stopId", stopId);
    line = preferences.getString ("line", line);
    nextStop= preferences.getString ("nextStop", nextStop);
    category = preferences.getString ("category", category);
    limit = preferences.getUChar ("limit", limit);
    refreshSec = preferences.getUInt ("refreshSec", refreshSec);
    r = preferences.getChar ("r", r);
    g = preferences.getUChar ("g", g);
    b = preferences.getUChar ("b", b);
    preferences.end();
}

void Config::save() {
    preferences.begin("cfg", false);
    preferences.putUInt ("stopId", stopId);
    preferences.putString ("line", line);
    preferences.putString ("category", category);
    preferences.putString ("nextStop", nextStop);
    preferences.putUChar ("limit", limit);
    preferences.putUInt ("refreshSec", refreshSec);
    preferences.putChar ("r", r);
    preferences.putChar ("g", g);
    preferences.putChar ("b", b);
    preferences.end();
}