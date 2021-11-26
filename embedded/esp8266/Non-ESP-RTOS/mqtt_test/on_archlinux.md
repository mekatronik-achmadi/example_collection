### run MQTT broker on Arch-based OS

##### install necessary

```
sudo pacman -S mosquitto libwebsockets
```

##### run broker

```
sudo systemctl start mosquitto
sudo systemctl enable mosquitto
```

##### get IP on network (if not on internet)

```
ifconfig
```

##### sub/pub test on topic hello/world

```
mosquitto_sub -t hello/world
mosquitto_pub -t hello/world -m "MQTT on ArchLinux"
```