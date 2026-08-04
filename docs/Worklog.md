
Privates Worklog

Struktur

Datum

 - tasks done

 - Herausforderungen

 - Design entscheidungen / implementierung

 - Was hat funktioniert / was nicht?

 -

---

12.01

Habe am Einfuehfungstag teilgenommen. Keine grossen Projektfortschritte.
Von Thomas habe ich einen Scetch bekommen, wie die Architektur aussehen
koennte in den verschiedenen Phasen des Projekts.

Projektziele konnte ich schon hauptsaechlich von meinem Formular, welches ich
eingereicht habe, uebernehmen.

---

13.01

Die definierung des Gantt-Charts.
Das Setup der Dokumente war eher minimal. Ich habe alles in einen Ordner in
mein Persoenliches OneDrive gelegt und die Dokumente darin erstellt, welche
ich vorraussichtlich brauchen werden. 


Herausforderung: viele Tasks vordefinieren, braucht wahrscheinlich noch
Anpassung waehrend das Projekt durchgefuert wird

Design entscheidung: Habe mich fuer excel entschieden, da es fuer mich am
einfachsten ist, und es schon vordefinierte Template gibt.

---

13.01
Habe mir den Vorschlag von Thomas angeschaut und darauf aufgebaut. Habe es
auch besser visualisiert durch Draw.io und Titel in technischer Dokumentation erfasst.

---

14.01
Habe nochmals das draw.io überarbeitet

---

26.02
Wieso von arduino IDE zu CLion + PlatformIO? 
-> bessere projektstruktur, versioncontrol mit GIT direkt aus der IDE

wie? https://esp32s3.com/getting-started.html#:~:text=UM%20FeatherS3.-,PlatformIO,-PlatformIO%20support%20is

---

02.08
WLAN-Verbindung: Entscheidung für ein nicht blockierendes Design. „WifiManager_update()“ wird von „loop()“ aufgerufen und überprüft bei jedem Durchlauf „WiFi.status()“; 
Wiederverbindungsversuche laufen mit einem 5-Sekunden-Timer („millis()“). 
Grund: Das Display muss auch bei ausgefallenem WLAN weiter aktualisiert werden, und das Gerät muss sich bei Routerausfällen zur Laufzeit ohne Neustart erholen können (eine blockierende Verbindung in „setup()“ stellt nur einmal eine Verbindung her).
Die Anmeldedaten wurden in die Datei „include/secrets.h“ verschoben, die nun in die .gitignore-Datei aufgenommen wurde, zusammen mit einer festgeschriebenen Beispielvorlage.

Implementierung der WLAN-Verbindung
**WifiManager_update()** wird von **loop()** aufgerufen und prüft bei jedem Durchlauf **WiFi.status()**. Durchläufe sind mit Methode **millis()** definiert.
Grund: Das Display soll bei ausgefallenem WLAN weiter akutalisiert weden und das Gerät muss sich bei Routerausfällen ohne neustart erholen können.
Die Anmeldedaten werden in **include/secrets.h** definiert. Vorlage ist unter **include/secrets.example.h** zu finden.

---

04.08
WLAN fertig (1 Stunde Standby + 2 Wiederverbindungen auf DevKitv1). Protokollierung in die Core-Log-Makros mit Dev-/Release-Umgebungen verschoben. Wiederholungsversuch als 30-Sekunden-„reconnect()“ festgelegt.

---