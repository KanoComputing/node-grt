#include "NodeTimeSeriesClassificationData.h"
#include "NodeDTW.h"
#include "NodeHMM.h"
#include "NodeKMeansQuantizer.h"

using v8::FunctionTemplate;

NAN_MODULE_INIT(InitAll) {
    NodeTimeSeriesClassificationData::Init(target);
    NodeDTW::Init(target);
    NodeHMM::Init(target);
    NodeKMeansQuantizer::Init(target);
}

NODE_MODULE(GRT, InitAll)
