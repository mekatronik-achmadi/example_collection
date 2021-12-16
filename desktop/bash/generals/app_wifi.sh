#!/bin/bash
#script to run some utility on terminal

menu=1
choice=0

while [ $menu -eq 1 ];do
  echo "
  
  please select menu:
  
  1.	 quit 
  2.	 network status
  3.	 network saved list
  4.	 wlan0 connect
  5.	 wlan0 connect with password
  6.	 wlan0 saved delete
  7.	 network manager (GUI)
  8.	 clock
  9.	 digital clock (GUI)
  10.	 battery
  11.	 battery (GUI)
  "
  read -p "Your selection? [1-13]> " choice
  
  if [ $choice -eq 1 ]; then
    menu=0
    
  elif [ $choice -eq 2 ]; then
    nm-tool
    
  elif [ $choice -eq 3 ]; then
    nmcli con list
    
  elif [ $choice -eq 4 ]; then
    read -p "SSID Name?> " ssidname
    ssidname="$(echo -e \'$ssidname\')"
    nmcli dev wifi connect $ssidname iface wlan0
    
  elif [ $choice -eq 5 ]; then
    read -p "SSID Name?> " ssidname
    read -p "SSID Password?> " ssidpass
    nmcli con delete id $ssidname
    nmcli dev wifi connect $ssidname password $ssidpass iface wlan0
    
  elif [ $choice -eq 6 ]; then
    read -p "ID Name?> " idname
    nmcli con delete id $idname iface wlan0
    
  elif [ $choice -eq 7 ]; then
    plasma-windowed org.kde.networkmanagement
    
  elif [ $choice -eq 8 ]; then
   echo "now time is $(date)"
    
  elif [ $choice -eq 9 ]; then
    plasma-windowed digital-clock
    
  elif [ $choice -eq 10 ]; then
    echo "now battery is $(upower -i  /org/freedesktop/UPower/devices/battery_BAT0 | grep percentage | cut -c 26-29)"
    
  elif [ $choice -eq 11 ]; then
    plasma-windowed battery
    
  else
    echo "invalid selection"
    
  fi

done

echo -e "program finished \n"