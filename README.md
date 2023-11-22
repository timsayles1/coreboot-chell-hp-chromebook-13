# coreboot-chell-hp-chromebook-13
Modified Coreboot for HP Chromebook 13

Replaced standard coreboot boot logo with HP logo for a more "factory" look.

Download coreboot.rom to USB drive.

You will need to flash the standard Coreboot firmware first and go ahead and install Linux. 
The latest Fedora along with the audio utility script (for sound) run great on this latop.

Fedora Workstation -- > https://download.fedoraproject.org/pub/fedora/linux/releases/39/Workstation/x86_64/iso/Fedora-Workstation-Live-x86_64-39-1.5.iso
Audio Script -- > https://github.com/WeirdTreeThing/chromebook-linux-audio

After Linux Installation, open the Terminal
Download and execute Mr. ChromeBox's firmware script

Script commands -- > cd; curl -LO mrchromebox.tech/firmware-util.sh && sudo bash firmware-util.sh

select option "2" (restore factory ROM)
select your USB drive
type in coreboot.rom

Reboot and enjoy your new boot logo.

Modified source included in Repo for reference.
