#include "Brain.h"
#include <dlfcn.h>
#include <unistd.h>

Brain::Brain(std::string& name)
  : _name(name)
  , _handle(NULL)
  , _chooseMove(NULL)
{
  char cwd[1024];
  getcwd(cwd, sizeof(cwd));
  std::string pwd(cwd);
  std::string filename = pwd + "/" + name + ".so";
  _handle = dlopen(filename.c_str(), RTLD_LAZY);
  if (_handle == NULL) {
    std::cerr << "Cannot open library: " << dlerror() << '\n';
    exit(-1);
  }
  _chooseMove = (int (*)(MoveList& m))dlsym(_handle, "chooseMove");
}

Brain::~Brain() {
  dlclose(_handle);
}


int Brain::chooseMove(MoveList& m) {
  return _chooseMove(m);
}