#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/modii/Documents/Development/max4live/mxos/build
  make -f /Users/modii/Documents/Development/max4live/mxos/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/modii/Documents/Development/max4live/mxos/build
  make -f /Users/modii/Documents/Development/max4live/mxos/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/modii/Documents/Development/max4live/mxos/build
  make -f /Users/modii/Documents/Development/max4live/mxos/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/modii/Documents/Development/max4live/mxos/build
  make -f /Users/modii/Documents/Development/max4live/mxos/build/CMakeScripts/ReRunCMake.make
fi

