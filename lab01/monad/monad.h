#ifndef MONAD_H
#define MONAD_H

#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <vector>

#include "monad_shared.h"
#include "random.h"
#include "util.h"

using namespace std;
using namespace util;
using namespace monad_shared;

namespace monad
{

void printHelp();
void printHelpConfig();
void printHelpTests();
void printLicense();
const char * getRandomQuote();

}

#endif // MONAD_H
