# tiles2bsb
Scrapes a tileserver and outputs the result in BSB format which is typically used for nautical charts navigation software

## Requirements

* libCurl
* ImageMagick / Magick++
* libtiff
* libpng

## Resources

* http://libbsb.sourceforge.net/
* http://wiki.openstreetmap.org/wiki/Openseamap/DE:KAP-Dateien_aus_OSeaMap_erstellen#Benutzung_von_vorgefertigten_Kacheln
* https://github.com/nlohmann/json
* http://opencpn.de/handbuecher/elektronische-seekarten-selbst-erstellen
* http://opencpn.org/ocpn/chart_conversion_linux
* http://www.dacust.com/inlandwaters/imgkap/
* http://www.imagemagick.org/Magick++/

## Tile Server

* http://a.tile.osm.org/{z}/{x}/{y}.png
* http://d2hcl9zx8watk4.cloudfront.net/tile/16/32985/22231?LAYERS=config_1_1_0&TRANSPARENT=FALSE&navtoken=TmF2aW9uaWNzX2ludGVybmFscHVycG9zZV8wMDAwMSt3ZWJhcHAubmF2aW9uaWNzLmNvbQ%3D%3D
