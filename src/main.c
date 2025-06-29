#include <API.h>
#include <extrn/tomlc17.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void __shift_argv(char **argv[], int *argc) {
  *argv = *argv + 1;
  *argc -= 1;
}

#define SHIFT_ARGV __shift_argv

#define COMMAND_HELP 0x0000
#define COMMAND_INSTALL 0x0001
#define COMMAND_REMOVE 0x0002
#define COMMAND_UPDATE 0x0003
#define COMMAND_LISTDB 0x0004
#define COMMAND_LIST 0x0005
#define COMMAND_SEARCH 0x0006

#define FLAGS_CONF 0x0001

toml_result_t G_config;

int Program_install(int argc, char *argv[], INT flags) {}

int main(int argc, char *argv[]) {

  INT command =
      COMMAND_HELP; /* Change this when the user specifies any commands */
  INT flags = 0;
  SHIFT_ARGV(&argv, &argc);
  for (int i = 0; i < argc; ++i) {
    if (!strcmp(argv[i], "help") || !strcmp(argv[i], "h")) {
      break;
    } else if (!strcmp(argv[i], "install") || !strcmp(argv[i], "i")) {
      command = COMMAND_INSTALL;
    } else if (!strcmp(argv[i], "list") || !strcmp(argv[i], "l")) {
      command = COMMAND_LIST;
    } else if (strcmp(argv[i], "remove") == 0 || strcmp(argv[i], "r") == 0) {
      command = COMMAND_REMOVE;
    } else if (strcmp(argv[i], "update") == 0 || strcmp(argv[i], "u") == 0) {
      command = COMMAND_UPDATE;
    } else if (strcmp(argv[i], "listdb") == 0 || strcmp(argv[i], "ld") == 0) {
      command = COMMAND_LISTDB;
    } else if (strcmp(argv[i], "search") == 0 || strcmp(argv[i], "s") == 0) {
      command = COMMAND_SEARCH;
    } else if (strcmp(argv[i], "-c") == 0 && i + 1 <= argc) {
      G_config = toml_parse_file_ex(argv[i++]);
    }

    if (command == COMMAND_INSTALL) {
      /* TODO: Implement the INSTALL flags */
    }
  }

  if (command == COMMAND_HELP) {
    printf("help or h: Shows this message\n"
           "install <PKGS> or i <PKGS>: install a package from the repository\n"
           "remove <PKGS> or r <PKGS>: remove a package from the system\n"
           "update or u: update all packages in the system\n"
           "listdb or ld: packages from all repositories in the database\n"
           "list or l: list all installed packages\n"
           "search <PKG> or s <PKG>: search for a package in the system\n");
    return 0;
  } else if (command == COMMAND_INSTALL) {
    Program_install(argc, argv, flags);
  }
}