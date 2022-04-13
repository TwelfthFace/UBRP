# UBRP
## UDEV Block Restriction Policies
This is a group effort. We have decided to create a program that allows for tracking &amp; authentication of USB devices via UDEV and functionality in the Linux Kernel (>3.8). This program was created for our Cyber Security MEng course at Leeds Beckett University.
UBRP is a program which will function to authenticate USB devices and is intended to be setup on a workstation that uses Linux. For optimal usage the default settings for authentication should be 0 across the USB interfaces, then in conjunction with this program, you can use UDEV to create authentication rules for the mouse & keyboard, for example. 

This program was created to prevent bad usb attacks (simular to USBGuard). Although this is an example proof of concept program that shouldn't be employed in a professional enviroment, this program does not come with any warrenty or guarantees.


Program must be ran as root to function.

#### Compile Instructions:
```
qmake UBRP.pro
make
./UBRP
```
Coded by Jack Daniel

Group Project Members:
Laura Arnold, Akilah Alnasser, Abhinav Maddukuri, and, Jack Daniel.
