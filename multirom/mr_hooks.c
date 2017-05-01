/*
 * This file contains device specific hooks.
 * Always enclose hooks to #if MR_DEVICE_HOOKS >= ver
 * with corresponding hook version!
 */

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>

#if MR_DEVICE_HOOKS >= 1

int mrom_hook_after_android_mounts(const char *busybox_path, const char *base_path, int type)
{
    // On m8, this fstab file is used to remount system to RO,
    // but with MultiROM, it remounts everything as RO, even /data and /cache
    if(access("/remount.qcom", F_OK) >= 0)
        remove("/remount.qcom");

    // remove mounting from .rc files
    int res = -1;
    int add_dummy = 0;
    char *l;
    char line[1024];
    char path_in[128];
    char path_out[128];
    FILE *in, *out;
    DIR *d;
    struct dirent *dp;

    d = opendir("/");
    if(!d)
        return -1;

    while((dp = readdir(d)))
    {
        if(dp->d_type != DT_REG || !strstr(dp->d_name, ".rc"))
            continue;

        snprintf(path_out, sizeof(path_out), "/%s", dp->d_name);
        snprintf(path_in, sizeof(path_in), "/%s.new", dp->d_name);

        if(rename(path_out, path_in) < 0)
            goto exit;

        in = fopen(path_in, "r");
        if(!in)
            goto exit;

        out = fopen(path_out, "w");
        if(!out)
        {
            fclose(in);
            goto exit;
        }

        while((fgets(line, sizeof(line), in)))
        {
            for(l = line; isspace(*l); ++l);

            if (strncmp(l, "on ", 3) == 0)
                add_dummy = 1;
            else if (strstr(l, "mount ") &&
                (strstr(l, "/data") || strstr(l, "/system") || strstr(l, "/cache")))
            {
                if(add_dummy == 1)
                {
                    add_dummy = 0;
                    fputs("    export DUMMY_LINE_INGORE_IT 1\n", out);
                }

                fputc((int)'#', out);
            }

            fputs(line, out);
        }

        fclose(out);
        fclose(in);
        remove(path_in);

        chmod(path_out, 0750);
    }

    res = 0;
exit:
    closedir(d);
    return res;
}

#endif /* MR_DEVICE_HOOKS >= 1 */

#if MR_DEVICE_HOOKS >= 2
void mrom_hook_before_fb_close(void) { }
#endif

#if MR_DEVICE_HOOKS >= 3
void tramp_hook_before_device_init(void) { }
#endif

#if MR_DEVICE_HOOKS >= 4
int mrom_hook_allow_incomplete_fstab(void)
{
    return 1;
}
#endif
