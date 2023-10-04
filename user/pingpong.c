#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{

  int p_parent[2];
  int p_child[2];

  char buf;

  pipe(p_parent);
  pipe(p_child);

  int pid = fork();
  
  if(pid == 0){
    
    read(p_parent[0], &buf,1);
    printf("%d: received ping\n", getpid());
    write(p_child[1],"b",1);
  } else{
    write(p_parent[1],"b",1);
    
    read(p_child[0], &buf,1);
    printf("%d: received pong\n", getpid());
  }

  exit(0);
}