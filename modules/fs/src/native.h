size_t os_get_homedir(char *to, size_t to_len);

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Shlobj.h>
#pragma comment(lib, "Shell32.lib")
size_t os_get_homedir(char *to, size_t to_len)
{
    char homedir[MAX_PATH];
    if (SHGetFolderPathA(0, CSIDL_COMMON_APPDATA, NULL, SHGFP_TYPE_CURRENT, homedir) != S_OK){
        return 0;       
    }

    size_t ll = strlen(homedir);
    if (ll > to_len) {            
        return 0;
    } 

    memcpy(to, homedir, ll);
    return ll;    
}
#endif

#ifdef __unix__


#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>


size_t os_get_homedir(char *to, size_t to_len)
{
    struct passwd *pw = getpwuid(getuid());
    if (pw == 0) {
        return 0;
    }
    const char *homedir = pw->pw_dir;

    size_t ll = strlen(homedir);

    if (ll > to_len) {
        memcpy(to, homedir, to_len);
        return to_len;
    } else {
        memcpy(to, homedir, ll);
        return ll;
    }
}


#endif

