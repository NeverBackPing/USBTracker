# USBTracker #

**usbtracker** is a lightweight tool to monitor USB-related events (`bind`, `add`, `remove`, etc.) in real-time on Linux systems using `udev`.

## 📦 Features

- Logs USB events (e.g., `bind`, `add`, `remove`)
- Displays device information: vendor, product, manufacturer, serial number, etc.
- Exports events in JSON format
- Can be run as a system daemon (optional)

## 🛠️ Dependencies

```
sudo apt-get install libudev-dev
```
```
sudo touch /var/log/usbtracker.log
```
```
sudo chmod 666 /var/log/usbtracker.log
```

## ⚙️ Clone & Execute

```
git clone git@github.com:NeverBackPing/USBTracker.git
```

```
cd USBTracker
```

```
make && sudo make run
```
```
sudo mv usbtracker /usr/local/bin/
```
## 🐧 Linux setting
```
sudo su
```
```
cp usbtracker.service /etc/systemd/system/
```
```
systemctl daemon-reexec
```
```
sudo systemctl enable usbtracker
```
```
sudo systemctl start usbtracker
````
Check if usbtracker.service okay
```
systemctl status usbtracker.service
````
