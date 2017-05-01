#include <stdlib.h>

// These are paths to folders in /sys which contain "uevent" file
// need to init this device.
// MultiROM needs to init framebuffer, mmc blocks, input devices,
// some ADB-related stuff and USB drives, if OTG is supported
// You can use * at the end to init this folder and all its subfolders
const char *mr_init_devices[] =
{

    "/sys/devices/virtual/mem/null",
    "/sys/devices/virtual/misc/fuse",

    "/sys/class/graphics/fb0",
    "/sys/class/graphics/fb1",
    "/sys/devices/virtual/graphics/fb0",
    "/sys/devices/virtual/graphics/fb1",

    "/sys/block/mmcblk0",
    "/dev/block/bootdevice/by-name",
    "/dev/block/platform/soc/7824900.sdhci",
    "/dev/block/platform/soc/7824900.sdhci/by-name",
    "/dev/block/platform/soc/7824900.sdhci/by-name/system", //system
    "/dev/block/platform/soc/7824900.sdhci/by-name/cache",
    "/dev/block/platform/soc/7824900.sdhci/by-name/userdata",
    "/dev/block/platform/soc/7824900.sdhci/by-name/boot",
    "/dev/block/platform/soc/7824900.sdhci/by-name/recovery",
    "/dev/block/platform/soc/7824900.sdhci/by-name/modem",
    "/sys/bus/mmc",
    "/sys/bus/mmc/drivers/mmcblk",
    "/sys/module/sdhci",
    "/sys/module/sdhci*",
    "/sys/module/sdhci_msm",
    "/sys/module/sdhci_msm*",
    "/sys/module/msm_core",

    // for input
    "/sys/devices/virtual/input*",
    "/sys/devices/virtual/input/*",
    "/sys/devices/soc/soc:gpio_keys/input*",
    "/sys/devices/soc/soc:gpio_keys/input/input6",
    "/sys/devices/soc/soc:gpio_keys/input/input6/event6",
    "/sys/devices/virtual/misc/uinput",
    "/sys/devices/virtual/input/mice",
    "/sys/devices/virtual/input*",
    "/sys/devices/virtual/input/input*",
    "/sys/devices/virtual/input/input*/event*",
    "/sys/module/uinput",
    // i2c
    "/sys/devices/soc/78b7000.i2c/i2c-3/3-0020/input*",
    "/sys/devices/soc/78b7000.i2c/i2c-3/3-0020/input/input2",

    // for adb
    "/sys/class/android_usb/android0*",
    "/sys/bus/platform/drivers/android_usb",
    "/sys/bus/usb",

    // for qualcomm overlay - /dev/ion
    "/sys/devices/virtual/misc/ion",

    // Encryption
    "/sys/devices/virtual/misc/device-mapper",
    "/sys/devices/virtual/qseecom/qseecom",

    NULL
};
