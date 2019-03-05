### DownloadStation Helper

The application is designed to simplify the process of adding download tasks to DownloadStation on your Synology DiskStation.
DSM 6.0 or higher is required on the DiskStation.

Advantages in comparison with extensions for browsers:
 - no need to keep always running (with a browser), does not waste memory
 - does not slow down the browser

The video shows the work with DS Helper: https://www.youtube.com/watch?v=oYu1oPmg7lM&list=PLVKAFhKhBAu6ELYvMGGZha2qLaP7VrJ7y&t=1s&index=1

Supported operating systems:  Microsoft Windows XP and later versions.
The application can be installed on Linux using PlayOnLinux (you must have Internet Explorer 8 installed on the same virtual disk).

The project uses the JsonCpp library:
https://github.com/open-source-parsers/jsoncpp

-----

##### How to configure file- and magnet-links associations in Linux Mint 18 XFCE:
1. Add these strings to the section [Default Applications] of the file ~/.local/share/applications/mimeapps.list
```
application/x-bittorrent=DownloadStationHelper.desktop
x-scheme-handler/magnet=DownloadStationHelper.desktop
```
2. In the directory ~/.local/share/applications create a file named "DownloadStationHelper.desktop" with the following content:
```
[Desktop Entry]
Name=DownloadStation Helper
Encoding=UTF-8
Comment=PlayOnLinux
#Exec=/usr/share/playonlinux/playonlinux --run "DS Helper" %u
#or
Exec=env WINEPREFIX="/home/USER_NAME/.PlayOnLinux/wineprefix/InternetExplorer8" /home/USER_NAME/.PlayOnLinux/wine/linux-x86/1.7.22/bin/wine start /Unix /home/USER_NAME/.PlayOnLinux/wineprefix/InternetExplorer8/dosdevices/c:/Program\\ Files/DownloadStation\\ Helper/DS\\ Helper.exe %u
Terminal=false
Type=Application
Categories=Network;P2P;
#Icon="/home/USER_NAME/.PlayOnLinux/icones/full_size/DS Helper"
#or
Icon=/home/USER_NAME/.local/share/icons/hicolor/256x256/apps/E815_DS Helper.0.png
Path=/home/USER_NAME/.PlayOnLinux/wineprefix/InternetExplorer8/drive_c/Program Files/DownloadStation Helper
```
(the name of the icon (E815...) may be different - check in the specified directory; USER_NAME - your username; InternetExplorer8 - prefix (a virtual disk, with IE8 and DS Helper))

##### Also, on linux it is convenient to use this bash script to manage Download Station tasks from the command line: https://github.com/xaozai/ds-cli
