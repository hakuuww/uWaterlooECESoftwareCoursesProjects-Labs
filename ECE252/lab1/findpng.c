#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>

#include <sys/types.h>

#include "./starter/png_util/lab_png.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PATH_MAX 4096

int isDirCurrentOrParentDirectory(const char *dirName) {
  return (strcmp(dirName, ".") == 0 || strcmp(dirName, "..") == 0);
}

int findpng(const char *path, int *count) {
  struct dirent *entry;
  DIR *dir = opendir(path);

  if (dir == NULL) { // should not happen inside reccursion
    //perror("Unable to open directory");
    return -11;
  }

  while ((entry = readdir(dir)) !=
         NULL) // not end of the path list inside a directory
  {
    if (!(isDirCurrentOrParentDirectory(entry->d_name))) {

      char new_path[PATH_MAX]; // Create a new buffer to store the concatenated
                               // path
      snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name);

      struct stat file_stat;
      if (lstat(new_path, &file_stat) == -1) {
        perror("Unable to get file information");
        continue;
      }
      if (S_ISDIR(file_stat.st_mode)) {
        findpng(new_path, count); // Recursive call for directories
      } else if (S_ISREG(file_stat.st_mode)) {
        if (is_png(new_path)) {
          (*count)++;
          printf("%s\n", new_path);
        }; // Process regular files
      }
    }
  }

  closedir(dir);
  return 0;
}

int main(int argc, char *argv[]) {
  int count = 0;
  char path[PATH_MAX];

  if (argc == 1) {
    if (getcwd(path, sizeof(path)) == NULL) {
      exit(-1);
    }
    findpng(path, &count);
  } else {
    findpng(argv[1], &count);
  }

  if (count == 0) {
    printf("findpng: No PNG file found \n");
  }

  return 0;
}
