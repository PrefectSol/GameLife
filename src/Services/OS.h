enum OS
{
    Linux,
    Windows
};

OS GetOS()
{
    return
#ifdef __linux
    OS::Linux;
#elif defined _WIN32
    OS::Windows;
#elif defined _WIN64
    OS::Windows;
#endif
}