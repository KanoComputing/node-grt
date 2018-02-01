#include "NodeTimeSeriesClassificationData.h"
#include "NodeDTW.h"

using v8::FunctionTemplate;

// NativeExtension.cc represents the top level of the module.
// C++ constructs that are exposed to javascript are exported here

NAN_MODULE_INIT(InitAll) {  
  NodeTimeSeriesClassificationData::Init(target);
  NodeDTW::Init(target);
}

NODE_MODULE(NativeExtension, InitAll)
