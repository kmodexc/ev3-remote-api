to run this without sudo use 
```KERNEL=="hidraw*", SUBSYSTEM=="hidraw", MODE="0664", GROUP="plugdev"```
and place it in `/etc/udev/rules/99-hidraw-permissions.rules`
