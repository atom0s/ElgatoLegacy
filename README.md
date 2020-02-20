# ElgatoLegacy
Use your Elgato Stream Deck on Windows 7, 8 and 8.1!

## Donate :heart:

Wish to donate to say thanks? [Donate via Paypal.](https://paypal.me/atom0s)

## Installation / How To Use

Please view the wiki page linked below for a full explaination on how to use this.

[Installation Guide](https://github.com/atom0s/ElgatoLegacy/wiki)

## Background

Elgato's popular Stream Deck hardware is sadly locked down to only working on Windows 10. Both the installer and the actual files are setup in a manner to block users from running the Stream Deck software on a non-Windows 10 machine.  The installer will prompt users that their operating system is not supported. Upon bypassing the installer, attempting to run StreamDeck.exe will result in errors due to bad imports / missing requirements on older systems.

This project solves the later of those problems by creating three proxy DLLs that are used to fake the intended API calls that StreamDeck.exe looks for. With these three proxy modules, StreamDeck.exe is fully functional on Windows 7, Windows 8 and Windows 8.1.

## Building

ElgatoLegacy is build using Visual Studio 2019. Please note; in order to target older systems properly, the projects are built against the XP version of the Visual Studio C++ 2017 Windows XP (v141_xp) development toolset. You must install this toolkit separately from the Visual Studio installer. To install this, follow these quick steps:

  * Install Visual Studio 2019. (Be sure to install the typical Desktop C++ development environment and tools.)
  * Open Control Panel on your system.
  * Open 'Programs & Features'.
  * Right-click the 'Microsoft Visual Studio Installer' for 2019 and choose 'Change'.
  * Next to your 'Visual Studio 2019' version, click the 'Modify' button.
  * Click the 'Individual Components' tab at the top.
  * Check the box next to 'MSVC v141 - VS 2017 x86/x64 build tools (v14.16)'.
  * Check the box next to 'C++ Windows XP Support for VS 2017 (v141) tools [Deprecated]'.

Apply your changes to install these extra components and then you should be all set to compile the project within VS2019 as-is.

## Legal

I am not affiliated with Elgato in any way. Nor am I affiliated with any of Elgato's partners.

You are responsible for anything you do while making use of this project. Use at your own risk.