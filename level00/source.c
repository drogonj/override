int32_t main(int32_t argc, char** argv, char** envp)
{
    puts(str: "********************************…");
    puts(str: "* \t     -Level00 -\t\t  *");
    puts(str: "********************************…");
    printf(format: "Password:");

    int32_t var_14;
    __isoc99_scanf(format: "%d", &var_14);
   
    if (var_14 != 0x149c) {
        puts(str: "\nInvalid Password!");
        return 1;
    }
      
    puts(str: "\nAuthenticated!");
    system(line: "/bin/sh");
    return 0;
}
