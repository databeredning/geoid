# geoid
Bilinear interpolation of geoid height using SWEN08_RH2000

![alt text](https://www.lantmateriet.se/globalassets/kartor-och-geografisk-information/gps-och-matning/referenssystem/geoiden/bilder/geoidprofil_eng.gif)

To convert the height above the ellipsoid (h) to the height above sea level (H) we need the separation between these two surfaces. This is the geoid height (N). The geoid height is calculated from the geoid model SWEN08_RH2000. 

H = h - N

The program takes an input file that consists of SWEREF 99 positions in lat / lon format ( DD.dd DD.dd ) and outputs the geoid height for each position.

57.546846969    12.168404628  
57.546833055    12.168402364  
57.546765665    12.168405298  
....  

57.5468470 12.1684046 35.8186  
57.5468331 12.1684024 35.8186  
57.5467657 12.1684053 35.8187  
....  

