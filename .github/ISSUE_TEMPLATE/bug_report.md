---
name: Bug report
about: Create a report to help us improve
title: ''
labels: ''
assignees: ''

---

---
name: Bug report
about: Create a report to help us fix your issue

---

**Is this the right place for my bug report?**
This repository contains the GPU firmware used on the Raspberry Pi. This software is the closed source part of the Raspberry Pi system, it includes booting (including network booting and USB booting), low-level power and clock control, FKMS and legacy HDMI control (not full KMS that is in the linux kernel), hardware legacy codecs (MPEG2, H264 and VC1), encode hardware including the ISP (image sensor pipeline) and camera control, audio output (analogue and HDMI audio).

If you believe that the issue you are seeing is within this area, this is the right place. If not, we have other repositories for the linux kernel at [github.com/raspberrypi/linux](https://github.com/raspberrypi/linux) and Raspberry Pi userland applications at [github.com/raspberrypi/userland](https://github.com/raspberrypi/userland). If you have problems with the Raspbian distribution packages, report them in the [github.com/RPi-Distro/repo](https://github.com/RPi-Distro/repo). If you simply have a question, then [the Raspberry Pi forums](https://www.raspberrypi.org/forums) are the best place to ask it.

**Describe the bug**
Add a clear and concise description of what you think the bug is.

**To reproduce**
List the steps required to reproduce the issue.

**Expected behaviour**
Add a clear and concise description of what you expected to happen.

**Actual behaviour**
Add a clear and concise description of what actually happened.

**System**
 Copy and paste the results of the raspinfo command in to this section. Alternatively, copy and paste a pastebin link, or add answers to the following questions:

* Which model of Raspberry Pi? e.g. Pi3B+, PiZeroW
* Which OS and version (`cat /etc/rpi-issue`)?
* Which firmware version (`vcgencmd version`)?
* Which kernel version (`uname -a`)?

**Logs**
If applicable, add the relevant output from `dmesg` or similar.

**Additional context**
Add any other relevant context for the problem.
