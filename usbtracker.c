# include <libudev.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <sys/select.h>
# include <unistd.h>

void log_event(FILE *f, const char *action, struct udev_device *dev) 
{
    char timestamp[64];
    struct timespec ts;
    clock_gettime(0, &ts);
    struct tm *tm_info = localtime(&ts.tv_sec);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%S", tm_info);

    const char *devnode = udev_device_get_devnode(dev);
    const char *vendor = udev_device_get_sysattr_value(dev, "idVendor");
    const char *product = udev_device_get_sysattr_value(dev, "idProduct");
    const char *manufacturer = udev_device_get_sysattr_value(dev, "manufacturer");
    const char *serial = udev_device_get_sysattr_value(dev, "serial");
    const char *devtype = udev_device_get_devtype(dev);
    const char *speed = udev_device_get_sysattr_value(dev, "speed");
    const char *product_name = udev_device_get_sysattr_value(dev, "product");

    fprintf(f,
        "{\n"
        "  \"timestamp\": \"%s.%03ld\",\n"
        "  \"action\": \"%s\",\n"
        "  \"devnode\": \"%s\",\n"
        "  \"vendor\": \"%s\",\n"
        "  \"product\": \"%s\",\n"
        "  \"manufacturer\": \"%s\",\n"
        "  \"serial\": \"%s\",\n"
        "  \"devtype\": \"%s\",\n"
        "  \"speed\": \"%s\",\n"
        "  \"product_name\": \"%s\"\n"
        "},\n",
        timestamp, ts.tv_nsec / 1000000,
        action ? action : "unknown",
        devnode ? devnode : "unknown",
        vendor ? vendor : "unknown",
        product ? product : "unknown",
        manufacturer ? manufacturer : "unknown",
        serial ? serial : "unknown",
        devtype ? devtype : "unknown",
        speed ? speed : "unknown",
        product_name ? product_name : "unknown"
    );
    fflush(f);
}

int main(void)
{
    struct udev *udev = udev_new();
    if (!udev)
    {
        fprintf(stderr, "Cannot create udev context\n");
        return 1;
    }

    struct udev_monitor *mon = udev_monitor_new_from_netlink(udev, "udev");
    udev_monitor_filter_add_match_subsystem_devtype(mon, "usb", NULL);
    udev_monitor_enable_receiving(mon);

    int fd = udev_monitor_get_fd(mon);

    FILE *logfile = fopen("usbtracker.log", "w");
    if (!logfile)
    {
        perror("Cannot open usbtracker.log");
        udev_unref(udev);
        return 1;
    }

    fprintf(logfile, "[\n");

    printf("USBTracker v2 démarré - collecte avancée\n");

    int first_entry = 1;

    while (1)
    {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(fd, &fds);

        int ret = select(fd + 1, &fds, NULL, NULL, NULL);
        if (ret < 0)
        {
            perror("select");
            break;
        }

        if (FD_ISSET(fd, &fds))
        {
            struct udev_device *dev = udev_monitor_receive_device(mon);
            if (dev)
            {
                const char *action = udev_device_get_action(dev);

                if (!first_entry)
                    fprintf(logfile, ",\n");
                else
                    first_entry = 0;

                log_event(logfile, action, dev);

                printf("Event: %s on %s\n", action ? action : "unknown", udev_device_get_devnode(dev));

                udev_device_unref(dev);
            }
        }
    }

    fprintf(logfile, "\n]\n");
    fclose(logfile);
    udev_monitor_unref(mon);
    udev_unref(udev);
    return 0;
}
