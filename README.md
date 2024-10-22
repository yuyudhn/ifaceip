# ifaceip
A simple utility for checking the IP address of a network interface.

## Compile
```bash
gcc -o ifaceip ifaceip.c -static
```
```bash
sudo mv ifaceip /usr/local/bin
```

Pre-compiled binary at bin/ directory.

## How to use
```bash
ifaceip wlan0
ifaceip wlan0 | xargs echo "My IP:"
```

Just like that. I created this for my own needs, so I don’t know if it will be useful for you.
